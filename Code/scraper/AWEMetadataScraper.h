#ifndef AWE_METADATA_SCRAPER_H
#define AWE_METADATA_SCRAPER_H

// for files, names, and paths
#include <string>

// for settings
#include "settings/AWEGlobalSettings.h"

// for media files
#include "items/AWEMediaFile.h"

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
	 *	- Prepare the scraper by calling `prepare()`.
	 *	- Scrape for metadata using `scrapeDataForFile()`.
	 *	- Deactivate the scraper by calling `deactivate()`.
	 *
	 * `MetadataScraper` implementations should be largely immutable,
	 * at least as seen by the functions outside of the class. The only
	 * place internal changes should be made is during the scraping of a
	 * file with temporary instance variables.
	 **/
	class MetadataScraper
	{
		public:
			/**
			 * \brief Deconstructor.
			 **/
			virtual ~MetadataScraper() { }

			/**
			 * \brief Prepares the scraper.
			 *
			 * This helps with memory management. If you rely on large objects
			 * to scrape for metadata, this is where you should construct them.
			 *
			 * \param[in] settings The [global settings of AWEMC](../settings/README.md),
			 *				so that your scraper can be customized.
			 *
			 * \returns `true` if the scraper was able to prepare itself,
			 *			`false` if an error occured and scraping should be
			 *			aborted.
			 **/
			virtual bool prepare(GlobalSettings* settings) = 0;

			/**
			 * \brief Retrieves metadata for a media file.
			 *
			 * You must write the metadata to `file`.
			 *
			 * To construct your JSON file, you should use 
			 * [jsoncpp](http://jsoncpp.sourceforge.net).
			 *
			 * `askUser` tells your scraper if the user wants to be
			 * given a list of choices for certain things. You should 
			 * NOT ask the user for everything if `askUser` is true;
			 * only basic things like, "Which icon do you want to use?"
			 *
			 * `import` specifies if the files you get should be
			 * copied into AWEMC's folders. Do NOT copy the media file.
			 *
			 * \param[inout] file The media file to get metadata for.
			 * \param[in] askUser `true` if the user wants to be given choices,
			 *				`false` otherwise.
			 * \param[in] import `true` if the user wants to import metadata files,
			 *				`false` otherwise.
			 *
			 * \returns `true` if the scraper was able to get the metadata,
			 *			`false` if it was not.
			 **/
			virtual bool scrapeDataForFile(MediaFile* file,
				bool askUser, bool import) = 0;

			/**
			 * \brief Destroys any used-up dynamic memory.
			 *
			 * This helps with memory management. If you rely on large objects
			 * to scrape for metadata, this is where you should `delete` them.
			 **/
			virtual void deactivate() = 0;

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
			virtual const std::string& getName() = 0;

			/**
			 * \brief Gets the media type for this scraper.
			 *
			 * \returns The media type name for the scraper.
			 **/
			virtual const std::string& getType() = 0;
	};
}

Q_DECLARE_INTERFACE(AWE::MetadataScraper, "com.awe.metadata.scraper/0.1")

#endif