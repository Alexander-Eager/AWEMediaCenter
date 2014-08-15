#ifndef INFO_PANE_H
#define INFO_PANE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// data related classes
#include "items/MediaItem.h"
#include "items/MediaFile.h"
#include "items/MediaServiceHandler.h"
#include "items/Folder.h"
#include "player/MediaPlayerHandler.h"
#include "scraper/MetadataScraperHandler.h"

namespace UI
{
	// internal data class
	class InfoPanePrivate;

	/**
	 * \brief Displays the details and description
	 *			of a media item.
	 **/
	class AWEMC_BACKEND_LIBRARY InfoPane : public Pane
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given parent.
			 *
			 * \param parent The parent widget.
			 **/
			InfoPane(QWidget* parent);

			/**
			 * \brief Destroys this object.
			 **/
			~InfoPane();

		public slots:
			/**
			 * \brief Set the infos displayed to
			 *			those of the given item.
			 *
			 * \param item The item to display infos for.
			 **/
			virtual void setItem(AWE::MediaItem* item);

		signals:
			/**
			 * \brief Sent when the user asks to play
			 *			the media file.
			 *
			 * \param[in] file The media file to play.
			 * \param[in] player The player to play it with.
			 **/
			void wantsToOpenFile(AWE::MediaFile* file, AWE::MediaPlayerHandler* player);

			/**
			 * \brief Sent when the user asks to open
			 *			a media service.
			 *
			 * \param[in] service The service to open.
			 **/
			void wantsToOpenService(AWE::MediaServiceHandler* service);

			/**
			 * \brief Sent when the user asks to open
			 *			a folder.
			 *
			 * \param[in] folder The folder to open.
			 **/
			void wantsToOpenFolder(AWE::Folder* folder);

			/**
			 * \brief Sent when the user asks to scrape
			 *			for new metadata.
			 *
			 * \param[in] item The item to scrape for metadata
			 *					for.
			 * \param[in] scraper The scraper to use.
			 * \param[in] flags The settings to use while scraping.
			 **/
			void wantsToScrapeForMetadata(AWE::MediaItem* item,
                AWE::MetadataScraperHandler* scraper,
                AWE::MetadataScraper::ScraperSettings flags);

		private:
			friend class InfoPanePrivate;
			InfoPanePrivate* d;
	};
}

#endif
