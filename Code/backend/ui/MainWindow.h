#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the superclass
#include <QWidget>

// Q_OBJECT
#include <QObject>

// media items
#include "items/MediaItem.h"
#include "items/MediaFile.h"
#include "items/MediaServiceHandler.h"

// media player
#include "player/MediaPlayerHandler.h"

// metadata scraper
#include "scraper/MetadataScraperHandler.h"

// window contents objects
#include "ui/contents/WindowContents.h"
#include "ui/contents/FolderBrowser.h"

/**
 * \brief Contains the user interface classes of AWEMC.
 *
 * \todo Create the UI delegate class.
 * \todo Settings browser class.
 **/
namespace UI
{
	// internal data class
	class MainWindowPrivate;

	/**
	 * \brief The main window of AWEMC, which allows
	 *			the user to browse through the application.
	 **/
	class AWEMC_BACKEND_LIBRARY MainWindow : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * \brief Construct the main window using AWEMC's global settings.
			 *
			 * \param parent The parent widget (usually nullptr).
			 **/
			MainWindow(QWidget* parent);

			/** 
			 * \brief Destroys this object. 
			 **/
			virtual ~MainWindow();

			/**
			 * \brief Shows this item in fullscreen and opens the
			 *			contents.
			 **/
			virtual void open();

			/**
			 * \brief Get the contents of the window.
			 *
			 * \returns The contents of the window.
			 **/
			virtual WindowContents* getContents();

			/**
			 * \brief Get the folder browser object.
			 *
			 * \returns The folder browser object.
			 **/
			virtual FolderBrowser* getFolderBrowser();

		public slots:
			/**
			 * \brief Set the contents of the window.
			 *
			 * \param contents The new contents of the window.
			 **/
			virtual void setContents(WindowContents* contents);

			/**
			 * \brief Switch to the folder browser.
			 *
			 * This is a convenience function,
			 * equivalent to `setContents(getFolderBrowser())`.
			 **/
			virtual void switchToFolderBrowser();

			/**
			 * \brief Open the media file with the given player.
			 *
			 * \param[in] file The media file to play.
			 * \param[in] player The media player to use.
			 **/
			virtual void openFile(AWE::MediaFile* file, AWE::MediaPlayerHandler* player);

			/**
			 * \brief Open the given media service.
			 *
			 * \param[in] service The service to open.
			 **/
			virtual void openService(AWE::MediaServiceHandler* service);

		protected:
			/**
			 * \brief Erases the window.
			 *
			 * \param[in] event The (ignored) paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);

		private:
			MainWindowPrivate* d;
	};
}

#endif