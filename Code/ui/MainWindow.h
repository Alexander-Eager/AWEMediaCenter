#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// the super class
#include <QWidget>

// global settings
#include "settings/AWEGlobalSettings.h"

// media items
#include "items/AWEMediaItem.h"
#include "items/AWEMediaFile.h"
#include "items/AWEMediaService.h"

// media player
#include "player/AWEMediaPlayer.h"

// metadata scraper
#include "scraper/AWEMetadataScraper.h"

// window contents objects
#include "ui/contents/WindowContents.h"
#include "ui/contents/FolderBrowser.h"
// #include "SettingsBrowser.h"

/**
 * \brief Contains the user interface classes of AWEMC.
 *
 * \todo Create the UI delegate class.
 **/
namespace UI
{
	/**
	 * \brief The main window of AWEMC, which allows
	 *			the user to browse through the application.
	 **/
	class MainWindow : public QWidget
	{
		public:
			/**
			 * \brief Construct the main window using AWEMC's global settings.
			 *
			 * \param parent The parent widget (usually nullptr).
			 **/
			MainWindow(QWidget* parent);

			/** \brief Destroys this object. **/
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

			/**
			 * \brief Get the settings browser object.
			 *
			 * \returns The settings browser object.
			 **/
			// virtual SettingsBrowser* getSettingsBrowser();

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
			 * \brief Switch to the settings browser.
			 *
			 * This is a convenience function,
			 * equivalent to `setContents(getSettingsBrowser())`.
			 **/
			// virtual void switchToSettingsBrowser();

			/**
			 * \brief Open the media file with the given player.
			 *
			 * \param[in] file The media file to play.
			 * \param[in] player The media player to use.
			 **/
			virtual void openFile(AWE::MediaFile* file, AWE::MediaPlayer* player);

			/**
			 * \brief Open the given media service.
			 *
			 * \param[in] service The service to open.
			 **/
			virtual void openService(AWE::MediaService* service);

		private:
			/** \brief The folder browser pane. **/
			FolderBrowser* myFolderBrowser;

			/** \brief The settings browser pane. **/
			// SettingsBrowser* mySettingsBrowser;

			/** \brief The current contents pane. **/
			WindowContents* myCurrentContents;

			/** \brief The layout for this window. **/
			QVBoxLayout* myLayout;
	};
}

#endif