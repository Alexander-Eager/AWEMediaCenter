// header file
#include "MetadataHolder.h"

// for testing data
#include <QDir>
#include <QUrl>

// for reading files
#include "libs/generic_file_reader/file_reader.h"

// for debug output
#include <QDebug>

using namespace JSON;

namespace AWE
{
	class MetadataHolderPrivate
	{
		public:
			MetadataHolder* p;

			// make the private data from the given
			// config file
			void make(ConfigFile* f);
			// make a detail string for the given
			// value
			QString stringFor(JsonValue val) const;

			ConfigFile* file;

			QString name;
			QString type;
			QString description;
			QString location;

			QList<QPixmap> iconImages;
			QList<QString> iconFiles;
			QList<bool> iconOwnership;
			int defaultIconIndex;

			QList<QPixmap> fanartImages;
			QList<QString> fanartFiles;
			QList<bool> fanartOwnership;
			int defaultFanartIndex;

			QList<QString> detailNames;
			JsonObject detailValues;
	};
}

using namespace AWE;

void MetadataHolderPrivate::make(ConfigFile* f)
{
	// make the file
	file = f;
	if (!f)
	{
		f = nullptr;
		qCritical() << "MetadataHolder: Configuration file is null";
		return;
	}
	if (!f->isValid())
	{
		qWarning() << "MetadataHolder: Configuration file not valid";
	}

	// this is a flag to see if we should warn about the file
	bool shouldWarnAboutFile = false;

	// check everything for existance
	if (!file->getData().isObject())
	{
		qWarning() << "MetadataHolder: Bad data";
		shouldWarnAboutFile = true;
		file->setData(JsonValue::Object);
	}
	if (!file->getMember({"metadata"}).isObject())
	{
		qWarning() << "MetadataHolder: Bad metadata";
		shouldWarnAboutFile = true;
		file->addMember({"metadata"}, JsonValue::Object);
	}
	if (!file->getMember({"metadata", "name"}).isString())
	{
		qWarning() << "MetadataHolder: Bad name";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "name"}, JsonValue::String);
	}
	if (!file->getMember({"metadata", "type"}).isString())
	{
		qWarning() << "MetadataHolder: Bad type";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "type"}, JsonValue::String);
	}
	if (!file->getMember({"metadata", "description"}).isString())
	{
		qWarning() << "MetadataHolder: Bad description";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "description"}, JsonValue::String);
	}
	if (!file->getMember({"metadata", "location"}).isString())
	{
		qWarning() << "MetadataHolder: Bad location";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "location"}, JsonValue::String);
	}
	if (!file->getMember({"metadata", "icons"}).isObject())
	{
		qWarning() << "MetadataHolder: Bad icons";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "icons"}, JsonValue::Object);
	}
	if (!file->getMember({"metadata", "fanarts"}).isObject())
	{
		qWarning() << "MetadataHolder: Bad fanarts";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "fanarts"}, JsonValue::Object);
	}
	if (!file->getMember({"metadata", "details"}).isObject())
	{
		qWarning() << "MetadataHolder: Bad details";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "details"}, JsonValue::Object);
	}
	if (!file->getMember({"metadata", "icons", "default"}).isNumber())
	{
		qWarning() << "MetadataHolder: Bad default icon";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "icons", "default"}, JsonValue::Number);
	}
	if (!file->getMember({"metadata", "icons", "files"}).isArray())
	{
		qWarning() << "MetadataHolder: Bad icon files";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "icons", "files"}, JsonValue::Array);
	}
	if (!file->getMember({"metadata", "icons", "owned"}).isArray())
	{
		qWarning() << "MetadataHolder: Bad icon ownership";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "icons", "owned"}, JsonValue::Array);
	}
	if (!file->getMember({"metadata", "fanarts", "default"}).isNumber())
	{
		qWarning() << "MetadataHolder: Bad default fanart";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "fanarts", "default"}, JsonValue::Number);
	}
	if (!file->getMember({"metadata", "fanarts", "files"}).isArray())
	{
		qWarning() << "MetadataHolder: Bad fanart files";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "fanarts", "files"}, JsonValue::Array);
	}
	if (!file->getMember({"metadata", "fanarts", "owned"}).isArray())
	{
		qWarning() << "MetadataHolder: Bad fanart ownership";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "fanarts", "owned"}, JsonValue::Array);
	}
	if (!file->getMember({"metadata", "details", "_order"}).isArray())
	{
		qWarning() << "MetadataHolder: Bad detail order";
		shouldWarnAboutFile = true;
		file->addMember({"metadata", "details", "_order"}, JsonValue::Array);
	}

	// get the type
	type = file->getMember({"metadata", "type"}).toString();
	if (type.isEmpty())
	{
		p->setType("Generic");
	}

	// get the name
	name = file->getMember({"metadata", "name"}).toString();
	if (name.isEmpty())
	{
		p->setName(type + " Item");
	}

	// get the description
	description = file->getMember({"metadata", "description"}).toString();

	// get the location
	location = file->getMember({"metadata", "location"}).toString();
	if (QDir(location).isRelative())
	{
		location = file->getPathToConfigFile().absoluteFilePath(location);
	}

	// get the icons
	JsonObject icons = file->getMember({"metadata", "icons"}).toObject();
	// get the default index
	defaultIconIndex = icons["default"].toInteger();
	// add all of the icons
	JsonArray files = icons["files"].toArray();
	JsonArray owned = icons["owned"].toArray();
	int index = 0;
	while (index < files.count())
	{
		// check for existence and add
		if (files.at(index).isString())
		{
			QString str = files.at(index).toString();
			if (QDir(str).isRelative())
			{
				str = file->getPathToConfigFile().absoluteFilePath(str);
			}
			if (QDir().exists(str))
			{
				QPixmap image(str);
				if (!image.isNull())
				{
					iconFiles << str;
					iconImages << image;
					if (owned.count() <= index)
					{
						shouldWarnAboutFile = true;
						owned << false;
						file->appendValueToMember({"metadata", "icons", "owned"},
							false);
					}
					iconOwnership << owned.at(index).toBoolean();
					++ index;
					continue;
				}
			}
		}
		// if we got to this point, there was a problem, so remove it
		files.removeAt(index);
		owned.removeAt(index);
		file->removeMember({"metadata", "icons", "files", index});
		file->removeMember({"metadata", "icons", "owned", index});
		shouldWarnAboutFile = true;
	}
	// check the default index for validity
	if ((defaultIconIndex < 0 || defaultIconIndex >= files.count())
		&& files.count())
	{
		qWarning() << "MetadataHolder: Bad default icon index";
		shouldWarnAboutFile = true;
		defaultIconIndex = 0;
		file->setMember({"metadata", "icons", "default"}, 0);
	}

	// get the fanarts
	JsonObject fanarts = file->getMember({"metadata", "fanarts"}).toObject();
	// get the default index
	defaultFanartIndex = fanarts.value("default").toInteger();
	// add all of the fanarts
	files = fanarts.value("files").toArray();
	owned = fanarts.value("owned").toArray();
	index = 0;
	while (index < files.count())
	{
		// check for existence and add
		if (files.at(index).isString())
		{
			QString str = files.at(index).toString();
			if (QDir(str).isRelative())
			{
				str = file->getPathToConfigFile().absoluteFilePath(str);
			}
			if (QDir().exists(str))
			{
				QPixmap image(str);
				if (!image.isNull())
				{
					fanartFiles << str;
					fanartImages << image;
					fanartOwnership << owned.at(index).toBoolean();
					++ index;
					continue;
				}
			}
		}
		// if we got to this point, there was a problem, so remove it
		files.removeAt(index);
		owned.removeAt(index);
		file->removeMember({"metadata", "fanarts", "files", index});
		file->removeMember({"metadata", "fanarts", "owned", index});
		shouldWarnAboutFile = true;
	}
	// check the default index for validity
	if ((defaultFanartIndex < 0 || defaultFanartIndex >= files.count())
		&& files.count())
	{
		qWarning() << "MetadataHolder: Bad default fanart index";
		shouldWarnAboutFile = true;
		defaultFanartIndex = 0;
		file->setMember({"metadata", "fanarts", "default"}, 0);
	}

	// get the details
	JsonObject details = file->getMember({"metadata", "details"}).toObject();
	JsonArray order = details.value("_order").toArray();
	index = 0;
	while (index < order.count())
	{
		if (order.at(index).isString())
		{
			QString name = order.at(index).toString();
			detailNames << name;
			if (details.contains(name))
			{
				detailValues[name] = details.value(name);
				++ index;
				continue;
			}
		}
		// need to remove name
		shouldWarnAboutFile = true;
		order.removeAt(index);
		file->removeMember({"metadata", "details", "_order", index});
	}

	// warn about the file
	if (shouldWarnAboutFile)
	{
		qWarning() << "MetadataHolder: One or more errors found in the metadata"
			<< "of config file" << file->getConfigFileName() << "."
			<< "The file was edited to have all necessary members in the right format.";
	}
}

MetadataHolder::MetadataHolder(QString file)
	:	d(new MetadataHolderPrivate)
{
	d->p = this;
	d->make(new ConfigFile(file));
}

MetadataHolder::MetadataHolder(ConfigFile* file)
	:	d(new MetadataHolderPrivate)
{
	d->p = this;
	d->make(file);
}

MetadataHolder::~MetadataHolder()
{
	delete d->file;
}

ConfigFile* MetadataHolder::getConfigFile()
{
	return d->file;
}

QString MetadataHolder::getName() const
{
	return d->name;
}

QString MetadataHolder::getType() const
{
	return d->type;
}

QString MetadataHolder::getDescription() const
{
	return d->description;
}

QString MetadataHolder::getLocation() const
{
	return d->location;
}

int MetadataHolder::numIcons() const
{
	return d->iconFiles.count();
}

QPixmap MetadataHolder::getIcon(int i) const
{
	if (i < 0 || i >= numIcons())
	{
		return QPixmap();
	}
	return d->iconImages[i];
}

QString MetadataHolder::getIconFile(int i) const
{
	if (i < 0 || i >= numIcons())
	{
		return QString();
	}
	return d->iconFiles[i];
}

QPixmap MetadataHolder::getDefaultIcon() const
{
	return getIcon(getDefaultIconIndex());
}

int MetadataHolder::getDefaultIconIndex() const
{
	return d->defaultIconIndex;
}

int MetadataHolder::numFanarts() const
{
	return d->fanartFiles.count();
}

QPixmap MetadataHolder::getFanart(int i) const
{
	if (i < 0 || i >= numFanarts())
	{
		return QPixmap();
	}
	return d->fanartImages[i];
}

QString MetadataHolder::getFanartFile(int i) const
{
	if (i < 0 || i >= numFanarts())
	{
		return QString();
	}
	return d->fanartFiles[i];
}

QPixmap MetadataHolder::getDefaultFanart() const
{
	return getFanart(getDefaultFanartIndex());
}

int MetadataHolder::getDefaultFanartIndex() const
{
	return d->defaultFanartIndex;
}

int MetadataHolder::numDetails() const
{
	return d->detailNames.count();
}

QString MetadataHolder::getDetailName(int i) const
{
	if (i < 0 || i >= numDetails())
	{
		return QString();
	}
	return d->detailNames[i];
}

JsonValue MetadataHolder::getDetailValue(int i) const
{
	if (i < 0 || i >= numDetails())
	{
		return JsonValue();
	}
	return d->detailValues[d->detailNames[i]];
}

QString MetadataHolder::getDetailValueAsString(int i) const
{
	return d->stringFor(getDetailValue(i));
}

bool MetadataHolder::hasDetail(QString detail) const
{
	return d->detailValues.contains(detail);
}

JsonValue MetadataHolder::getDetailValue(QString detail) const
{
	if (!hasDetail(detail))
	{
		return JsonValue();
	}
	return d->detailValues[detail];
}

QString MetadataHolder::getDetailValueAsString(QString detail) const
{
	return d->stringFor(getDetailValue(detail));
}

void MetadataHolder::setName(QString name)
{
	if (name != d->name)
	{
		d->name = name;
		d->file->setMember({"metadata", "name"}, name);
		emit nameChanged(name);
	}
}

void MetadataHolder::setType(QString type)
{
	if (type != d->type)
	{
		d->type = type;
		d->file->setMember({"metadata", "type"}, type);
		emit typeChanged(type);
	}
}

void MetadataHolder::setDescription(QString description)
{
	if (description != d->description)
	{
		d->description = description;
		d->file->setMember({"metadata", "description"}, description);
		emit descriptionChanged(description);
	}
}

void MetadataHolder::setLocation(QString location)
{
	if (location != d->location)
	{
		d->location = location;
		d->file->setMember({"metadata", "location"}, location);
		emit locationChanged(location);
	}
}

bool MetadataHolder::setDefaultIconIndex(int i)
{
	if (i < 0 || i >= numIcons())
	{
		qWarning() << "MetadataHolder: Tried to set default icon to an invalid index";
		return false;
	}
	if (i != getDefaultIconIndex())
	{
		d->defaultIconIndex = i;
		d->file->setMember({"metadata", "icons", "default"}, i);
		emit defaultIconChanged(i);
	}
	return true;
}

bool MetadataHolder::addIcon(QString file)
{
	// test to see if its from the web
	QUrl url(file);
	if (url.isValid() && !url.isRelative())
	{
		return importIcon(file);
	}
	// local file, so link to it
	QPixmap image(file);
	if (!image.isNull())
	{
		d->iconImages << image;
		d->iconFiles << file;
		d->iconOwnership << false;
		d->file->appendValueToMember({"metadata", "icons", "files"},
			d->file->getPathToConfigFile().relativeFilePath(file));
		d->file->appendValueToMember({"metadata", "icons", "owned"},
			false);
		emit iconAdded(image);
		return true;
	}
	qWarning() << "MetadataHolder: Tried to add bad icon file";
	return false;
}

bool MetadataHolder::importIcon(QString file)
{
	// get the file name
	QString extension = file;
	int ind = file.lastIndexOf('.');
	if (ind != -1)
	{
		extension.replace(0, ind, "");
	}
	QString fileName = d->file->getConfigFileName()
		+ ".icon." + QString::number(numIcons())
		+ extension;
	// copy the file
	QFile writeToMe(d->file->getPathToConfigFile().absoluteFilePath(fileName));
	if (writeToMe.open(QIODevice::ReadWrite)
		&& copyFile(file, writeToMe))
	{
		writeToMe.close();
		// succesfully copied, so try to open
		QPixmap image(writeToMe.fileName());
		if (!image.isNull())
		{
			// it is a legit image, so add it
			d->iconImages << image;
			d->iconFiles << writeToMe.fileName();
			d->iconOwnership << true;
			d->file->appendValueToMember({"metadata", "icons", "files"},
				fileName);
			d->file->appendValueToMember({"metadata", "icons", "owned"},
				true);
			emit iconAdded(image);
			return true;
		}
		else
		{
			// not a real image, so delete the imported file
			d->file->getPathToConfigFile().remove(fileName);
		}
	}
	// it didn't work
	qWarning() << "MetadataHolder: Tried to add bad icon";
	return false;
}

bool MetadataHolder::addIcon(QPixmap icon)
{
	if (!icon.isNull())
	{
		QString fileName = d->file->getConfigFileName()
			+ ".icon." + QString::number(numIcons())
			+ ".png";
		if (icon.save(d->file->getPathToConfigFile().absoluteFilePath(fileName)))
		{
			d->iconImages << icon;
			d->iconFiles << d->file->getPathToConfigFile().absoluteFilePath(fileName);
			d->iconOwnership << true;
			d->file->appendValueToMember({"metadata", "icons", "files"},
				fileName);
			d->file->appendValueToMember({"metadata", "icons", "owned"},
				true);
			emit iconAdded(icon);
			return true;
		}
	}
	qWarning() << "MetadataHolder: Tried to add bad icon";
	return false;
}

bool MetadataHolder::importIcon(QPixmap icon)
{
	return addIcon(icon);
}

bool MetadataHolder::removeIcon(int i)
{
	// check index validity
	if (i < 0 || i >= numIcons())
	{
		qWarning() << "MetadataHolder: Tried to remove icon that did not exist";
		return false;
	}
	// delete the file if necessary
	if (d->iconOwnership[i])
	{
		QDir::root().remove(d->iconFiles[i]);
	}
	// remove the icon
	d->iconImages.removeAt(i);
	d->iconFiles.removeAt(i);
	d->iconOwnership.removeAt(i);
	// remove from the config file
	d->file->removeMember({"metadata", "icons", "files", i});
	d->file->removeMember({"metadata", "icons", "owned", i});
	// change default image if necessary
	if (i == getDefaultIconIndex())
	{
		setDefaultIconIndex(0);
	}
	else if (i < getDefaultIconIndex())
	{
		setDefaultIconIndex(getDefaultIconIndex() - 1);
	}
	// emit signals
	emit iconRemoved(i);
	return true;
}

bool MetadataHolder::setDefaultFanartIndex(int i)
{
	if (i < 0 || i >= numFanarts())
	{
		qWarning() << "MetadataHolder: Tried to set default icon to an invalid index";
		return false;
	}
	if (i != getDefaultFanartIndex())
	{
		d->defaultFanartIndex = i;
		d->file->setMember({"metadata", "fanarts", "default"}, i);
		emit defaultFanartChanged(i);
	}
	return true;
}

bool MetadataHolder::addFanart(QString file)
{
	// test to see if its from the web
	QUrl url(file);
	if (url.isValid() && !url.isRelative())
	{
		return importFanart(file);
	}
	// local file, so link to it
	QPixmap image(file);
	if (!image.isNull())
	{
		d->fanartImages << image;
		d->fanartFiles << file;
		d->fanartOwnership << false;
		d->file->appendValueToMember({"metadata", "fanarts", "files"},
			d->file->getPathToConfigFile().relativeFilePath(file));
		d->file->appendValueToMember({"metadata", "fanarts", "owned"},
			false);
		emit fanartAdded(image);
		return true;
	}
	qWarning() << "MetadataHolder: Tried to add bad fanart";
	return false;
}

bool MetadataHolder::importFanart(QString file)
{
	// get the file name
	QString extension = file;
	int ind = file.lastIndexOf('.');
	if (ind != -1)
	{
		extension.replace(0, ind, "");
	}
	QString fileName = d->file->getConfigFileName()
		+ ".fanart." + QString::number(numIcons())
		+ extension;
	// copy the file
	QFile writeToMe(d->file->getPathToConfigFile().absoluteFilePath(fileName));
	if (writeToMe.open(QIODevice::ReadWrite)
		&& copyFile(file, writeToMe))
	{
		writeToMe.close();
		// succesfully copied, so try to open
		QPixmap image(writeToMe.fileName());
		if (!image.isNull())
		{
			// it is a legit image, so add it
			d->fanartImages << image;
			d->fanartFiles << writeToMe.fileName();
			d->fanartOwnership << true;
			d->file->appendValueToMember({"metadata", "fanarts", "files"},
				fileName);
			d->file->appendValueToMember({"metadata", "fanarts", "owned"},
				true);
			emit fanartAdded(image);
			return true;
		}
		else
		{
			// not a real image, so delete the imported file
			d->file->getPathToConfigFile().remove(fileName);
		}
	}
	// it didn't work
	qWarning() << "MetadataHolder: Tried to add bad fanart";
	return false;
}

bool MetadataHolder::addFanart(QPixmap fanart)
{
	if (!fanart.isNull())
	{
		QString fileName = d->file->getConfigFileName()
			+ ".fanart." + QString::number(numIcons())
			+ ".png";
		if (fanart.save(d->file->getPathToConfigFile().absoluteFilePath(fileName)))
		{
			d->fanartImages << fanart;
			d->fanartFiles << d->file->getPathToConfigFile().absoluteFilePath(fileName);
			d->fanartOwnership << true;
			d->file->appendValueToMember({"metadata", "fanarts", "files"},
				fileName);
			d->file->appendValueToMember({"metadata", "fanarts", "owned"},
				true);
			emit fanartAdded(fanart);
			return true;
		}
	}
	qWarning() << "MetadataHolder: Tried to add bad fanart";
	return false;
}

bool MetadataHolder::importFanart(QPixmap fanart)
{
	return importFanart(fanart);
}

bool MetadataHolder::removeFanart(int i)
{
	// check index validity
	if (i < 0 || i >= numFanarts())
	{
		qWarning() << "MetadataHolder: Tried to remove fanart that did not exist";
		return false;
	}
	// delete the file if necessary
	if (d->fanartOwnership[i])
	{
		QDir::root().remove(d->fanartFiles[i]);
	}
	// remove the icon
	d->fanartImages.removeAt(i);
	d->fanartFiles.removeAt(i);
	d->fanartOwnership.removeAt(i);
	// remove from the config file
	d->file->removeMember({"metadata", "fanarts", "files", i});
	d->file->removeMember({"metadata", "fanarts", "owned", i});
	// change default image if necessary
	if (i == getDefaultFanartIndex())
	{
		setDefaultFanartIndex(0);
	}
	else if (i < getDefaultFanartIndex())
	{
		setDefaultFanartIndex(getDefaultFanartIndex() - 1);
	}
	// emit signals
	emit fanartRemoved(i);
	return true;
}

void MetadataHolder::addDetail(QString name, JsonValue value)
{
	if (hasDetail(name))
	{
		d->detailValues[name] = value;
		if (d->file->getMember({"metadata", "details", name}).isArray())
		{
			d->file->appendValueToMember({"metadata", "details", name}, value);
		}
		else
		{
			d->file->setMember({"metadata", "details", name}, value);	
		}
		emit detailChanged(name);
		emit detailChanged(d->detailNames.indexOf(name));
	}
	else
	{
		d->detailNames << name;
		d->file->appendValueToMember({"metadata", "details", "_order"}, name);
		d->detailValues[name] = value;
		d->file->appendValueToMember({"metadata", "details"}, name, value);
		emit detailAdded(name);
	}
}

bool MetadataHolder::removeDetail(int i)
{
	if (i < 0 || i >= numDetails())
	{
		qWarning() << "MetadataHolder: Tried to remove detail that did not exist";
		return false;
	}
	// remove the detail value
	QString name = d->detailNames[i];
	d->detailValues.remove(name);
	d->file->removeMember({"metadata", "details", name});
	// remove the detail name
	d->detailNames.removeAt(i);
	d->file->removeMember({"metadata", "details", "_order", i});
	detailRemoved(i);
	detailRemoved(name);
	return true;
}

bool MetadataHolder::removeDetail(QString name)
{
	if (!hasDetail(name))
	{
		qWarning() << "MetadataHolder: Tried to remove detail that did not exist";
		return false;
	}
	// remove the detail value
	d->detailValues.remove(name);
	d->file->removeMember({"metadata", "details", name});
	// remove the detail name
	int i = d->detailNames.indexOf(name);
	d->detailNames.removeAt(i);
	d->file->removeMember({"metadata", "details", "_order", i});
	detailRemoved(i);
	detailRemoved(name);
	return true;
}

QString MetadataHolderPrivate::stringFor(JsonValue value) const
{
	QString ans;
	JsonArray arr;
	JsonValue::Type type = value.getType();
	switch (type)
	{
		case JsonValue::String:
			return value.toString();
		case JsonValue::Number:
			return QString::number(value.toDouble());
		case JsonValue::Boolean:
			if (value.toBoolean())
			{
				return "Yes";
			}
			return "No";
		case JsonValue::Array:
			arr = value.toArray();
			if (arr.count() == 0)
			{
				return "";
			}
			ans = stringFor(((const JsonArray) arr).at(0));
			for (int i = 1; i < arr.count(); ++ i)
			{
				ans += ", " + stringFor(((const JsonArray) arr).at(i));
			}
			return ans;
		case JsonValue::Object:
			qWarning() << "MetadataHolder: Object in detail value.";
			return "";
		case JsonValue::Null:
			qWarning() << "MetadataHolder: Null value in detail value.";
			return "";
		default:
			qWarning() << "MetadataHolder: Unknown type in detail value.";
			return "";
	}
}