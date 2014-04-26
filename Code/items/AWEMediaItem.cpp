// header file
#include "AWEMediaItem.h"

// for file reading
#include "libs/generic_file_reader/file_reader.h"
#include <QTextStream>
#include <QString>

// for property parsing
#include <sstream>
#include <string>

using namespace AWE;
using namespace Json;
using namespace std;

MediaItem::MediaItem(const QDir& file) :
	myJSONFile(file)
{
	// read in the settings file
	Reader reader;
	QString contents;
	QTextStream stream(&contents);
	copyFile(file.absolutePath(), stream);
	reader.parse(contents.toStdString(), myData, false);
}

MediaItem::~MediaItem()
{
	// nothing
}

const Value& MediaItem::getData() const
{
	return myData;
}

Value& MediaItem::getData()
{
	return myData;
}

const Value& MediaItem::getMember(const QString& str) const
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	const Value* toSet = &myData;
	stringstream propParser;
	propParser << str.toStdString();
	string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

Value& MediaItem::getMember(const QString& str)
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	Value* toSet = &myData;
	stringstream propParser;
	propParser << str.toStdString();
	string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

bool MediaItem::getBoolMember(const QString& str) const
{
	return getMember(str).asBool();
}

QString MediaItem::getStringMember(const QString& str) const
{
	return getMember(str).asCString();
}

int MediaItem::getIntMember(const QString& str) const
{
	return getMember(str).asInt();
}

QString MediaItem::getName() const
{
	return getMember("metadata.name").asCString();
}

const QDir& MediaItem::getJSONFile() const
{
	return myJSONFile;
}