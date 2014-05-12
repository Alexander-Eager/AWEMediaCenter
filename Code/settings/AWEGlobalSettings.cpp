// class header
#include "AWEGlobalSettings.h"

// for debugging
#include "debug_macros/debug.h"

// for the singleton
#include "AWEMC.h"

/* the types that are held inside GlobalSettings */
// scrapers
#include "scraper/AWEMetadataScraper.h"
#include "scraper/AWEJSONScraper.h"

// players
#include "player/AWEMediaPlayer.h"
#include "player/AWEJSONPlayer.h"

// types
#include "type/AWEFolderGenerator.h"

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

// for writing files
#include <fstream>
#include <iostream>

// for temporary data
#include <QQueue>

using namespace AWE;
using namespace Json;
using namespace std;

Value GlobalSettings::null = Value::null;

GlobalSettings::GlobalSettings(QDir settingsFile)
	:	mySettingsFile(settingsFile.absolutePath())
{
	// set the AWEMC::settings() value
	if (!AWEMC::settings())
	{
		AWEMC::mySettings = this;
	}
	// read in the settings file
	QString contents;
	QTextStream ss(&contents);
	copyFile(settingsFile.absolutePath(), ss);
	Reader reader;
	reader.parse(contents.toStdString(), mySettings, false);

	// get all of the objects
	obtainFonts();
	obtainScrapers();
	obtainPlayers();
	obtainSkins();
	obtainTypes();
	obtainServices();
	obtainItems();
}

GlobalSettings::~GlobalSettings()
{
	// delete everything
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

void GlobalSettings::obtainFonts()
{
	Value::Members mems = mySettings["fonts"].getMemberNames();
	for (auto font : mems)
	{
		QFont f(mySettings["fonts"][font]["name"].asCString(),
				mySettings["fonts"][font]["size"].asInt(),
				mySettings["fonts"][font]["weight"].asInt(),
				mySettings["fonts"][font]["italic"].asBool());
		myFonts[font.data()] = f;
	}
}

void GlobalSettings::obtainScrapers()
{
	// get the directory
	QDir dir(mySettingsFile.absolutePath());
	dir.cdUp();
	dir.cd(mySettings["folders"]["scrapers"].asCString());

	// important variables
	Reader reader;
	Value scraper;
	QString name, type, file;
	QString contents;
	QTextStream stream(&contents);

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
	QDir dir(mySettingsFile.absolutePath());
	dir.cdUp();
	dir.cd(mySettings["folders"]["players"].asCString());

	// important variables
	Reader reader;
	Value player;
	QString name, file;
	QString contents;
	QTextStream stream(&contents);

	// get all of the JSON players
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (uint i = 0; i < dir.count(); ++ i)
	{
		file = dir.absoluteFilePath(dir[i]);
		copyFile(file, stream);
		if (reader.parse(contents.toStdString(),
							player, false))
		{
			name = player["name"].asCString();
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
	QDir dir(mySettingsFile.absolutePath());
	dir.cdUp();
	dir.cd(mySettings["folders"]["types"].asCString());

	// important variables
	FolderGenerator* type;
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
		QQueue<FolderGenerator*> types;
		types.enqueue(type);
		while (types.count() > 0)
		{
			// get the front of the queue
			type = types.dequeue();

			// add it to the relevant internal data
			name = type->getType();
			myFolderGenerators[name] = type;

			// add all sub generators to the queue
			for (FolderGenerator* j : type->getSubGenerators())
			{
				types.enqueue(j);
			}
		}
	}
}

void GlobalSettings::obtainServices()
{
	// get the directory
	QDir dir(mySettingsFile.absolutePath());
	dir.cdUp();
	dir.cd(mySettings["folders"]["services"].asCString());

	// important variables
	MediaService* service;
	QString name;
	QDir file;

	// get all of the JSON services
	dir.cd("json");
	QStringList filter;
	filter << "*.json";
	dir.setNameFilters(filter);
	for (uint i = 0; i < dir.count(); ++ i)
	{
		file = QDir(dir.absoluteFilePath(dir[i]));
		service = new JSONService(file);
		name = service->getName();
		myMediaServices[name] = service;
	}

	// TODO plugins
}

void GlobalSettings::obtainItems() 
{
	QDir dir(mySettingsFile.absolutePath());
	dir.cdUp();
	dir = QDir(dir.absolutePath() + "/" + mySettings["folders"]["root"].asCString());
	myRootFolder = (Folder*) getMediaItemByJSONFile(dir);
}

QFont GlobalSettings::getFontByName(QString str)
{
	auto i = myFonts.find(str);
	if (i != myFonts.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Font \"" << str.toStdString() << "\" does not exist")
	return myFonts["normal"];
}

MetadataScraper* GlobalSettings::getScraperByName(QString str)
{
	auto i = myMetadataScrapers.find(str);
	if (i != myMetadataScrapers.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Scraper \"" << str.toStdString() << "\" does not exist")
	return nullptr;
}

Value& GlobalSettings::getScraperSettingsByName(QString str)
{
	auto i = myMetadataScraperSettings.find(str);
	if (i != myMetadataScraperSettings.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Scraper \"" << str.toStdString() << "\" does not exist")
	return null;
}

QList<QString> GlobalSettings::getAllMetadataScraperNames()
{
	return myMetadataScrapers.keys();
}

QList<MetadataScraper*> GlobalSettings::getAllScrapersForItem(MediaItem* item)
{
	QList<MetadataScraper*> ans;
	for (auto scraper : myMetadataScrapers)
	{
		if (scraper->getType() == item->getType()
			|| item->getType() == "Generic Media")
		{
			ans << scraper;
		}
	}
	return ans;
}

MediaPlayer* GlobalSettings::getPlayerByName(QString str)
{
	auto i = myMediaPlayers.find(str);
	if (i != myMediaPlayers.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Player \"" << str.toStdString() << "\" does not exist")
	return nullptr;
}

Value& GlobalSettings::getPlayerSettingsByName(QString str)
{
	auto i = myMediaPlayerSettings.find(str);
	if (i != myMediaPlayerSettings.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Player \"" << str.toStdString() << "\" does not exist")
	return null;
}

QList<QString> GlobalSettings::getAllMediaPlayerNames()
{
	return myMediaPlayers.keys();
}

QList<MediaPlayer*> GlobalSettings::getAllPlayersForFile(MediaFile* file)
{
	QList<MediaPlayer*> ans;
	for (auto player : myMediaPlayers)
	{
		if (player->canPlay(file))
		{
			ans << player;
		}
	}
	return ans;
}

Value& GlobalSettings::getTypeByName(QString str)
{
	auto i = myFolderGenerators.find(str);
	if (i != myFolderGenerators.end())
	{
		return (*i)->getDefaultMetadata();
	}
	DEBUG_WARN("WARNING: Type \"" << str.toStdString() << "\" does not exist")
	return null;
}

QList<QString> GlobalSettings::getAllMediaTypeNames()
{
	return myMediaTypes.keys();
}

MediaItem* GlobalSettings::getMediaItemByJSONFile(QDir file)
{
	auto i = myMediaItems.find(file.absolutePath());
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
		QTextStream stream(&contents);
		if (copyFile(file.absolutePath(), stream)
			&& reader.parse(contents.toStdString(), temp, false))
		{
			if (temp["type"].asString() == "file")
			{
				myMediaItems[file.absolutePath()] = (item = new MediaFile(file));
			}
			else if (temp["type"].asString() == "folder")
			{
				item = new Folder(file);
			}
			else if (temp["type"].asString() == "service")
			{
				item = getMediaServiceByName(temp["name"].asCString());
			}
		}
		return item;
	}
}

QList<QString> GlobalSettings::getAllMediaServiceNames()
{
	return myMediaServices.keys();
}

MediaService* GlobalSettings::getMediaServiceByName(QString str)
{
	auto i = myMediaServices.find(str);
	if (i != myMediaServices.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Service \"" << str.toStdString() << "\" does not exist")
	return nullptr;
}

void GlobalSettings::addItem(MediaItem* item)
{
	myMediaItems[item->getConfigFile().absolutePath()] = item;
}

Folder* GlobalSettings::getRootFolder()
{
	return myRootFolder;
}

FolderGenerator* GlobalSettings::getFolderGeneratorForType(QString type)
{
	auto i = myFolderGenerators.find(type);
	if (i != myFolderGenerators.end())
	{
		return *i;
	}
	DEBUG_WARN("WARNING: Type \"" << type.toStdString() << "\" does not exist")
	return nullptr;
}