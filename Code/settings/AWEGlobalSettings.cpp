// class header
#include "AWEGlobalSettings.h"

// the types that are held inside GlobalSettings

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

using namespace AWE;
using namespace Json;
using namespace std;

Value GlobalSettings::null = Value::null;

GlobalSettings::GlobalSettings(const string& settingsFile)
{
	// TODO make safe
	stringstream ss;
	copyFile(settingsFile, ss);
	Reader reader;
	reader.parse(ss.str(), mySettingsFile, false);

	// get all of the objects
	obtainScrapers();
	obtainPlayers();
	obtainSkins();
	obtainTypes();
	obtainServices();
	obtainItems();
}

GlobalSettings::~GlobalSettings()
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

void GlobalSettings::obtainScrapers()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["scrapers"].asCString());

	// important variables
	Reader reader;
	Value scraper;
	string name, type, file;
	stringstream contents;

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
			myMetadataScrapers[name] = new JSONScraper(name, type);
		}
		contents.clear();
	}

	// TODO plugins
}

void GlobalSettings::obtainPlayers()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["players"].asCString());

	// important variables
	Reader reader;
	Value player;
	string name, file;
	stringstream contents;

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
			myMediaPlayers[name] = new JSONPlayer(player);
		}
		contents.clear();
	}

	// TODO plugins
}

void GlobalSettings::obtainSkins() {}

void GlobalSettings::obtainTypes()
{
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["types"].asCString());

	// important variables
	Reader reader;
	Value type;
	string name, file;
	stringstream contents;

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

void GlobalSettings::obtainServices()
{
	// get the directory
	QDir dir(QDir::current());
	dir.cd(mySettingsFile["services"].asCString());

	// important variables
	Reader reader;
	Value service;
	string name, file;
	stringstream contents;

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
			myMediaServices[name] = new JSONService(QDir(file.c_str()));
		}
		contents.clear();
	}

	// TODO plugins
}

void GlobalSettings::obtainItems() 
{
	QDir root(mySettingsFile["root"].asCString());
	myRootFolder = (Folder*) getMediaItemByJSONFile(root);
}

MetadataScraper* GlobalSettings::getScraperByName(const string& str)
{
	map<string, MetadataScraper*>::iterator i
		= myMetadataScrapers.find(str);
	if (i != myMetadataScrapers.end())
	{
		return i->second;
	}
	return NULL;
}

Value& GlobalSettings::getScraperSettingsByName(const string& str)
{
	map<string, Value>::iterator i
		= myMetadataScraperSettings.find(str);
	if (i != myMetadataScraperSettings.end())
	{
		return i->second;
	}
	return null;
}

const GlobalSettings::NameSet& GlobalSettings::getAllMetadataScraperNames()
{
	return myMetadataScraperNames;
}

MediaPlayer* GlobalSettings::getPlayerByName(const string& str)
{
	map<string, MediaPlayer*>::iterator i
		= myMediaPlayers.find(str);
	if (i != myMediaPlayers.end())
	{
		return i->second;
	}
	return NULL;
}

Value& GlobalSettings::getPlayerSettingsByName(const string& str)
{
	map<string, Value>::iterator i
		= myMediaPlayerSettings.find(str);
	if (i != myMediaPlayerSettings.end())
	{
		return i->second;
	}
	return null;
}

const GlobalSettings::NameSet& GlobalSettings::getAllMediaPlayerNames()
{
	return myMediaPlayerNames;
}

Value& GlobalSettings::getTypeByName(const string& str)
{
	map<string, Value>::iterator i
		= myMediaTypes.find(str);
	if (i != myMediaTypes.end())
	{
		return i->second;
	}
	return null;
}

const GlobalSettings::NameSet& GlobalSettings::getAllMediaTypeNames()
{
	return myMediaTypeNames;
}

MediaItem* GlobalSettings::getMediaItemByJSONFile(const QDir& file)
{
	string str = QDir::cleanPath(file.absolutePath()).toStdString();
	map<string, MediaItem*>::iterator i = myMediaItems.find(str);
	if (i != myMediaItems.end())
	{
		return i->second;
	}
	else
	{
		// read to get the type
		MediaItem* item = NULL;
		Reader reader;
		Value temp;
		stringstream ss;
		if (copyFile(file.absolutePath().toStdString(), ss)
			&& reader.parse(ss.str(), temp, false))
		{
			if (temp["type"].asString() == "file")
			{
				myMediaItems[str] = (item = new MediaFile(file, this));
			}
			else if (temp["type"].asString() == "folder")
			{
				item = new Folder(file, this);
			}
			else if (temp["type"].asString() == "service")
			{
				item = getMediaServiceByName(temp["name"].asString());
			}
		}
		return item;
	}
}

const GlobalSettings::NameSet& GlobalSettings::getAllMediaServiceNames()
{
	return myMediaServiceNames;
}

MediaService* GlobalSettings::getMediaServiceByName(const string& str)
{
	map<string, MediaService*>::iterator i
		= myMediaServices.find(str);
	if (i != myMediaServices.end())
	{
		return i->second;
	}
	return NULL;
}

void GlobalSettings::addFolder(const string& str, Folder* folder)
{
	myMediaItems[str] = folder;
}

Folder* GlobalSettings::getRootFolder()
{
	return myRootFolder;
}