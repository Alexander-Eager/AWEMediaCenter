#ifndef JSON_SCRAPER_H
#define JSON_SCRAPER_H

// implemented interface
#include "scraper/MetadataScraper.h"

// configuration file
#include "settings/ConfigFile.h"

// internal data class
class JsonScraperPrivate;

/**
 * \brief A metadata scraper implementation based on
 *			a JSON configuration file.
 *
 * See the <README.md> for information on creating a
 * JSON-based scraper.
 *
 * \todo user prompting
 */
class JsonScraper : public AWE::MetadataScraper
{
	public:
		/**
		 * \brief Create a scraper for the given
		 *			configuration file.
         */
		JsonScraper(AWE::ConfigFile* file);

		/**
		 * \brief Destroy this object.
         */
		virtual ~JsonScraper();

		/**
		 * \brief Retrieves metadata for a metadata object.
		 *
		 * \param[inout] item The object to get metadata for.
		 * \param[in] config Settings to determine scraping behaviour.
		 *
		 * \returns `true` if the scraper was able to get the metadata,
		 *			`false` if it was not.
         */
		virtual bool addMetadata(AWE::MetadataHolder* item,
			ScraperSettings config);

		/**
		 * \brief Create a media item (or multiple if applicable) from a
		 *			given file or folder.
		 *
		 * \param[out] placeInMe The `Folder` to put the created items in.
		 * \param[in] file The file or folder to get media items for.
		 * \param[in] config Settings to determine scraping behaviour.
		 *
         * \returns A list of media items for the given file. The list is empty
         * if the file does not match.
         */
		// virtual QList<MediaItem*> makeMediaItems(AWE::Folder* placeInMe,
		//	QString file, ScraperSettings config);

		/**
		 * \brief Determines if this is scraper can be used.
		 *
		 * \returns `true` if this scraper can be used successfully,
		 *			`false` otherwise.
         */
		virtual bool isValid();

		/**
		 * \brief Gets the name of the scraper.
		 *
		 * \returns The name of the scraper.
         */
		virtual QString getName();

		/**
		 * \brief Gets the media type for this scraper.
		 *
		 * \returns The media type name for the scraper.
         */
		virtual QString getType();

	private:
		JsonScraperPrivate* d;
};

#endif // JSON_SCRAPER_H
