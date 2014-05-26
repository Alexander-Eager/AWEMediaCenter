#ifndef METADATA_SCRAPER_H
#define METADATA_SCRAPER_H

// library macro
#include "macros/BackendLibraryMacros.h"

// for files, names, and paths
#include <QString>

// for media files
#include "items/MediaItem.h"
#include <QList>

namespace AWE
{
	/**
	 * \brief Defines the general interface for a metadata scraper.
	 *
	 * Metadata scrapers must take in the path to a media file and
	 * use that path to collect icons, fanart images, and other
	 * details about the media item.
	 *
	 * In order to scrape for metadata, AWEMC does the following:
	 *	- Creates the scraper using a `MetadataScraperFactory` in
	 *		a plugin.
	 *	- Scrape for metadata using `scrapeDataForFile()`, multiple
	 *		times if necessary.
	 *	- Deletes the scraper afterward to save memory.
	 *
	 * `MetadataScraper` implementations should be largely immutable,
	 * at least as seen by the functions outside of the class. The only
	 * place internal changes should be made is during the scraping of a
	 * file with temporary instance variables.
	 **/
	class AWEMC_BACKEND_LIBRARY MetadataScraper
	{
		public:
			/**
			 * \brief Enumeration for possible flags.
			 **/
			enum ScraperFlags
			{
				AskUser				= 0x1,
				ImportIcons			= 0x2,
				ImportFanarts		= 0x4,
				ImportImages		= 0x6
			};

			/**
			 * \brief Deconstructor.
			 **/
			virtual ~MetadataScraper() { }

			/**
			 * \brief Retrieves metadata for a metadata object.
			 *
			 * \param[inout] item The object to get metadata for.
			 * \param[in] flags Settings to determine scraping behaviour.
			 *
			 * \returns `true` if the scraper was able to get the metadata,
			 *			`false` if it was not.
			 **/
			virtual bool addMetadata(MetadataHolder* item, int flags) = 0;

			/**
			 * \brief Create a media item (or multiple if applicable) from a
			 *			given file or folder.
			 *
			 * \param[out] placeInMe The `Folder` to put the created items in.
			 * \param[in] file The file or folder to get media items for.
			 * \param[in] flags Settings to determine scraping behaviour.
			 *
			 * \returns A list of media items for the given file. The list is empty if
			 *			the file does not match.
			 **/
			virtual QList<MediaItem*> makeMediaItems(Folder* placeInMe, QString file,
				int flags) = 0;

			/**
			 * \brief Determines if this is scraper can be used.
			 *
			 * \returns `true` if this scraper can be used successfully,
			 *			`false` otherwise.
			 **/
			virtual bool isValid() = 0;

			/**
			 * \brief Gets the name of the scraper.
			 *
			 * \returns The name of the scraper.
			 **/
			virtual QString getName() = 0;

			/**
			 * \brief Gets the media type for this scraper.
			 *
			 * \returns The media type name for the scraper.
			 **/
			virtual QString getType() = 0;
	};
}

#endif // METADATA_SCRAPER_H