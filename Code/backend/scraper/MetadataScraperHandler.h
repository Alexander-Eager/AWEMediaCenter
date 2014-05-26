#ifndef METADATA_SCRAPER_HANDLER_H
#define METADATA_SCRAPER_HANDLER_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "settings/MetadataHolder.h"

// data classes
#include <QList>
#include <QString>

// scraper related classes
#include "items/Folder.h"

namespace AWE
{
	// internal data class
	class MetadataScraperHandlerPrivate;

	/**
	 * \brief Handler for a metadata scraper.
	 *
	 * Loads and unloads the plugin to help
	 * save memory.
	 **/
	class AWEMC_BACKEND_LIBRARY MetadataScraperHandler : public MetadataHolder
	{
		public:
			/**
			 * \brief Make a new handler for the
			 *			scraper with the given
			 *			config file.
			 *
			 * \param file The configuration file.
			 **/
			MetadataScraperHandler(QString file);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~MetadataScraperHandler();

			/**
			 * \brief Prepare the scraper by loading
			 *			data into memory.
			 *
			 * \returns `true` if the scraper was
			 *			prepared successfully,
			 *			`false` otherwise.
			 **/
			virtual bool prepare();

			/**
			 * \brief Retrieves metadata for a metadata object.
			 *
			 * \param[inout] item The object to get metadata for.
			 * \param[in] flags Settings to determine scraping behaviour.
			 *
			 * \returns `true` if the scraper was able to get the metadata,
			 *			`false` if it was not.
			 **/
			virtual bool addMetadata(MetadataHolder* item, int flags);

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
				int flags);

			/**
			 * \brief Deactivate the scraper and clean up memory usage.
			 **/
			virtual void deactivate();

			/**
			 * \brief Determine if the scraper can be used.
			 *
			 * \returns `true` if the scraper can be used,
			 *			`false` otherwise.
			 **/
			virtual bool isValid() const;

			/**
			 * \brief Determine if the scraper can be used
			 *			on the given file.
			 *
			 * \returns `true` if the scraper can be used
			 *			on the given file, `false`
			 *			otherwise.
			 **/
			virtual bool canBeUsedFor(MetadataHolder* item) const;

		private:
			MetadataScraperHandlerPrivate* d;
	};
}

#endif // METADATA_SCRAPER_HANDLER_H