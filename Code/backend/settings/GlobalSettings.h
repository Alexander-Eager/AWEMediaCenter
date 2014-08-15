#ifndef AWE_GLOBAL_SETTINGS_H
#define AWE_GLOBAL_SETTINGS_H

// for names and accessing data
#include <QString>

// for settings file data
#include <JsonDataTree/Json.h>
#include "ConfigFile.h"

// what actually is contained
#include "settings/MetadataHolder.h"
#include "items/MediaItem.h"
#include "items/Folder.h"
#include "items/MediaServiceHandler.h"
#include "items/MediaFile.h"
#include "scraper/MetadataScraperHandler.h"
#include "player/MediaPlayerHandler.h"
#include "skin/Skin.h"

/**
 * \brief Backend for AWEMC.
 */
namespace AWE {
	// internal data class
	class GlobalSettingsPrivate;

	/**
	 * \brief Holds the global settings for AWEMC.
	 *
	 * \todo Skins
	 * \todo UI delegate (with user prompting)
	 *
	 * Functions for pretty much anything you want to know
	 * about the prefernces for AWEMC are here. Every plugin
	 * extending AWEMC has its own configuration file, which
	 * is held in here via sub-configuration objects.
	 *
	 * You shouldn't instantiate this class. You should get the
	 * main instance of this class from the `AWEMC` class.
     */
    class AWEMC_BACKEND_LIBRARY GlobalSettings : public ConfigFile {
		Q_OBJECT

		public:
			/**
			 * \brief Create the global settings object.
			 *
			 * \param[in] settingsFile The file that contains
             *			  the settings for AWEMC (usually
             *			  `settings.json` in the root folder)
             */
			GlobalSettings(QString settingsFile);

			/**
			 * \brief Destroy this object.
             */
			virtual ~GlobalSettings();

			/**
			 * \brief Get a list of all skin names.
			 *
			 * \returns A list of all skin names.
             */
			virtual QList<QString> getSkinNames();

			/**
			 * \brief Switch to the given skin.
			 *
			 * \param name The name of the skin to switch to.
			 *
			 * \returns `true` if the desired skin exists and was
			 *			switched to, `false` otherwise.
             */
			virtual bool switchToSkin(QString name);

			/**
			 * \brief Get the current skin.
			 *
			 * Use this to get widget configurations and fonts.
			 *
			 * \returns The current skin.
             */
			virtual UI::Skin* getCurrentSkin();

			/** 
			 * \brief Get a set of all metadata scraper names.
			 *
			 * \returns A set filled with every metadata scraper name.
             */
			virtual QList<QString> getScraperNames();

			/**
			 * \brief Get a metadata scraper handler by name.
			 *
			 * \param[in] name The name of the scraper.
			 *
			 * \returns The desired scraper as an `MetadataScraper` object
			 *			or `nullptr` if it does not exist.
             */
			virtual MetadataScraperHandler* getScraperHandler(QString name);

			/**
			 * \brief Get a set of all metadata scrapers that can scrape
             *		  for the given item.
			 *
			 * \param item The media item to get possible scrapers for.
			 *
			 * \returns A list of all possible metadata scrapers that
			 *			can get metadata for `item`.
             */
            virtual QList<MetadataScraperHandler*> getScrapersForItem(
                    MetadataHolder* item);

			/** 
			 * \brief Get a set of all media player names.
			 *
			 * \returns A set filled with every media player name.
             */
			virtual QList<QString> getPlayerNames();

			/**
			 * \brief Get a media player handler by name.
			 *
			 * \param[in] name The name of the player.
			 *
			 * \returns The desired media player
			 *			or `nullptr` if it does not exist.
             */
			virtual MediaPlayerHandler* getPlayerHandler(QString name);

			/**
			 * \brief Get a set of all media players that can play the given
			 *			file.
			 *
			 * \param[in] file The file for which to get possible players.
			 *
			 * \returns A list of all possible media players that can play
			 *			`file`.
             */
			virtual QList<MediaPlayerHandler*> getPlayersForFile(MediaFile* file);

			/**
			 * \brief Get a set of all media types.
			 *
			 * \returns A set filled with every media type name.
             */
			virtual QList<QString> getTypeNames();

			/**
			 * \brief Get the metadata for the given type.
			 *
			 * \returns The default metadata settings for the given type.
             */
			virtual JSON::JsonValue getTypeMetadata(QString name);

			/**
			 * \brief Get the names of all of the media services.
			 *
			 * \returns A set filled with every media service name.
             */
			virtual QList<QString> getServiceNames();

			/**
			 * \brief Get a media service by name.
			 *
			 * \param name The name of the media service.
			 *
			 * \returns The desired media service.
             */
			virtual MediaServiceHandler* getServiceHandler(QString name);

			/**
			 * \brief Get the root folder.
			 *
			 * \returns The root folder.
             */
			virtual Folder* getRootFolder();

		signals:
			/**
			 * \brief Sent when the current skin has been changed,
             *		  so that all relevant widgets can change.
             */
			void skinChanged();

		private:
			GlobalSettingsPrivate* d;
	};
}

#endif
