#ifndef AWE_GLOBAL_SETTINGS_H
#define AWE_GLOBAL_SETTINGS_H

// for internal data storage
#include <QHash>
#include <QList>

// for names and accessing data
#include <QString>
#include <QDir>

// for settings file reading
#include "libs/json/json.h"

/**
 * \brief Backend for AWEMC.
 **/
namespace AWE
{
	// forward declarations
	class FolderGenerator;
	class MetadataScraper;
	class MediaItem;
	class Folder;
	class MediaService;
	class MediaPlayer;

	/**
	 * \brief Holds the global settings for AWEMC.
	 *
	 * \todo Skins...
	 * \todo Get a better folder adding system.
	 *
	 * Functions for pretty much anything you want to know
	 * about the prefernces for AWEMC are here. Every plugin
	 * extending AWEMC has its own configuration file, which
	 * is held in here via sub-configuration objects.
	 *
	 * You shouldn't need to instantiate this class on your own;
	 * most objects are passed a copy of the settings object during
	 * creation or through some other means.
	 **/
	class GlobalSettings
	{
		public:
			/** \brief The set type used to hold names. **/
			typedef QList<QString> NameSet;

			static Json::Value null;

			/**
			 * \brief Create the global settings object.
			 *
			 * \param[in] settingsFile The file that contains
			 *				the settings for AWEMC (usually
			 *				`settings.json` in the root folder)
			 **/
			GlobalSettings(const QString& settingsFile);

			/** \brief Deconstructor.
			 * 
			 * Deletes every scraper, player and item.
			 **/
			~GlobalSettings();

			/**
			 * \brief Get a metadata scraper by name.
			 *
			 * \param[in] name The name of the scraper.
			 *
			 * \returns The desired scraper as an `MetadataScraper` object
			 *			or `NULL` if it does not exist.
			 **/
			MetadataScraper* getScraperByName(const QString& name);

			/**
			 * \brief Get a metadata scraper's settings by name.
			 *
			 * \param[in] name The name of the scraper.
			 *
			 * \returns The settings of the desired scraper
			 *			or `Json::Value::null` if it does not exist.
			 **/
			Json::Value& getScraperSettingsByName(const QString& name);

			/** 
			 * \brief Get a set of all metadata scrapers.
			 *
			 * \returns A set filled with every metadata scraper name.
			 **/
			QList<QString> getAllMetadataScraperNames();

			/**
			 * \brief Get a media player by name.
			 *
			 * \param[in] name The name of the player.
			 *
			 * \returns The desired media player
			 *			or `NULL` if it does not exist.
			 **/
			MediaPlayer* getPlayerByName(const QString& name);

			/**
			 * \brief Get a media player's settings by name.
			 *
			 * \param[in] name The name of the player.
			 *
			 * \returns The settings of the desired media player
			 *			or `Json::Value::null` if it does not exist.
			 **/
			Json::Value& getPlayerSettingsByName(const QString& name);

			/** 
			 * \brief Get a set of all media players.
			 *
			 * \returns A set filled with every media player name.
			 **/
			QList<QString> getAllMediaPlayerNames();

			/**
			 * \brief Get the media type with the given name.
			 *
			 * \returns The default metadata settings for the given type.
			 **/
			Json::Value& getTypeByName(const QString& name);

			/**
			 * \brief Get a set of all media types.
			 *
			 * \returns A set filled with every media type name.
			 **/
			QList<QString> getAllMediaTypeNames();

			/**
			 * \brief Get the names of all of the media services.
			 *
			 * \returns A set filled with every media service name.
			 **/
			QList<QString> getAllMediaServiceNames();

			/**
			 * \brief Get a media service by name.
			 *
			 * \param name The name of the media service.
			 *
			 * \returns The desired media service.
			 **/
			MediaService* getMediaServiceByName(const QString& name);

			/**
			 * \brief Get a media item from its JSON file.
			 *
			 * `file` is a `QDir`, so relative paths and links
			 * do not duplicate. If `file` is not found, it is
			 * added.
			 *
			 * \returns The desired media item.
			 **/
			MediaItem* getMediaItemByJSONFile(const QDir& file);

			/**
			 * \brief Add the given media item.
			 *
			 * \param item The media item.
			 **/
			void addItem(MediaItem* item);

			/**
			 * \brief Get the root folder.
			 *
			 * \returns The root folder.
			 **/
			Folder* getRootFolder();

		private:
			/** \brief The global settings. **/
			Json::Value mySettings;
			/** \brief The global settings file. **/
			Json::Value mySettingsFile;

			/** \brief Maps names of media players onto players. **/
			QHash<QString, MediaPlayer*> myMediaPlayers;
			/** \brief Maps names of media players onto settings. **/
			QHash<QString, Json::Value> myMediaPlayerSettings;

			/** \brief Maps names of metadata scrapers onto scrapers. **/
			QHash<QString, MetadataScraper*> myMetadataScrapers;
			/** \brief Maps names of metadata scrapers onto settings. **/
			QHash<QString, Json::Value> myMetadataScraperSettings;

			/** \brief Maps names of media types onto folder generators. **/
			QHash<QString, FolderGenerator*> myFolderGenerators;

			/** \brief Maps names of media services onto services. **/
			QHash<QString, MediaService*> myMediaServices;

			/** \brief Maps the absolute, clean path of an item onto the item. **/
			QHash<QDir, MediaItem*> myMediaItems;
			/** \brief The root folder. **/
			Folder* myRootFolder;

			/** \brief Obtain the scrapers. **/
			void obtainScrapers();
			/** \brief Obtain the players. **/
			void obtainPlayers();
			/** \brief Obtain the skins. **/
			void obtainSkins();
			/** \brief Obtain the types. **/
			void obtainTypes();
			/** \brief Obtain the services. **/
			void obtainServices();
			/** \brief Obtain the items. **/
			void obtainItems();
	};
}

#endif