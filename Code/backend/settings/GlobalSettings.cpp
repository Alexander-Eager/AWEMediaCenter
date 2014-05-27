// class header
#include "GlobalSettings.h"

// for the singleton
#include "AWEMC.h"

using namespace JSON;
using namespace UI;

namespace AWE
{
	class GlobalSettingsPrivate
	{
		public:
			// the object this belongs to
			GlobalSettings* p;

			// functions for loading the settings at startup
			void obtainSkins();
			void obtainTypes();
			void obtainPlayers();
			void obtainScrapers();
			void obtainServices();
			void obtainItems();

			// all of the maps for important data types
			QHash<QString, Skin*> skins;
			QHash<QString, JsonValue> typeMetadata;
			QHash<QString, MediaPlayerHandler*> players;
			QHash<QString, MetadataScraperHandler*> scrapers;
			QHash<QString, MediaServiceHandler*> services;

			// the root folder
			Folder* rootFolder;

			// the current skin
			Skin* currentSkin;
	};
}

using namespace AWE;

GlobalSettings::GlobalSettings(QString settingsFile)
	:	ConfigFile(settingsFile),
		d(new GlobalSettingsPrivate)
{
	// ensure that the folder config section is there
	if (!getMember({"folders"}).isObject())
	{
		addMember({"folders"}, JsonValue::Object);
	}

	// set the singleton
	if (!AWEMC::mySettings)
	{
		AWEMC::mySettings = this;	
	}

	// add pointer to this to the data
	d->p = this;

	// obtain all of the individual parts of AWEMC
	d->obtainSkins();
	d->obtainTypes();
	d->obtainPlayers();
	d->obtainScrapers();
	d->obtainServices();
	d->obtainItems();
}

GlobalSettings::~GlobalSettings()
{
	// delete all of the media items
	MediaItem::deleteAllItems();
	// delete services
	for (auto i : d->services)
	{
		delete i;
	}
	// delete scrapers
	for (auto i : d->scrapers)
	{
		delete i;
	}
	// delete players
	for (auto i : d->players)
	{
		delete i;
	}
	// delete skins
	for (auto i : d->skins)
	{
		delete i;
	}
	// delete internal data
	delete d;
}

QList<QString> GlobalSettings::getSkinNames()
{
	return d->skins.keys();
}

bool GlobalSettings::switchToSkin(QString name)
{
	if (d->skins.contains(name))
	{
		Skin* s = d->skins[name];
		if (s != d->currentSkin)
		{
			d->currentSkin = s;
			emit skinChanged();
		}
		return true;
	}
	return false;
}

Skin* GlobalSettings::getCurrentSkin()
{
	return d->currentSkin;
}

QList<QString> GlobalSettings::getScraperNames()
{
	return d->scrapers.keys();
}

MetadataScraperHandler* GlobalSettings::getScraperHandler(QString name)
{
	if (d->scrapers.contains(name))
	{
		return d->scrapers[name];
	}
	return nullptr;
}

QList<MetadataScraperHandler*> GlobalSettings::getScrapersForItem(MetadataHolder* item)
{
	QList<MetadataScraperHandler*> ans;
	for (auto i : d->scrapers)
	{
		if (i->canBeUsedFor(item))
		{
			ans << i;
		}
	}
	return ans;
}

QList<QString> GlobalSettings::getPlayerNames()
{
	return d->players.keys();
}

MediaPlayerHandler* GlobalSettings::getPlayerHandler(QString name)
{
	if (d->players.contains(name))
	{
		return d->players[name];
	}
	return nullptr;
}

QList<MediaPlayerHandler*> GlobalSettings::getPlayersForFile(MediaFile* file)
{
	QList<MediaPlayerHandler*> ans;
	for (auto i : d->players)
	{
		if (i->canPlay(file))
		{
			ans << i;
		}
	}
	return ans;
}

QList<QString> GlobalSettings::getTypeNames()
{
	return d->typeMetadata.keys();
}

JsonValue GlobalSettings::getTypeMetadata(QString name)
{
	if (d->typeMetadata.contains(name))
	{
		return d->typeMetadata[name];
	}
	return JsonValue::Null;
}

QList<QString> GlobalSettings::getServiceNames()
{
	return d->services.keys();
}

MediaServiceHandler* GlobalSettings::getServiceHandler(QString name)
{
	if (d->services.contains(name))
	{
		return d->services[name];
	}
	return nullptr;
}

Folder* GlobalSettings::getRootFolder()
{
	return d->rootFolder;
}

void GlobalSettingsPrivate::obtainSkins()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "skins"}).isString())
	{
		p->addMember({"folders", "skins"}, "skins/");
	}
	if (!p->getMember({"default skin"}).isString())
	{
		p->addMember({"default skin"}, "Default");
	}

	// get the folder
	QDir folder = p->getPathToConfigFile();
	folder.cd(p->getMember({"folders", "skins"}).toString());
	// look for all JSON files in the folder
	QStringList files = folder.entryList({"*.json"}, QDir::Files);
	for (auto f : files)
	{
		QString file = folder.absoluteFilePath(f);
		Skin* skin = new Skin(file);
		if (/*skin->isValid()*/ 1)
		{
			skins[skin->getName()] = skin;
		}
		else
		{
			delete skin;
		}
	}
	// switch to the default skin
	currentSkin = nullptr;
	p->switchToSkin(p->getMember({"default skin"}).toString());
	if (!currentSkin)
	{
		p->switchToSkin("Default");
	}
}

void GlobalSettingsPrivate::obtainTypes()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "types"}).isString())
	{
		p->addMember({"folders", "types"}, "types/");
	}

	// get the folder
	QDir folder = p->getPathToConfigFile();
	folder.cd(p->getMember({"folders", "types"}).toString());
	// look for all JSON files in the folder
	QStringList files = folder.entryList({"*.json"}, QDir::Files);
	for (auto f : files)
	{
		ConfigFile file(folder.absoluteFilePath(f));
		if (file.isValid())
		{
			typeMetadata[file.getMember({"metadata", "name"}).toString()]
				= file.getMember({"metadata"});
		}
	}
}

void GlobalSettingsPrivate::obtainPlayers()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "players"}).isString())
	{
		p->addMember({"folders", "players"}, "players/");
	}

	// get the folder
	QDir folder = p->getPathToConfigFile();
	folder.cd(p->getMember({"folders", "players"}).toString());
	// look for all JSON files in the folder
	QStringList files = folder.entryList({"*.json"}, QDir::Files);
	for (auto f : files)
	{
		MediaPlayerHandler* player = new MediaPlayerHandler(folder.absoluteFilePath(f));
		players[player->getName()] = player;
	}
}

void GlobalSettingsPrivate::obtainScrapers()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "scrapers"}).isString())
	{
		p->addMember({"folders", "scrapers"}, "scrapers/");
	}

	// get the folder
	QDir folder = p->getPathToConfigFile();
	folder.cd(p->getMember({"folders", "scrapers"}).toString());
	// look for all JSON files in the folder
	QStringList files = folder.entryList({"*.json"}, QDir::Files);
	for (auto f : files)
	{
		MetadataScraperHandler* scraper = new MetadataScraperHandler(f);
		scrapers[scraper->getName()] = scraper;
	}
}

void GlobalSettingsPrivate::obtainServices()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "services"}).isString())
	{
		p->addMember({"folders", "services"}, "services/");
	}

	// get the folder
	QDir folder = p->getPathToConfigFile();
	folder.cd(p->getMember({"folders", "services"}).toString());
	// look for all JSON files in the folder
	QStringList files = folder.entryList({"*.json"}, QDir::Files);
	for (auto f : files)
	{
		MediaServiceHandler* service = new MediaServiceHandler(f);
		services[service->getName()] = service;
	}
}

void GlobalSettingsPrivate::obtainItems()
{
	// ensure that the necessary members are there
	if (!p->getMember({"folders", "root"}).isString())
	{
		p->addMember({"folders", "root"}, "root/root.json");
	}

	// get the file
	QDir folder = p->getPathToConfigFile();
	QString file = folder.absoluteFilePath(p->getMember(
		{"folders", "root"}).toString());
	rootFolder = new Folder(file);
}