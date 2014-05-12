// class header
#include "AWEJSONScraper.h"

// for reading and writing
#include "libs/generic_file_reader/file_reader.h"
#include <iostream>
#include <fstream>

// for item creation
#include "items/AWEMediaFile.h"
#include "items/AWEFolder.h"
#include <QChar>

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace Json;
using namespace std;

JSONScraper::JSONScraper(QString name,
		QString type) :
	myValidity(false),
	myName(name),
	myType(type),
	myCurrentFile(0)
	{ }

bool JSONScraper::prepare(GlobalSettings* settings)
{
	myGlobalSettings = settings;
	// get the scraper and default props
	myScraper = settings->getScraperSettingsByName(myName);
	myDefaultProperties = settings->getTypeByName(myType);
	// get the inherited metadata props
	for (auto prop : myScraper["inherited metadata"].getMemberNames())
	{
		myInheritedProperties[prop.data()] 
			= myScraper["inherited metadata"][prop.data()].asCString();
	}
	// get the file props
	for (auto prop : myScraper["force copy"])
	{
		myFileProperties << prop.asCString();
	}
	for (auto prop : myScraper["copy"])
	{
		myFileProperties << prop.asCString();
	}
	// check validity
	myValidity = checkValidity();
	return myValidity;
}

bool JSONScraper::scrapeDataForFile(MediaItem* file,
	bool askUser, bool import, bool inheritMetadata)
{
	// get the containing folder
	if (file->getItemType() == FOLDER_TYPE)
	{
		QDir folder = file->getConfigFile().absolutePath();
		folder.cdUp();
		folder.cdUp();
		folder = folder.absoluteFilePath("config.json");
		myCurrentFolder = (Folder*) myGlobalSettings->getMediaItemByJSONFile(folder);
	}
	else
	{
		QDir folder = file->getConfigFile().absolutePath();
		folder.cdUp();
		folder = folder.absoluteFilePath("config.json");
		myCurrentFolder = (Folder*) myGlobalSettings->getMediaItemByJSONFile(folder);
	}
	// check validity
	if (!isValid())
	{
		DEBUG_ERR("ERROR: Scraper \"" << getName().toStdString() << "\" not valid")
		return false;
	}

	// reset to defaults
	QString locationValue = file->getStringMember("metadata.location");
	file->getMember("metadata") = myDefaultProperties;
	file->getMember("metadata.location") = locationValue.toStdString();

	// get the filename regex
	myCurrentFile = file;
	QString temp = myCurrentFile->getStringMember("metadata.location");
	QRegularExpression fileNameRegex(myScraper["filename"].asCString());

	// get the matches for the filename
	QList<QRegularExpressionMatch> matches;
	if (myScraper["multiple items per file"].asBool())
	{
		auto matchIter = fileNameRegex.globalMatch(temp);
		while (matchIter.hasNext())
		{
			matches << matchIter.next();
		}
	}
	else
	{
		QRegularExpressionMatch m = fileNameRegex.match(temp);
		if (m.isValid())
		{
			matches << m;
		}
	}

	// check for matching error
	if (matches.count() == 0)
	{
		DEBUG_ERR("File \"" << temp.toStdString() << "\" does not match")
		return false;
	}

	// get the match that we care about
	QRegularExpressionMatch matchWeCareAbout = matches[0];
	if (matches.count() > 1)
	{
		// TODO prompt user
	}

	// run through the procedures, noting issues
	bool procsSucceeded = true;
	for (uint i = 0; i < myScraper["procedures"].size(); ++ i)
	{
		procsSucceeded = procsSucceeded 
			&& executeProcedure(myScraper["procedures"][i], matchWeCareAbout,
				askUser, import, inheritMetadata);
	}

	// import files
	importFiles(myScraper["force copy"]);
	if (import)
	{
		importFiles(myScraper["copy"]);
	}

	// write out the config file
	ofstream out(file->getConfigFile().absolutePath().toStdString());
	out << myCurrentFile->getData();

	// reset the file variable
	myCurrentFile = nullptr;
	myCurrentFolder = nullptr;

	// return the success/failure
	return procsSucceeded;
}

QList<MediaItem*> JSONScraper::scrapeDataForFile(Folder* placeInMe,
	GlobalSettings* globalSettings, QDir file,
	bool askUser, bool import, bool inheritMetadata)
{
	myCurrentFolder = placeInMe;

	// check validity
	if (!isValid())
	{
		DEBUG_ERR("ERROR: Scraper \"" << getName().toStdString() << "\" not valid")
		return QList<MediaItem*>();
	}

	// get the filename regex
	QString temp = file.absolutePath();
	QRegularExpression fileNameRegex(myScraper["filename"].asCString());

	// get the matches for the filename
	QList<QRegularExpressionMatch> matches;
	if (myScraper["multiple items per file"].asBool())
	{
		auto matchIter = fileNameRegex.globalMatch(temp);
		while (matchIter.hasNext())
		{
			matches << matchIter.next();
		}
	}
	else
	{
		QRegularExpressionMatch m = fileNameRegex.match(temp);
		if (m.isValid())
		{
			matches << m;
		}
	}

	// ans list
	QList<MediaItem*> ans;

	// check for matching error
	if (matches.count() == 0)
	{
		DEBUG_ERR("File \"" << temp.toStdString() << "\" does not match")
		return ans;
	}

	for (int i = 0; i < matches.count(); ++ i)
	{
		// get the folder to put the JSON file in
		QDir folderPath = placeInMe->getConfigFile();
		folderPath.cdUp();

		// make the folder if necessary
		if (myScraper["type"] == "folder")
		{
			folderPath.mkdir(matches[i].captured(0));
		}

		// get the JSON file name
		QDir jsonFile = folderPath;
		jsonFile = QDir(jsonFile.absolutePath() + "/" + matches[i].captured(0));

		// make the item
		if (myScraper["type"] == "file")
		{
			jsonFile = QDir(jsonFile.absolutePath() + ".json");
			myCurrentFile = new MediaFile(jsonFile);
		}
		else if (myScraper["type"] == "folder")
		{
			jsonFile = QDir(jsonFile.absolutePath() + "/config.json");
			myCurrentFile = new Folder(jsonFile);
		}

		// make sure it knows its media file location
		myCurrentFile->getMember("metadata") = myDefaultProperties;
		myCurrentFile->getMember("metadata.location")
			= folderPath.relativeFilePath(file.absolutePath()).toStdString();

		// run through the procedures, noting issues
		bool procsSucceeded = true;
		for (uint j = 0; j < myScraper["procedures"].size(); ++ j)
		{
			procsSucceeded = procsSucceeded 
				&& executeProcedure(myScraper["procedures"][j], matches[i],
					askUser, import, inheritMetadata);
		}

		// import files
		importFiles(myScraper["force copy"]);
		if (import)
		{
			importFiles(myScraper["copy"]);
		}

		// add the item to the list
		ans.append(myCurrentFile);

		// add the item to the folder
		placeInMe->addItem(myCurrentFile);

		// add the item to the global settings
		globalSettings->addItem(myCurrentFile);

		// write out the config file
		ofstream out(jsonFile.absolutePath().toStdString());
		out << myCurrentFile->getData();
	}

	// reset the file variable
	myCurrentFile = nullptr;
	myCurrentFolder = nullptr;

	// return the list
	return ans;
}

bool JSONScraper::executeProcedure(Value& procedure, QRegularExpressionMatch backrefs,
	bool askUser, bool import, bool inheritMetadata)
{
	// get the file to look in and what to look for
	QString lookInFile = procedure["look in file"].asCString();
	QString lookFor = procedure["for"].asCString();

	// replace backrefs
	replaceBackrefs(lookInFile, backrefs);
	replaceBackrefs(lookFor, backrefs);

	// get the contents of the file
	QString fileContents = getFileContents(lookInFile);

	// get the regex
	QRegularExpression forRegex(lookFor);

	// get the matches
	QList<QRegularExpressionMatch> matches;
	if (procedure["repeat"].asBool()
		|| procedure["ask user"].asString() != "")
	{
		// repetitive or user-prompting, so get all of them
		auto matchIter = forRegex.globalMatch(fileContents);
		while (matchIter.hasNext())
		{
			matches << matchIter.next();
		}
	}
	else
	{
		// not repetitive and user is not prompted, so get first
		QRegularExpressionMatch m = forRegex.match(fileContents);
		if (m.capturedRef().count() != 0)
		{
			matches << m;
		}
	}

	// no matches is an error
	if (matches.count() == 0)
	{
		DEBUG_ERR("ERROR: No matches for \"" << lookFor.toStdString() << "\" in "
						<< lookInFile.toStdString())
		DEBUG_ERR(fileContents.toStdString())
		return false;
	}

	// TODO user prompting
	if (!procedure["repeat"].asBool())
	{
		QList<QRegularExpressionMatch> newMatches;
		newMatches << matches[0];
		newMatches.swap(matches);
	}

	// run for every match
	bool procsSucceeded = true;
	for (auto i : matches)
	{
		procsSucceeded = procsSucceeded
			&& useMatchForProcedure(procedure, i,
				askUser, import, inheritMetadata);
	}

	// TODO import

	// return success/failure
	return procsSucceeded;
}

bool JSONScraper::useMatchForProcedure(Value& procedure, QRegularExpressionMatch backrefs,
	bool askUser, bool import, bool inheritMetadata)
{
	bool procsSucceeded = true;

	// apply to the properties in this procedure
	Value::Members mems = procedure["set properties"].getMemberNames();
	for (auto prop : mems)
	{
		// if we are not inheriting or, if we are, it isn't supposed to be
		// anyway
		if (!inheritMetadata || !myInheritedProperties.contains(prop.data()))
		{
			DEBUG_OUT("Setting property \"" << prop << "\"")
			// determine what type it is
			Value valueToSet;
			if (procedure["set properties"][prop].isString()) // string implies backrefs
			{
				// replace backrefs in the value
				QString temp = procedure["set properties"][prop].asCString();
				replaceBackrefs(temp, backrefs);
				valueToSet = temp.toStdString();
				DEBUG_OUT("To " << temp.toStdString())
			}
			else
			{
				valueToSet = procedure["set properties"][prop];
				DEBUG_OUT("To " << valueToSet)
			}

			// parse the property name to delve down objects
			Value* toSet = &(myCurrentFile->getMember(
									"metadata." + QString(prop.c_str())));

			// set the object in the appropriate way
			if (toSet->isArray())
			{
				// append to the array
				toSet->append(valueToSet);
			}
			else if (toSet->isInt() && valueToSet.isString())
			{
				// make sure to set to int interpretation
				toSet->operator= (QString(valueToSet.asCString()).toInt());
			}
			else if (toSet->isBool() && valueToSet.isString())
			{
				// make sure to set to bool cast of int interpretation
				toSet->operator= ((bool) QString(valueToSet.asCString()).toInt());
			}
			else // something else
			{
				// replace the current value
				toSet->operator= (valueToSet);
			}
		}
		else // inherit from the containing folder
		{
			// if it is a file property and this is a folder
			if (myFileProperties.contains(prop.data())
				&& myCurrentFile->getItemType() == FOLDER_TYPE)
			{
				myCurrentFile->getMember(QString("metadata.") + prop.data())
					= "../" + myCurrentFolder->getMember("metadata." 
										+ myInheritedProperties[prop.data()]).asString();
			}
			else
			{
				myCurrentFile->getMember(QString("metadata.") + prop.data())
					= myCurrentFolder->getMember("metadata." 
										+ myInheritedProperties[prop.data()]);
			}
		}
	}

	// apply to the sub procedures
	for (uint j = 0; j < procedure["procedures"].size(); ++ j)
	{
		procsSucceeded = procsSucceeded 
			&& executeProcedure(procedure["procedures"][j],
				backrefs, askUser, import, inheritMetadata);
	}

	return procsSucceeded;
}

void JSONScraper::importFiles(Value& props)
{
	for (auto str : props)
	{
		// get the base of the file name
		QString prop = str.asCString();
		QString fileName = myCurrentFile->getConfigFile().dirName()
							+ ".metadata." + prop;
		// get the member to set
		Json::Value& temp = myCurrentFile->getMember("metadata." + prop);
		// if it is an array
		if (temp.isArray())
		{
			for (uint j = 0; j < temp.size(); ++ j)
			{
				// get the file extension
				QString extension = temp[j].asCString();
				extension.replace(0, extension.lastIndexOf("."), "");
				// the file name is item_json_file.array_prop_path.#.extension
				// located in the folder with the JSON file
				QDir pathToNewFile(myCurrentFile->getConfigFile().absolutePath());
				pathToNewFile.cdUp();
				pathToNewFile = pathToNewFile.absoluteFilePath(fileName + "."
									+ QString::number(j) + extension);
				QFile writeToMe(pathToNewFile.absolutePath());
				if (writeToMe.open(QFile::WriteOnly))
				{
					// copy the file
					copyFile(temp[j].asCString(), writeToMe);
					// change the property value
					DEBUG_OUT(temp[j].asCString() << " -> " 
						<< pathToNewFile.dirName().toStdString())
					temp[j] = pathToNewFile.dirName().toStdString();
				}
				writeToMe.close();
			}
		}
		// just a single file string
		else if (temp.isString())
		{
			// get the file extension
			QString extension = temp.asCString();
			extension.replace(0, extension.lastIndexOf("."), "");
			// the file name is item_json_file.array_prop_path.#.extension
			// located in the folder with the JSON file
			QDir pathToNewFile(myCurrentFile->getConfigFile().absolutePath());
			pathToNewFile.cdUp();
			pathToNewFile = pathToNewFile.absoluteFilePath(fileName + "." + extension);
			QFile writeToMe(pathToNewFile.absolutePath());
			if (writeToMe.open(QFile::WriteOnly))
			{
				// copy the file
				copyFile(temp.asCString(), writeToMe);
				// change the property value
				DEBUG_OUT(temp.asCString() << " -> " 
					<< pathToNewFile.dirName().toStdString())
				temp = pathToNewFile.dirName().toStdString();
			}
		}
	}
}

void JSONScraper::deactivate()
{
	myScraper = Value::null;
	myDefaultProperties = Value::null;
	myGlobalSettings = nullptr;
}

int JSONScraper::replaceBackrefs(QString& pseudo_reg, 
		QRegularExpressionMatch backrefs)
{
	int max = -1;
	int i = pseudo_reg.indexOf("$");
	while (i >= 0 && i < pseudo_reg.count() - 1)
	{
		if (pseudo_reg[i + 1] == '$') // "$$"
		{
			// actually just want a $
			pseudo_reg.replace(i, 2, "$");
			++ i;
		}
		else // backref, "$#""
		{
			int c = pseudo_reg[i + 1].toLatin1() - '0';
			// change the max backref (for validity check)
			if (c > max)
			{
				max = c;
			}
			pseudo_reg.replace(i, 2, backrefs.captured(c));
			i += backrefs.captured(c).count();
		}
		i = pseudo_reg.indexOf("$", i);
	}
	return max;
}

QString& JSONScraper::getFileContents(QString file)
{
	if (!myMetadataFiles.contains(file))
	{
		QTextStream stream(&myMetadataFiles[file]);
		copyFile(file, stream);
	}
	return myMetadataFiles[file];
}

bool JSONScraper::isValid()
{
	return myValidity;
}

bool JSONScraper::checkValidity()
{
	// if true, we assume its good
	if (myValidity)
	{
		return true;
	}

	// doesn't have the necessary tags
	if (!myScraper.isMember("filename") || !myScraper["filename"].isString()
		|| !myScraper.isMember("multiple items per file")
			|| !myScraper["multiple items per file"].isBool()
		|| !myScraper.isMember("inherited metadata")
			|| !myScraper["inherited metadata"].isObject()
		|| !myScraper.isMember("procedures") || !myScraper["procedures"].isArray()
		|| !myScraper.isMember("force copy") || !myScraper["force copy"].isArray()
		|| !myScraper.isMember("copy") || !myScraper["copy"].isArray())
	{
		DEBUG_ERR("Missing tags")
		return false;
	}

	// check regex validity
	QRegularExpression regex(myScraper["filename"].asCString());
	if (!regex.isValid())
	{
		DEBUG_ERR("Regex \"" << regex.pattern().toStdString() << "\" Invalid")
		return false;
	}

	// check each procedure
	for (uint i = 0; i < myScraper["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(myScraper["procedures"][i], regex.captureCount()))
		{
			// bad procedure
			return false;
		}
	}

	// all is well
	return true;
}

bool JSONScraper::checkProcedureValidity(Value& procedure, int capCount)
{
	// doesn't have the necessary tags
	if (!procedure.isMember("repeat") || !procedure["repeat"].isBool()
		|| !procedure.isMember("ask user") || !procedure["ask user"].isString()
		|| !procedure.isMember("look in file") || !procedure["look in file"].isString()
		|| !procedure.isMember("for") || !procedure["for"].isString()
		|| !procedure.isMember("set properties")
			|| !procedure["set properties"].isObject()
		|| !procedure.isMember("procedures") || !procedure["procedures"].isArray())
	{
		DEBUG_ERR("Missing tags")
		return false;
	}

	/* check regex validity */
	QString pattern = procedure["look in file"].asCString();
	// check backref replace for "look in file"
	if (replaceBackrefs(pattern, QRegularExpressionMatch()) > capCount)
	{
		DEBUG_ERR("Backref pattern \"" << pattern.toStdString() << "\" Invalid")
		return false;
	}
	// check backref replace for "for"
	pattern = procedure["for"].asCString();
	if (replaceBackrefs(pattern, QRegularExpressionMatch()) > capCount)
	{
		DEBUG_ERR("Backref pattern \"" << pattern.toStdString() << "\" Invalid")
		return false;
	}
	// check regex for "for"
	QRegularExpression regex(pattern);
	if (!regex.isValid())
	{
		DEBUG_ERR("Regex \"" << regex.pattern().toStdString() << "\" Invalid")
		return false;
	}
	// check backref replace for "ask user"
	pattern = procedure["ask user"].asCString();
	if (replaceBackrefs(pattern, QRegularExpressionMatch()) > regex.captureCount())
	{
		DEBUG_ERR("Backref pattern \"" << pattern.toStdString() << "\" Invalid")
	}
	// check backref replace for each property set
	for (auto str : procedure["set properties"].getMemberNames())
	{
		if (!procedure["set properties"][str].isString())
		{
			continue;
		}
		pattern = procedure["set properties"][str].asCString();
		if (replaceBackrefs(pattern, QRegularExpressionMatch()) > regex.captureCount())
		{
			DEBUG_ERR("Setting \"" << str << "\"")
			DEBUG_ERR("Backref pattern \"" << pattern.toStdString() << "\" Invalid")
			return false;
		}
	}

	/* check each sub procedure */
	for (uint i = 0; i < procedure["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(procedure["procedures"][i], regex.captureCount()))
		{
			// bad procedure
			return false;
		}
	}

	// all is well
	return true;
}

QString JSONScraper::getName()
{
	return myName;
}

QString JSONScraper::getType()
{
	return myType;
}