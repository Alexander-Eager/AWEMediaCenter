#ifndef AWE_GLOBAL_SETTINGS_H
#define AWE_GLOBAL_SETTINGS_H

// for internal data storage
#include <map>
#include <set>

// for names and accessing data
#include <string>
#include <QDir>

// for settings file reading
#include "libs/json/json.h"

/**
 * \brief Backend for AWEMC.
 **/
namespace AWE
{
	// forward declarations
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
			typedef std::set<std::string> NameSet;

			static Json::Value null;

			/**
			 * \brief Create the global settings object.
			 *
			 * \param[in] settingsFile The file that contains
			 *				the settings for AWEMC (usually
			 *				`settings.json` in the root folder)
			 **/
			GlobalSettings(const std::string& settingsFile);

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
			MetadataScraper* getScraperByName(const std::string& name);

			/**
			 * \brief Get a metadata scraper's settings by name.
			 *
			 * \param[in] name The name of the scraper.
			 *
			 * \returns The settings of the desired scraper
			 *			or `Json::Value::null` if it does not exist.
			 **/
			Json::Value& getScraperSettingsByName(const std::string& name);

			/** 
			 * \brief Get a set of all metadata scrapers.
			 *
			 * \returns A set filled with every metadata scraper name.
			 **/
			const NameSet& getAllMetadataScraperNames();

			/**
			 * \brief Get a media player by name.
			 *
			 * \param[in] name The name of the player.
			 *
			 * \returns The desired media player
			 *			or `NULL` if it does not exist.
			 **/
			MediaPlayer* getPlayerByName(const std::string& name);

			/**
			 * \brief Get a media player's settings by name.
			 *
			 * \param[in] name The name of the player.
			 *
			 * \returns The settings of the desired media player
			 *			or `Json::Value::null` if it does not exist.
			 **/
			Json::Value& getPlayerSettingsByName(const std::string& name);

			/** 
			 * \brief Get a set of all media players.
			 *
			 * \returns A set filled with every media player name.
			 **/
			const NameSet& getAllMediaPlayerNames();

			/**
			 * \brief Get the media type with the given name.
			 *
			 * \returns The default metadata settings for the given type.
			 **/
			Json::Value& getTypeByName(const std::string& name);

			/**
			 * \brief Get a set of all media types.
			 *
			 * \returns A set filled with every media type name.
			 **/
			const NameSet& getAllMediaTypeNames();

			/**
			 * \brief Get the names of all of the media services.
			 *
			 * \returns A set filled with every media service name.
			 **/
			const NameSet& getAllMediaServiceNames();

			/**
			 * \brief Get a media service by name.
			 *
			 * \param name The name of the media service.
			 *
			 * \returns The desired media service.
			 **/
			MediaService* getMediaServiceByName(const std::string& name);

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
			 * \brief Add the given folder.
			 *
			 * \param path The path to the config file.
			 * \param folder The folder.
			 **/
			void addFolder(const std::string& path, Folder* folder);

			/**
			 * \brief Get the root folder.
			 *
			 * \returns The root folder.
			 **/
			Folder* getRootFolder();

		private:
			/** \brief The global settings file. **/
			Json::Value mySettingsFile;

			/** \brief Names of all of the media players. **/
			NameSet myMediaPlayerNames;
			/** \brief Maps names of media players onto players. **/
			std::map<std::string, MediaPlayer*> myMediaPlayers;
			/** \brief Maps names of media players onto settings. **/
			std::map<std::string, Json::Value> myMediaPlayerSettings;

			/** \brief Names of all of the metadata scrapers. **/
			NameSet myMetadataScraperNames;
			/** \brief Maps names of metadata scrapers onto scrapers. **/
			std::map<std::string, MetadataScraper*> myMetadataScrapers;
			/** \brief Maps names of metadata scrapers onto settings. **/
			std::map<std::string, Json::Value> myMetadataScraperSettings;

			/** \brief Names of all of the media types. **/
			NameSet myMediaTypeNames;
			/** \brief Maps names of media types onto metadata defaults. **/
			std::map<std::string, Json::Value> myMediaTypes;

			/** \brief Names of all of the media services. **/
			NameSet myMediaServiceNames;
			/** \brief Maps names of media services onto services. **/
			std::map<std::string, MediaService*> myMediaServices;

			/** \brief Maps the absolute, clean path of an item onto the item. **/
			std::map<std::string, MediaItem*> myMediaItems;
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