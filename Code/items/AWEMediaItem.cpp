// header file
#include "AWEMediaItem.h"

// for file reading
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>

AWEMediaItem::AWEMediaItem(const QDir& file) :
	myJSONFile(file)
{
	// read in the settings file
	Json::Reader reader;
	std::stringstream ss;
	copyFile(file.absolutePath().toStdString(), ss);
	reader.parse(ss.str(), myData, false);
}

AWEMediaItem::~AWEMediaItem()
{
	// nothing
}

const Json::Value& AWEMediaItem::getData() const
{
	return myData;
}

Json::Value& AWEMediaItem::getData()
{
	return myData;
}

const Json::Value& AWEMediaItem::getMember(const std::string& str) const
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	const Json::Value* toSet = &myData;
	std::stringstream propParser;
	propParser << str;
	std::string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

Json::Value& AWEMediaItem::getMember(const std::string& str)
{
	// str is of the form "object.object.object. ... .key"
	// so parse by period and delve down until you reach the end
	Json::Value* toSet = &myData;
	std::stringstream propParser;
	propParser << str;
	std::string parseResult;
	while (getline(propParser, parseResult, '.'))
	{
		toSet = &(toSet->operator[] (parseResult));
	}
	return *toSet;
}

bool AWEMediaItem::getBoolMember(const std::string& str) const
{
	return getMember(str).asBool();
}

std::string AWEMediaItem::getStringMember(const std::string& str) const
{
	return getMember(str).asString();
}

int AWEMediaItem::getIntMember(const std::string& str) const
{
	return getMember(str).asInt();
}

std::string AWEMediaItem::getName() const
{
	return getMember("metadata.name").asString();
}

const QDir& AWEMediaItem::getJSONFile() const
{
	return myJSONFile;
}