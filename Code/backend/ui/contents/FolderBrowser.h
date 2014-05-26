#ifndef FOLDER_BROWSER_H
#define FOLDER_BROWSER_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "WindowContents.h"

// Q_OBJECT
#include <QObject>

// Media items that can be opened
#include "items/MediaItem.h"

// Folders that contain media items
#include "items/Folder.h"

// for scraping
#include "scraper/MetadataScraperHandler.h"

namespace UI
{
	// internal data class
	class FolderBrowserPrivate;

	/**
	 * \brief A window contents pane designed for browsing files.
	 **/
	class AWEMC_BACKEND_LIBRARY FolderBrowser : public WindowContents
	{
		Q_OBJECT

		public:
			/**
			 * \brief Construct a new folder browser.
			 **/
			FolderBrowser();

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~FolderBrowser();

			/**
			 * \brief Get the type of contents, i.e.
			 *			`"Folder Browser"`.
			 *
			 * \returns `"Folder Browser"`
			 **/
			virtual QString getType();

			/**
			 * \brief Set the parent of this
			 *			contents pane (i.e., the main window).
			 *
			 * \param[in] window The `MainWindow` of AWEMC.
			 **/
			virtual void setParent(MainWindow* window);

			/**
			 * \brief Gets the main widget for this screen.
			 *
			 * All of the UI elements for folder browsing
			 * are inside of this widget.
			 *
			 * \returns The main folder browsing widget.
			 **/
			virtual QWidget* getWidget();

			/**
			 * \brief Opens the root folder.
			 **/
			virtual void open();

			/**
			 * \brief Get the current folder.
			 *
			 * \returns The current folder.
			 **/
			virtual AWE::Folder* getCurrentFolder();

		public slots:
			/**
			 * \brief Open the given item.
			 *
			 * If it is a folder, it is opened in the folder pane.
			 * If it is a file or service, it is passed onward
			 * to the main window so that it can open it.
			 * 
			 * \param[in] item The media item to open.
			 **/
			virtual void openItem(AWE::MediaItem* item);

			/**
			 * \brief Go up one folder.
			 *
			 * If this is the root folder,
			 * this function does nothing.
			 **/
			virtual void moveUpOneFolder();

			/**
			 * \brief Set the title bar text.
			 *
			 * \param text The new title bar text.
			 **/
			virtual void setTitleBarText(QString text);

			/**
			 * \brief Set the background image.
			 *
			 * \param image The new background image.
			 **/
			virtual void setBackgroundImage(QPixmap image);

			/**
			 * \brief Scrape for metadata.
			 *
			 * \param[inout] item The item to get metadata for.
			 * \param[in] scraper The scraper to use.
			 * \param[in] flags The scraping configuration.
			 **/
			virtual void scrapeForMetadata(AWE::MetadataHolder* item,
				AWE::MetadataScraperHandler* scraper, int flags);

		private:
			FolderBrowserPrivate* d;
	};
}

#endif