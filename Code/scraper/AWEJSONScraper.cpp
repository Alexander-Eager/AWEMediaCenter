// class header
#include "AWEJSONScraper.h"

// for reading and writing
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>
#include <iostream>

// for item creation
#include "items/AWEMediaFile.h"
#include "items/AWEFolder.h"

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace Json;

JSONScraper::JSONScraper(const QString& name,
		const QString& type) :
	myValidity(false),
	myName(name),
	myType(type),
	myCurrentFile(0)
	{ }

bool JSONScraper::prepare(GlobalSettings* settings)
{
	myScraper = settings->getScraperSettingsByName(myName);
	myDefaultProperties = settings->getTypeByName(myType)["metadata"];
	myValidity = checkValidity();
	return myValidity;
}

bool JSONScraper::scrapeDataForFile(MediaItem* file,
	bool askUser, bool import, bool inheritMetadata)
{
	// check validity
	if (!isValid())
	{
		DEBUG(qDebug() << "Scraper \"" << getName() << "\" not valid";)
		return false;
	}

	// get the filename regex
	myCurrentFile = file;
	QString temp = myCurrentFile->getStringMember("metadata.location");
	QRegExp fileNameRegex(myScraper["filename"].asCString());

	// get the matches for the filename
	QList<QRegExp> matches;
	if (myScraper["multiple items per file"].asBool())
	{
		int loc = 0;
		while ((loc = fileNameRegex.indexIn(temp, 0)) != -1)
		{
			matches << fileNameRegex;
		}
	}
	else
	{
		if (fileNameRegex.indexIn(temp) != -1)
		{
			matches << fileNameRegex;
		}
	}

	// check for matching error
	if (matches.count() == 0)
	{
		DEBUG(qDebug() << "File \"" << temp << "\" does not match";)
		return false;
	}

	// get the match that we care about
	QRegExp matchWeCareAbout = matches[0];
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

	// reset the file variable
	myCurrentFile = nullptr;

	// return the success/failure
	return procsSucceeded;
}

QList<MediaItem*> JSONScraper::scrapeDataForFile(Folder* placeInMe,
	GlobalSettings* globalSettings, const QDir& file,
	bool askUser, bool import, bool inheritMetadata)
{
	// check validity
	if (!isValid())
	{
		DEBUG(qDebug() << "Scraper \"" << getName() << "\" not valid";)
		return QList<MediaItem*>();
	}

	// get the filename regex
	QRegExp fileNameRegex(myScraper["filename"].asCString());
	QString temp = file.absolutePath();

	// get the matches for the filename
	QList<QRegExp> matches;
	if (myScraper["multiple items per file"].asBool())
	{
		int loc = 0;
		while ((loc = fileNameRegex.indexIn(temp, 0)) != -1)
		{
			matches << fileNameRegex;
		}
	}
	else
	{
		if (fileNameRegex.indexIn(temp) != -1)
		{
			matches << fileNameRegex;
		}
	}

	// ans list
	QList<MediaItem*> ans;

	// check for matching error
	if (matches.count() == 0)
	{
		DEBUG(qDebug() << "File \"" << temp << "\" does not match";)
		return ans;
	}

	for (int i = 0; i < matches.count(); ++ i)
	{
		// get the folder to put the JSON file in
		QDir folderPath = placeInMe->getJSONFile();
		folderPath.cdUp();

		// make the folder if necessary
		if (myScraper["type"] == "folder")
		{
			folderPath.mkdir(matches[i].cap(0));
		}

		// get the JSON file name
		QDir jsonFile = folderPath;
		jsonFile = QDir(jsonFile.absolutePath() + "/" + matches[i].cap(0));

		// make the item
		if (myScraper["type"] == "file")
		{
			jsonFile = QDir(jsonFile.absolutePath() + ".json");
			myCurrentFile = new MediaFile(jsonFile, globalSettings);
		}
		else if (myScraper["type"] == "folder")
		{
			jsonFile = QDir(jsonFile.absolutePath() + "/config.json");
			myCurrentFile = new Folder(jsonFile, globalSettings);
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

		// add the item to the list
		ans.append(myCurrentFile);

		// add the item to the folder
		placeInMe->addItem(myCurrentFile);

		// add the item to the global settings
		globalSettings->addItem(myCurrentFile);
	}

	// reset the file variable
	myCurrentFile = nullptr;

	// return the list
	return ans;
}

bool JSONScraper::executeProcedure(Value& procedure, QRegExp& backrefs,
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
	QRegExp forRegex(lookFor);

	// get the matches
	QList<QRegExp> matches;
	if (procedure["repeat"].asBool()
		|| procedure["ask user"].asString() != "")
	{
		// repetitive or user-prompting, so get all of them
		int loc = 0;
		while ((loc = forRegex.indexIn(fileContents, loc)) != -1)
		{
			matches << forRegex;
		}
	}
	else
	{
		// not repetitive and user is not prompted, so get first
		if (forRegex.indexIn(fileContents) != -1)
		{
			matches << forRegex;
		}
	}

	// no matches is an error
	if (matches.count() == 0)
	{
		return false;
	}

	// TODO user prompting

	// if there is only one accepted match, just use that one
	if (matches.count() == 1)
	{
		return useMatchForProcedure(procedure, matches[0], 
			askUser, import, inheritMetadata);
	}

	// multiple matches -> run many times
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

bool JSONScraper::useMatchForProcedure(Value& procedure,
	QRegExp& backrefs, bool askUser, bool import, bool inheritMetadata)
{
	bool procsSucceeded = true;

	// apply to the properties in this procedure
	Value::Members mems = procedure["set properties"].getMemberNames();
	for (auto prop : mems)
	{
		// determine what type it is
		Value valueToSet;
		if (procedure["set properties"][prop].isString()) // string implies backrefs
		{
			// replace backrefs in the value
			QString temp = procedure["set properties"][prop].asCString();
			replaceBackrefs(temp, backrefs);
			valueToSet = temp.toStdString();
		}
		else
		{
			valueToSet = procedure["set properties"][prop];
		}

		// parse the property name to delve down objects
		Value* toSet = &(myCurrentFile->getMember(
								"metadata." + QString(prop.c_str()));

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

	// apply to the sub procedures
	for (unsigned int j = 0; j < procedure["procedures"].size(); ++ j)
	{
		procsSucceeded = procsSucceeded 
			&& executeProcedure(procedure["procedures"][j],
				backrefs, askUser, import, inheritMetadata);
	}

	return procsSucceeded;
}

void JSONScraper::deactivate()
{
	myScraper = Value::null;
	myDefaultProperties = Value::null;
}

void JSONScraper::replaceBackrefs(QString& pseudo_reg, 
	const QRegExp& backrefs)
{
	int i = 0;
	while (i < pseudo_reg.count())
	{
		if (pseudo_reg[i] == '$')
		{
			if (pseudo_reg[i + 1] == '$')
			{
				// actually just want a $
				pseudo_reg = pseudo_reg.replace(i, 2, "$");
				++ i;
			}
			else
			{
				// backref
				uint c = pseudo_reg[i + 1].unicode() - '0';
				pseudo_reg = pseudo_reg.replace(i, 2, backrefs.cap(c));
				i += backrefs.cap(c).count();
			}
		}
		else
		{
			++ i;
		}
	}
}

QString& JSONScraper::getFileContents(const QString& file)
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
			|| !myScraper["multpe items per file"].isBool()
		|| !myScraper.isMember("inherited metadata")
			|| !myScraper["inherited metadata"].isObject()
		|| !myScraper.isMember("procedures") || !myScraper["procedures"].isArray()
		|| !myScraper.isMember("force copy") || !myScraper["force copy"].isArray()
		|| !myScraper.isMember("copy") || !myScraper["copy"].isArray())
	{
		return false;
	}

	// check regex validity
	QRegExp regex(myScraper["filename"].asCString());
	if (!regex.isValid())
	{
		return false;
	}

	// check each procedure
	for (uint i = 0; i < myScraper["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(myScraper["procedures"][i]))
		{
			// bad procedure
			return false;
		}
	}

	// all is well
	return true;
}

bool JSONScraper::checkProcedureValidity(Value& procedure)
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
		return false;
	}

	// check regex validity
	QString pseudo_reg = myScraper["look in file"].asCString();
	for (int i = 0; i < pseudo_reg.count(); ++ i)
	{
		if (pseudo_reg[i] == '$')
		{
			if (i > pseudo_reg.count())
			{
				return false;
			}
			if (pseudo_reg[i + 1] != '$'
				&& (pseudo_reg[i + 1] > '9'
					|| pseudo_reg[i + 1] < '0')
				)
			{
				return false;
			}
		}
	}
	pseudo_reg = myScraper["for"].asCString();
	// todo
	QRegExp regex(myScraper["for"].asCString());
	if (!regex.isValid())
	{
		return false;
	}

	// check each sub procedure
	for (uint i = 0; i < procedure["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(procedure["procedures"][i]))
		{
			// bad procedure
			return false;
		}
	}

	// all is well
	return true;
}

const QString& JSONScraper::getName()
{
	return myName;
}

const QString& JSONScraper::getType()
{
	return myType;
}