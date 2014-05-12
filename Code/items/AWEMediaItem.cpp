// header file
#include "AWEMediaItem.h"

// debug
#include "debug_macros/debug.h"

// for file reading
#include "libs/generic_file_reader/file_reader.h"
#include <QTextStream>

// for writing to file
#include <iostream>
#include <fstream>

// for URL handling
#include <QUrl>

// for property parsing
#include <sstream>
#include <string>

using namespace AWE;
using namespace Json;
using namespace std;

MediaItem::MediaItem(QDir file) :
	myConfigFile(file),
	myData(),
	myHasBeenEdited(false)
{
	// read in the JSON file
	Reader reader;
	QString contents;
	QTextStream stream(&contents);
	copyFile(file.absolutePath(), stream);
	reader.parse(contents.toStdString(), myData, false);
	// now refresh the properties
	refresh();
}

MediaItem::~MediaItem()
{
	// write to file if necessary
	if (hasBeenEdited())
	{
		ofstream out(myConfigFile.absolutePath().toStdString());
		out << myData;
	}
}

QString MediaItem::getName() const
{
	return myName;
}

QString MediaItem::getType() const
{
	return myType;
}

QString MediaItem::getDescription() const
{
	return myDescription;
}

QString MediaItem::getLocation() const
{
	return myLocation;
}

int MediaItem::numIcons() const
{
	return myIconImages.count();
}

QPixmap MediaItem::getIcon(int i) const
{
	if (i < 0 || i >= numIcons())
	{
		return QPixmap();
	}
	return myIconImages.at(i);
}

QPixmap MediaItem::getDefaultIcon() const
{
	return getIcon(myDefaultIconIndex);
}

int MediaItem::getDefaultIconIndex() const
{
	return myDefaultIconIndex;
}

int MediaItem::numFanarts() const
{
	return myFanartImages.count();
}

QPixmap MediaItem::getFanart(int i) const
{
	if (i < 0 || i >= numFanarts())
	{
		return QPixmap();
	}
	return myFanartImages.at(i);
}

QPixmap MediaItem::getDefaultFanart() const
{
	return getFanart(myDefaultFanartIndex);
}

int MediaItem::getDefaultFanartIndex() const
{
	return myDefaultFanartIndex;
}

int MediaItem::numDetails() const
{
	return myDetailNames.count();
}

QString MediaItem::getDetailName(int i) const
{
	return myDetailNames.at(i);
}

const Value& MediaItem::getDetailValue(int i) const
{
	if (i < 0 || i >= numDetails())
	{
		return Value::null;
	}
	string key = myData["metadata"]["details"]["_order"][i].asString();
	return myData["metadata"]["details"][key];
}

QString MediaItem::getDetailValueAsString(int i) const
{
	return stringFor(getDetailValue(i));
}

bool MediaItem::hasDetail(QString detail) const
{
	return myDetailNames.contains(detail);
}

const Json::Value& MediaItem::getDetailValue(QString name) const
{
	if (hasDetail(name))
	{
		return myData["metadata"]["details"][name.toStdString()];
	}
	return Value::null;
}

QString MediaItem::getDetailValueAsString(QString name) const
{
	return stringFor(getDetailValue(name));
}

QDir MediaItem::getConfigFile() const
{
	return myConfigFile;
}

void MediaItem::markAsEdited()
{
	myHasBeenEdited = true;
}

bool MediaItem::hasBeenEdited() const
{
	return myHasBeenEdited;
}

void MediaItem::refresh()
{
	// for resetting the value after all of these operations
	bool hasBeenEditedRest = hasBeenEdited();

	// text infos
	setName(myData["metadata"]["name"].asCString());
	setType(myData["metadata"]["type"].asCString());
	setDescription(myData["metadata"]["description"].asCString());
	setLocation(myData["metadata"]["location"].asCString());

	QDir dir(myConfigFile.absolutePath());
	dir.cdUp();
	// icons
	Value temp = myData["metadata"]["icons"];
	myData["metadata"]["icons"]["default"] = -1;
	myData["metadata"]["icons"]["files"].clear();
	for (auto str : temp["files"])
	{
		QUrl url(str.asCString());
		if (url.isValid() && !url.isRelative())
		{
			addIcon(str.asCString());
		}
		else
		{
			addIcon(dir.absoluteFilePath(str.asCString()));
		}
	}
	setDefaultIconIndex(temp["default"].asInt());

	// fanarts
	temp = myData["metadata"]["fanarts"];
	myData["metadata"]["fanarts"]["default"] = -1;
	myData["metadata"]["fanarts"]["files"].clear();
	for (auto str : temp["files"])
	{
		QUrl url(str.asCString());
		if (url.isValid() && !url.isRelative())
		{
			addFanart(str.asCString());
		}
		else
		{
			addFanart(dir.absoluteFilePath(str.asCString()));
		}
	}
	setDefaultFanartIndex(temp["default"].asInt());

	// details
	temp = myData["metadata"]["details"];
	myData["metadata"]["details"].clear();
	for (auto str : temp["_order"])
	{
		addDetail(str.asCString(), stringFor(temp[str.asString()]));
	}

	// reset edit status
	myHasBeenEdited = hasBeenEditedRest;
}

void MediaItem::setName(QString name)
{
	if (myName != name)
	{
		myName = name;
		markAsEdited();
		emit nameChanged(myName);
	}
}

void MediaItem::setType(QString type)
{
	if (myType != type)
	{
		myType = type;
		markAsEdited();
		emit typeChanged(type);
	}
}

void MediaItem::setDescription(QString description)
{
	if (myDescription != description)
	{
		myDescription = description;
		markAsEdited();
		emit descriptionChanged(myDescription);
	}
}

void MediaItem::setLocation(QString location)
{
	if (myLocation != location)
	{
		myLocation = location;
		markAsEdited();
		emit locationChanged(myLocation);
	}
}

bool MediaItem::addIcon(QString file)
{
	QUrl url(file);
	if (url.isValid() && !url.isRelative())
	{
		// since it is a URL, we should import
		return importIcon(file);
	}
	// not a URL, so try it locally
	QPixmap image(file);
	if (!image.isNull())
	{
		// it is a real image, so add it
		myIconImages << image;
		QDir dir(myConfigFile.absolutePath());
		dir.cdUp();
		myData["metadata"]["icons"]["files"].append(dir.relativeFilePath(file).toStdString());
		emit iconAdded(image);
		markAsEdited();
		return true;
	}
	return false;
}

bool MediaItem::importIcon(QString file)
{
	// get the file name
	QString extension = file;
	int ind = file.lastIndexOf('.');
	if (ind != -1)
	{
		extension.replace(0, ind, "");
	}
	QString fileName = myConfigFile.absolutePath()
		+ ".metadata.icons.files."
		+ QString::number(numIcons())
		+ extension;
	// copy the file
	QFile writeToMe(fileName);
	if (writeToMe.open(QIODevice::ReadWrite)
		&& copyFile(file, writeToMe))
	{
		writeToMe.close();
		// succesfully copied, so try to open
		QPixmap image(fileName);
		if (!image.isNull())
		{
			// it is a legit image, so add it
			myIconImages << image;
			myData["metadata"]["icons"]["files"].append(QDir(fileName).dirName().toStdString());
			emit iconAdded(image);
			markAsEdited();
			return true;
		}
		else
		{
			// not a real image, so delete the imported file
			QDir dir(fileName);
			QString nameToRm = dir.dirName();
			dir.cdUp();
			dir.remove(nameToRm);
		}
	}
	// it didn't work
	return false;
}

bool MediaItem::addIcon(QPixmap icon)
{
	if (!icon.isNull())
	{
		// it is a legit image
		// get the file name
		QString fileName = myConfigFile.absolutePath()
			+ ".metadata.icons.files."
			+ QString::number(numIcons())
			+ ".png";
		if (icon.save(fileName))
		{
			// we were able to write the file, so go ahead and add it
			myIconImages << icon;
			myData["metadata"]["icons"]["files"].append(QDir(fileName).dirName().toStdString());
			emit iconAdded(icon);
			markAsEdited();
			return true;
		}
	}
	return false;
}

bool MediaItem::importIcon(QPixmap icon)
{
	return addIcon(icon);
}

bool MediaItem::removeIcon(int i)
{
	// check index validity
	if (i < 0 || i > numIcons())
	{
		// not in range
		return false;
	}
	// remove the file entry
	Value& iconFiles = myData["metadata"]["icons"]["files"];
	for (uint j = i; j < iconFiles.size() - 1; ++ j)
	{
		iconFiles[j] = iconFiles[j + 1];
	}
	iconFiles.resize(iconFiles.size() - 1);
	// remove the icon image
	myIconImages.removeAt(i);
	// change the default index as necessary
	if (getDefaultIconIndex() > i)
	{
		setDefaultIconIndex(getDefaultIconIndex() - 1);
	}
	else if (i == getDefaultIconIndex())
	{
		setDefaultIconIndex(0);
		if (i == 0) // it wouldn't emit in the setter
		{
			emit defaultIconChanged(0);
		}
	}
	// indicate that an icon was removed
	emit iconRemoved(i);
	markAsEdited();
	return true;
}

bool MediaItem::setDefaultIconIndex(int i)
{
	if (i < 0 || i > numIcons()
		|| i == myDefaultIconIndex)
	{
		return false;
	}
	myDefaultIconIndex = i;
	myData["metadata"]["icons"]["default"] = i;
	markAsEdited();
	emit defaultIconChanged(i);
	return true;
}

bool MediaItem::addFanart(QString file)
{
	if (QUrl(file).isValid())
	{
		// since it is a URL, we should import
		return importFanart(file);
	}
	// not a URL, so try it locally
	QPixmap image(file);
	if (!image.isNull())
	{
		// it is a real image, so add it
		myFanartImages << image;
		QDir dir(myConfigFile.absolutePath());
		dir.cdUp();
		myData["metadata"]["fanarts"]["files"].append(dir.relativeFilePath(file).toStdString());
		emit fanartAdded(image);
		markAsEdited();
		return true;
	}
	return false;
}

bool MediaItem::importFanart(QString file)
{
	// get the file name
	QString extension = file;
	int ind = file.lastIndexOf('.');
	if (ind != -1)
	{
		extension.replace(0, ind, "");
	}
	QString fileName = myConfigFile.absolutePath()
		+ ".metadata.fanarts.files."
		+ QString::number(numFanarts())
		+ extension;
	// copy the file
	QFile writeToMe(fileName);
	if (writeToMe.open(QIODevice::ReadWrite)
		&& copyFile(file, writeToMe))
	{
		writeToMe.close();
		// succesfully copied, so try to open
		QPixmap image(fileName);
		if (!image.isNull())
		{
			// it is a legit image, so add it
			myFanartImages << image;
			myData["metadata"]["fanarts"]["files"].append(QDir(fileName).dirName().toStdString());
			emit fanartAdded(image);
			markAsEdited();
			return true;
		}
		else
		{
			// not a real image, so delete the imported file
			QDir dir(fileName);
			QString nameToRm = dir.dirName();
			dir.cdUp();
			dir.remove(nameToRm);
		}
	}
	// it didn't work
	return false;
}

bool MediaItem::addFanart(QPixmap fanart)
{
	if (!fanart.isNull())
	{
		// it is a legit image
		// get the file name
		QString fileName = myConfigFile.absolutePath()
			+ ".metadata.fanarts.files."
			+ QString::number(numFanarts())
			+ ".png";
		if (fanart.save(fileName))
		{
			// we were able to write the file, so go ahead and add it
			myFanartImages << fanart;
			myData["metadata"]["fanarts"]["files"].append(QDir(fileName).dirName().toStdString());
			emit fanartAdded(fanart);
			markAsEdited();
			return true;
		}
	}
	return false;
}

bool MediaItem::importFanart(QPixmap fanart)
{
	return addFanart(fanart);
}

bool MediaItem::removeFanart(int i)
{
	// check index validity
	if (i < 0 || i >= numFanarts())
	{
		// not in range
		return false;
	}
	// remove the file entry
	Value& fanartFiles = myData["metadata"]["fanarts"]["files"];
	for (uint j = i; j < fanartFiles.size() - 1; ++ j)
	{
		fanartFiles[j] = fanartFiles[j + 1];
	}
	fanartFiles.resize(fanartFiles.size() - 1);
	// remove the fanart image
	myFanartImages.removeAt(i);
	// change the default index as necessary
	if (getDefaultFanartIndex() > i)
	{
		setDefaultFanartIndex(getDefaultFanartIndex() - 1);
	}
	else if (i == getDefaultFanartIndex())
	{
		setDefaultFanartIndex(0);
		if (i == 0) // it wouldn't emit in the setter
		{
			emit defaultFanartChanged(0);
		}
	}
	// indicate that an fanart was removed
	emit fanartRemoved(i);
	markAsEdited();
	return true;
}

bool MediaItem::setDefaultFanartIndex(int i)
{
	if (i < 0 || i >= numIcons()
		|| i == myDefaultFanartIndex)
	{
		return false;
	}
	myDefaultFanartIndex = i;
	myData["metadata"]["fanarts"]["default"] = i;
	markAsEdited();
	emit defaultFanartChanged(i);
	return true;
}

bool MediaItem::addDetail(QString name, QString value)
{
	return addDetail(name, Value(value.toStdString()));
}

bool MediaItem::addDetail(QString name, const Value& value)
{
	int i = 0;
	while (i < numDetails() && getDetailName(i) != name)
	{
		++ i;
	}
	if (i < numDetails())
	{
		if (getDetailValue(name).isArray())
		{
			// append to the array
			myData["metadata"]["details"][name.toStdString()].append(value);
			emit detailChanged(i);
			markAsEdited();
			return true;
		}
		else if (getDetailValue(name) != Value(value))
		{
			myData["metadata"]["details"][name.toStdString()] = value;
			emit detailChanged(i);
			markAsEdited();
			return true;
		}
		return false;
	}
	myDetailNames << name;
	myData["metadata"]["details"]["_order"].append(name.toStdString());
	myData["metadata"]["details"][name.toStdString()] = value;
	emit detailAdded(name);
	markAsEdited();
	return true;
}

bool MediaItem::removeDetail(int i)
{
	// check for index validity
	if (i < 0 || i >= numDetails())
	{
		return false;
	}
	// remove the entry
	Value& detailNames = myData["metadata"]["details"]["_order"];
	for (uint j = i; j < detailNames.size() - 1; ++ j)
	{
		detailNames[j] = detailNames[j + 1];
	}
	detailNames.resize(detailNames.size() - 1);
	myData["metadata"]["details"].removeMember(getDetailName(i).toStdString());
	// remove the detail name from the list
	myDetailNames.removeAt(i);
	emit detailRemoved(i);
	markAsEdited();
	return true;
}

bool MediaItem::removeDetail(QString name)
{
	int i = 0;
	while (i < numDetails() && getDetailName(i) != name)
	{
		++ i;
	}
	return removeDetail(i);
}

QString MediaItem::stringFor(const Value& val) const
{
	// strings should just be as is
	if (val.isNull())
	{
		return QString();
	}
	else if (val.isString())
	{
		return val.asCString();
	}
	// numbers should be the decimal representation
	else if (val.isInt())
	{
		return QString::number(val.asInt());
	}
	// booleans are "Yes" or "No"
	else if (val.isBool())
	{
		if (val.asBool())
		{
			return tr("Yes");
		}
		else
		{
			return tr("No");
		}
	}
	// arrays should be comma-separated lists of the strings for each member
	else if (val.isArray() && val.size() > 0)
	{
		QString text = stringFor(val[0]);
		for (uint i = 1; i < val.size(); ++ i)
		{
			text += ", " + stringFor(val[i]);
		}
		return text;
	}
	// objects shouldn't occur, so make it empty
	return QString();
}