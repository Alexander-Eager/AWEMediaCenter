// class header
#include "AWEGlobalSettings.h"

// the types that are held inside AWEGlobalSettings

// scrapers
#include "scraper/AWEMetadataScraper.h"
#include "scraper/AWEJSONScraper.h"

// players
#include "player/AWEMediaPlayer.h"
#include "player/AWEJSONPlayer.h"

// items
#include "items/AWEMediaItem.h"
#include "items/AWEMediaFile.h"
#include "items/AWEFolder.h"
#include "items/AWEMediaService.h"
#include "items/AWEJSONService.h"

// for traversing paths
#include <QDir>
#include <QStringList>
#include <QString>

// for reading files
#include "libs/generic_file_reader/file_reader.h"
#include <iostream>
#include <sstream>

Json::Value AWEGlobalSettings::null = Json::Value::null;

AWEGlobalSettings::AWEGlobalSettings(const std::string& settingsFile)
{
	// TODO make safe
	std::stringstream ss;
	copyFile(settingsFile, ss);
	Json::Reader reader;
	reader.parse(ss.str(), mySettingsFile, false);

	// get all of the objects
	obtainScrapers();
	obtainPlayers();
	obtainSkins();
	obtainTypes();
	obtainServices();
	obtainItems();
}

AWEGlobalSettings::~AWEGlobalSettings()
{
	for (auto i : myMediaPlayers)
	{
		delete i.second;
	}
	for (auto i : myMetadataScrapers)
	{
		delete i.second;
	}
	for (auto i : myMediaItems)
	{
		delete i.second;
	}
}

void AWEGlobalSettings::obtainScrapers()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["scrapers"].asCString());

	// important variables
	Json::Reader reader;
	Json::Value scraper;
	std::string name, type, file;
	std::stringstream contents;

	// get all of the JSON scrapers
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]).toStdString();
		copyFile(file, contents);
		if (reader.parse(contents.str(), 
							scraper, false))
		{
			name = scraper["name"].asString();
			type = scraper["type"].asString();
			myMetadataScraperNames.insert(name);
			myMetadataScraperSettings[name] = scraper;
			myMetadataScrapers[name] = new AWEJSONScraper(name, type);
		}
		contents.clear();
	}

	// TODO plugins
}

void AWEGlobalSettings::obtainPlayers()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["players"].asCString());

	// important variables
	Json::Reader reader;
	Json::Value player;
	std::string name, file;
	std::stringstream contents;

	// get all of the JSON players
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]).toStdString();
		copyFile(file, contents);
		if (reader.parse(contents.str(),
							player, false))
		{
			name = player["name"].asString();
			myMediaPlayerNames.insert(name);
			myMediaPlayerSettings[name] = player;
			myMediaPlayers[name] = new AWEJSONPlayer(player);
		}
		contents.clear();
	}

	// TODO plugins
}

void AWEGlobalSettings::obtainSkins() {}

void AWEGlobalSettings::obtainTypes()
{
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["types"].asCString());

	// important variables
	Json::Reader reader;
	Json::Value type;
	std::string name, file;
	std::stringstream contents;

	// get all of the media types
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]).toStdString();
		copyFile(file, contents);
		if (reader.parse(contents.str(),
							type, false))
		{
			name = type["type"].asString();
			myMediaTypeNames.insert(name);
			myMediaTypes[name] = type;
		}
		contents.clear();
	}
}

void AWEGlobalSettings::obtainServices()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["services"].asCString());

	// important variables
	Json::Reader reader;
	Json::Value service;
	std::string name, file;
	std::stringstream contents;

	// get all of the JSON players
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]).toStdString();
		copyFile(file, contents);
		if (reader.parse(contents.str(),
							service, false))
		{
			name = service["name"].asString();
			myMediaServiceNames.insert(name);
			myMediaServices[name] = new AWEJSONService(QDir(file.c_str()));
		}
		contents.clear();
	}

	// TODO plugins
}

void AWEGlobalSettings::obtainItems() 
{
	QDir root(mySettingsFile["root"].asCString());
	myRootFolder = (AWEFolder*) getMediaItemByJSONFile(root);
}

AWEMetadataScraper* AWEGlobalSettings::getScraperByName(const std::string& str)
{
	std::map<std::string, AWEMetadataScraper*>::iterator i
		= myMetadataScrapers.find(str);
	if (i != myMetadataScrapers.end())
	{
		return i->second;
	}
	return NULL;
}

Json::Value& AWEGlobalSettings::getScraperSettingsByName(const std::string& str)
{
	std::map<std::string, Json::Value>::iterator i
		= myMetadataScraperSettings.find(str);
	if (i != myMetadataScraperSettings.end())
	{
		return i->second;
	}
	return null;
}

const AWEGlobalSettings::NameSet& AWEGlobalSettings::getAllMetadataScraperNames()
{
	return myMetadataScraperNames;
}

AWEMediaPlayer* AWEGlobalSettings::getPlayerByName(const std::string& str)
{
	std::map<std::string, AWEMediaPlayer*>::iterator i
		= myMediaPlayers.find(str);
	if (i != myMediaPlayers.end())
	{
		return i->second;
	}
	return NULL;
}

Json::Value& AWEGlobalSettings::getPlayerSettingsByName(const std::string& str)
{
	std::map<std::string, Json::Value>::iterator i
		= myMediaPlayerSettings.find(str);
	if (i != myMediaPlayerSettings.end())
	{
		return i->second;
	}
	return null;
}

const AWEGlobalSettings::NameSet& AWEGlobalSettings::getAllMediaPlayerNames()
{
	return myMediaPlayerNames;
}

Json::Value& AWEGlobalSettings::getTypeByName(const std::string& str)
{
	std::map<std::string, Json::Value>::iterator i
		= myMediaTypes.find(str);
	if (i != myMediaTypes.end())
	{
		return i->second;
	}
	return null;
}

const AWEGlobalSettings::NameSet& AWEGlobalSettings::getAllMediaTypeNames()
{
	return myMediaTypeNames;
}

AWEMediaItem* AWEGlobalSettings::getMediaItemByJSONFile(const QDir& file)
{
	std::string str = QDir::cleanPath(file.absolutePath()).toStdString();
	std::map<std::string, AWEMediaItem*>::iterator i = myMediaItems.find(str);
	if (i != myMediaItems.end())
	{
		return i->second;
	}
	else
	{
		// read to get the type
		AWEMediaItem* item = NULL;
		Json::Reader reader;
		Json::Value temp;
		std::stringstream ss;
		if (copyFile(file.absolutePath().toStdString(), ss)
			&& reader.parse(ss.str(), temp, false))
		{
			if (temp["type"].asString() == "file")
			{
				myMediaItems[str] = (item = new AWEMediaFile(file, this));
			}
			else if (temp["type"].asString() == "folder")
			{
				item = new AWEFolder(file, this);
			}
			else if (temp["type"].asString() == "service")
			{
				item = getMediaServiceByName(temp["name"].asString());
			}
		}
		return item;
	}
}

const AWEGlobalSettings::NameSet& AWEGlobalSettings::getAllMediaServiceNames()
{
	return myMediaServiceNames;
}

AWEMediaService* AWEGlobalSettings::getMediaServiceByName(const std::string& str)
{
	std::map<std::string, AWEMediaService*>::iterator i
		= myMediaServices.find(str);
	if (i != myMediaServices.end())
	{
		return i->second;
	}
	return NULL;
}

void AWEGlobalSettings::addFolder(const std::string& str, AWEFolder* folder)
{
	myMediaItems[str] = folder;
}

AWEFolder* AWEGlobalSettings::getRootFolder()
{
	return myRootFolder;
}