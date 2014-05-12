// header file
#include "ConfigFile.h"

// for reading/writing data
#include "libs/generic_file_reader/file_reader.h"
#include <iostream>
#include <fstream>
#include <string>

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace Json;
using namespace std;

ConfigFile::ConfigFile()
	:	QObject(),
		myConfigFileName(),
		myPathToConfigFile(),
		myData(),
		myEditedFlag(false),
		myValidity(false)
	{ }

ConfigFile::ConfigFile(QString file)
	:	QObject(),
		myConfigFileName(),
		myPathToConfigFile(file),
		myData(),
		myEditedFlag(false),
		myValidity(true)
{
	// get the file
	myConfigFileName = myPathToConfigFile.dirName();
	myPathToConfigFile.cdUp();

	// read it in
	QString contents;
	QTextStream writer(&contents, QFile::WriteOnly);
	if (copyFile(file, writer))
	{
		// put it in the data
		Reader reader;
		if (!reader.parse(contents.toStdString(), myData, false))
		{
			myValidity = false;
			DEBUG_ERR("ERROR: File \"" << file.toStdString() << "\" has error "
						<< error.errorString() << " at offset " << error.offset)
			return;
		}
	}
	else
	{
		// since the file could not be opened, we will make a new one
		DEBUG_WARN("WARNING: File \"" << file.toStdString() << "\" does not exist.")
		DEBUG_WARN("\tThe file will be created.")
		myEditedFlag = true;
	}
}

ConfigFile::~ConfigFile()
{
	// write to file if necessary
	if (hasBeenEdited())
	{
		writeToFile();
	}
}

bool ConfigFile::isValid() const
{
	return myValidity;
}

QString ConfigFile::getConfigFileName() const
{
	return myConfigFileName;
}

QDir ConfigFile::getPathToConfigFile() const
{
	return myPathToConfigFile;
}

bool ConfigFile::hasBeenEdited() const
{
	return myEditedFlag;
}

void ConfigFile::markAsEdited()
{
	// editing only matters if there is a file
	if (!myConfigFileName.isNull())
	{
		myEditedFlag = true;
	}
}

void ConfigFile::writeToFile()
{
	if (myConfigFileName.isNull())
	{
		return;
	}
	string file = myPathToConfigFile.absoluteFilePath(myConfigFileName)
					.toStdString();
	ofstream out(file);
	if (out)
	{
		out << myData;
	}
	else
	{
		DEBUG_ERR("ERROR: Could not write to file \""
					<< file.toStdString() << "\"")
	}
}

const Value& ConfigFile::getData() const
{
	return myData;
}

void ConfigFile::setData(const Value& data)
{
	myData = data;
	markAsEdited();
	emit dataChanged();
}

const Value& ConfigFile::getMember(JsonPath path) const
{
	return path.followConst(myData);
}

bool ConfigFile::setMember(JsonPath path, const Value& value)
{
	Value* toSet = &path.follow(myData);
	if (toSet->isNull())
	{
		return false;
	}
	toSet->operator= (value);
	return true;
}

bool ConfigFile::appendValueToMember(JsonPath path, const Value& value)
{
	Value* toChange = &path.follow(myData);
	if (toChange->isNull() || !toChange->isArray())
	{
		return false;
	}
	toChange->append(value);
	return true;
}

bool ConfigFile::appendValueToMember(JsonPath path, QString key, const Value& value)
{
	Value* toChange = &path.follow(myData);
	if (toChange->isNull() || !toChange->isObject())
	{
		return false;
	}
	toChange->operator[] (key.toStdString()) = value;
	return true;
}