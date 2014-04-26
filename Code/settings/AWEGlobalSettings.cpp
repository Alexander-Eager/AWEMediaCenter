// class header
#include "AWEGlobalSettings.h"

// the types that are held inside GlobalSettings

// scrapers
#include "scraper/AWEMetadataScraper.h"
#include "scraper/AWEJSONScraper.h"

// players
#include "player/AWEMediaPlayer.h"
#include "player/AWEJSONPlayer.h"

// types
#include "types/AWEFolderGenerator.h"

// items
#include "items/AWEMediaItem.h"
#include "items/AWEMediaFile.h"
#include "items/AWEFolder.h"
#include "items/AWEMediaService.h"
#include "items/AWEJSONService.h"

// for traversing paths
#include <QStringList>

// for reading files
#include "libs/generic_file_reader/file_reader.h"
#include <iostream>
#include <sstream>

// for temporary data
#include <QQueue>

using namespace AWE;
using namespace Json;
using namespace std;

Value GlobalSettings::null = Value::null;

GlobalSettings::GlobalSettings(const QString& settingsFile)
{
	// read in the settings file
	QString contents;;
	QTextStream ss(contents);
	copyFile(settingsFile, ss);
	Reader reader;
	reader.parse(contents.toStdString(), mySettings, false);

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
		delete i;
	}
	for (auto i : myMetadataScrapers)
	{
		delete i;
	}
	for (auto i : myMediaItems)
	{
		delete i;
	}
	for (auto i : myFolderGenerators)
	{
		delete i;
	}
}

void GlobalSettings::obtainScrapers()
{
	// get the directory
	QDir dir(mySettingsFile);
	dir.cdUp();
	dir.cd(mySettings["scrapers"].asCString());

	// important variables
	Reader reader;
	Value scraper;
	QString name, type, file;
	QTextStream stream;
	QString contents;

	// get all of the JSON scrapers
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (uint i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]);
		copyFile(file, stream);
		if (reader.parse(contents.toStdString(), 
							scraper, false))
		{
			name = scraper["name"].asCString();
			type = scraper["type"].asCString();
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
	QDir dir(mySettingsFile);
	dir.cdUp();
	dir.cd(mySettings["players"].asCString());

	// important variables
	Reader reader;
	Value player;
	QString name, file;
	QTextStream stream;
	QString contents;

	// get all of the JSON players
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]);
		copyFile(file, stream);
		if (reader.parse(contents.toStdString(),
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

void GlobalSettings::obtainSkins() { }

void GlobalSettings::obtainTypes()
{
	QDir dir(mySettingsFile);
	dir.cdUp();
	dir.cd(mySettings["types"].asCString());

	// important variables
	FolderGenerator* type;
	FolderGenerator* sub;
	QString name;
	QDir file;

	// get all of the media types
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (uint i = 0; i < dir.count(); ++ i)
	{
		// get the file
		file = QDir(dir.absoluteFilePath(dir[i]));

		// get the root type
		type = new FolderGenerator(file);

		// get all sub types
		deque<FolderGenerator*> types;
		types.push_back(type);
		while (types.size() > 0)
		{
			// get the front of the queue
			sub = types.front();
			types.pop_front();

			// add it to the relevant internal data
			name = type->getType();
			myMediaTypeNames.insert(name);
			myFolderGenerators[name] = type;

			// add all sub generators to the queue
			for (FolderGenerator* j : sub->getSubGenerators())
			{
				types.push_back(j);
			}
		}
	}
}

void GlobalSettings::obtainServices()
{
	// get the directory
	QDir dir(mySettingsFile);
	dir.cdUp();
	dir.cd(mySettings["services"].asCString());

	// important variables
	MediaService* service;
	QString name;
	QDir file;

	// get all of the JSON services
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (unsigned int i = 0; i < dir.count(); ++ i)
	{
		file = QDir(dir.absoluteFilePath(dir[i]));

		service = new MediaService(file)
		name = service->getName();
		myMediaServiceNames.insert(name);
		myMediaServices[name] = service;
	}

	// TODO plugins
}

void GlobalSettings::obtainItems() 
{
	QDir dir(mySettingsFile);
	dir.cdUp();
	myRootFolder = (Folder*) getMediaItemByJSONFile(root);
}

MetadataScraper* GlobalSettings::getScraperByName(const QString& str)
{
	auto i = myMetadataScrapers.find(str);
	if (i != myMetadataScrapers.end())
	{
		return *i;
	}
	return nullptr;
}

Value& GlobalSettings::getScraperSettingsByName(const QString& str)
{
	auto i = myMetadataScraperSettings.find(str);
	if (i != myMetadataScraperSettings.end())
	{
		return *i;
	}
	return null;
}

QList<QString> GlobalSettings::getAllMetadataScraperNames()
{
	return myMetadataScraperNames;
}

MediaPlayer* GlobalSettings::getPlayerByName(const QString& str)
{
	auto i = myMediaPlayers.find(str);
	if (i != myMediaPlayers.end())
	{
		return *i;
	}
	return nullptr;
}

Value& GlobalSettings::getPlayerSettingsByName(const QString& str)
{
	auto i = myMediaPlayerSettings.find(str);
	if (i != myMediaPlayerSettings.end())
	{
		return *i;
	}
	return null;
}

QList<QString> GlobalSettings::getAllMediaPlayerNames()
{
	return myMediaPlayerNames;
}

Value& GlobalSettings::getTypeByName(const QString& str)
{
	auto i = myFolderGenerators.find(str);
	if (i != myFolderGenerators.end())
	{
		return i->getDefaultMetadata();
	}
	return null;
}

QList<QString> GlobalSettings::getAllMediaTypeNames()
{
	return myMediaTypeNames;
}

MediaItem* GlobalSettings::getMediaItemByJSONFile(const QDir& file)
{
	auto i = myMediaItems.find(file);
	if (i != myMediaItems.end())
	{
		return *i;
	}
	else
	{
		// read to get the type
		MediaItem* item = nullptr;
		Reader reader;
		Value temp;
		QString contents;
		QTextStream stream(contents);
		if (copyFile(file.absolutePath(), stream)
			&& reader.parse(contents.toStdString(), temp, false))
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

QList<QString> GlobalSettings::getAllMediaServiceNames()
{
	return myMediaServiceNames;
}

MediaService* GlobalSettings::getMediaServiceByName(const QString& str)
{
	auto i = myMediaServices.find(str);
	if (i != myMediaServices.end())
	{
		return *i;
	}
	return nullptr;
}

void GlobalSettings::addItem(MediaItem* item)
{
	myMediaItems[item->getJSONFile()] = item;
}

Folder* GlobalSettings::getRootFolder()
{
	return myRootFolder;
}