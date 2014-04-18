// header file
#include "AWEMediaItem.h"

// for file reading
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>

using namespace AWE;
using namespace Json;
using namespace std;

MediaItem::MediaItem(const QDir& file) :
	myJSONFile(file)
{
	// read in the settings file
	Reader reader;
	std::stringstream ss;
	copyFile(file.absolutePath().toStdString(), ss);
	reader.parse(ss.str(), myData, false);
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

const Value& MediaItem::getMember(const std::string& str) const
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	const Value* toSet = &myData;
	std::stringstream propParser;
	propParser << str;
	std::string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

Value& MediaItem::getMember(const std::string& str)
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	Value* toSet = &myData;
	std::stringstream propParser;
	propParser << str;
	std::string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

bool MediaItem::getBoolMember(const std::string& str) const
{
	return getMember(str).asBool();
}

std::string MediaItem::getStringMember(const std::string& str) const
{
	return getMember(str).asString();
}

int MediaItem::getIntMember(const std::string& str) const
{
	return getMember(str).asInt();
}

std::string MediaItem::getName() const
{
	return getMember("metadata.name").asString();
}

const QDir& MediaItem::getJSONFile() const
{
	return myJSONFile;
}