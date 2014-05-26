// header file
#include "ConfigFile.h"

// debug
#include <QtDebug>

using namespace JSON;

namespace AWE
{
	class ConfigFilePrivate
	{
		public:
			JsonValue data;
			QString configFileName;
			QDir configFilePath;
			bool edited;
			bool valid;
	};
}

using namespace AWE;

ConfigFile::ConfigFile()
	:	d(new ConfigFilePrivate)
{
	d->edited = false;
	d->valid = false;
}

ConfigFile::ConfigFile(QString file)
	:	d(new ConfigFilePrivate)
{
	// get the file
	d->configFilePath = file;
	d->configFileName = d->configFilePath.dirName();
	d->configFilePath.cdUp();

	// initialize edited/valid flags
	d->edited = false;
	d->valid = true;

	// read it in
	QFile f(file);
	if (f.open(QFile::ReadOnly))
	{
		// put it in the data
		JsonReader reader;
		JsonReaderErrors errors;
		d->data = reader.read(&f, &errors);
		if (errors.numErrors())
		{
			qWarning() << "ConfigFile: File" << file << "had errors:";
			d->valid = false;
			for (auto err : errors)
			{
				qWarning() << "\t" << err.message();
			}
			return;
		}
	}
	else
	{
		// since the file could not be opened, we will make a new one
		qWarning() << "ConfigFile: File" << file << "does not exist.";
		qWarning() << "\tThe file will be created when this object is deleted.";
		d->edited = true;
	}
}

ConfigFile::~ConfigFile()
{
	// write to file if necessary
	if (hasBeenEdited())
	{
		writeToFile();
	}
	delete d;
}

bool ConfigFile::isValid() const
{
	return d->valid;
}

QString ConfigFile::getConfigFileName() const
{
	return d->configFileName;
}

QDir ConfigFile::getPathToConfigFile() const
{
	return d->configFilePath;
}

bool ConfigFile::hasBeenEdited() const
{
	return d->edited;
}

void ConfigFile::markAsEdited()
{
	// editing only matters if there is a file
	if (!getConfigFileName().isNull())
	{
		d->edited = true;
	}
}

void ConfigFile::writeToFile()
{
	if (getConfigFileName().isNull())
	{
		// we don't want to write to nonexistant files
		return;
	}
	JsonWriter writer(d->data);
	QString file = getPathToConfigFile()
		.absoluteFilePath(getConfigFileName());
	QFile outputFile(file);
	if (outputFile.open(QFile::WriteOnly))
	{
		writer.writeTo(&outputFile);
	}
	else
	{
		qWarning() << "ConfigFile: Could not write to file"
			<< file;
	}
}

JsonValue ConfigFile::getData() const
{
	return d->data;
}

void ConfigFile::setData(JsonValue data)
{
	d->data = data;
	markAsEdited();
	emit dataChanged();
}

JsonValue ConfigFile::getMember(JsonPath path) const
{
	return d->data.follow(path);
}

bool ConfigFile::setMember(JsonPath path, JsonValue value)
{
	bool ok;
	JsonValue* toSet = &d->data.follow(path, &ok);
	if (ok)
	{
		toSet->operator= (value);
		markAsEdited();
		emit dataChanged();
		return true;
	}
	return false;
}

bool ConfigFile::appendValueToMember(JsonPath path, JsonValue value)
{
	bool ok;
	JsonValue* toEdit = &d->data.follow(path, &ok);
	if (ok)
	{
		if (toEdit->isNull())
		{
			toEdit->setType(JsonValue::Array);
		}
		if (toEdit->isArray())
		{
			toEdit->toArray().append(value);
			markAsEdited();
			emit dataChanged();
			return true;
		}
	}
	return false;
}

bool ConfigFile::appendValueToMember(JsonPath path, QString key, JsonValue value)
{
	bool ok;
	JsonValue* toEdit = &d->data.follow(path, &ok);
	if (ok)
	{
		if (toEdit->isNull())
		{
			toEdit->setType(JsonValue::Object);
		}
		if (toEdit->isObject())
		{
			toEdit->toObject().get(key) = value;
			markAsEdited();
			emit dataChanged();
			return true;
		}
	}
	return false;
}

bool ConfigFile::removeMember(JsonPath path)
{
	if (!path.length())
	{
		setData(JsonValue::Null);
		return true;
	}
	bool ok;
	JsonValue* toEdit = &d->data.follow(path.trimmed(0, path.length() - 1), &ok);
	if (ok)
	{
		JsonKey key = path.last();
		if (toEdit->isObject() && key.isObjectKey())
		{
			if (toEdit->toObject().remove(key.toObjectKey()))
			{
				markAsEdited();
				emit dataChanged();
				return true;
			}
		}
		else if (toEdit->isArray() && key.isArrayIndex())
		{
			if (toEdit->toArray().remove(key.toArrayIndex()))
			{
				markAsEdited();
				emit dataChanged();
				return true;
			}
		}
	}
	return false;
}

bool ConfigFile::addMember(JsonPath path, JsonValue value)
{
	if (!path.length())
	{
		setData(value);
		return true;
	}
	bool ok;
	JsonValue* toEdit = &d->data.create(path, &ok);
	if (ok)
	{
		toEdit->operator= (value);
		markAsEdited();
	}
	return ok;
}