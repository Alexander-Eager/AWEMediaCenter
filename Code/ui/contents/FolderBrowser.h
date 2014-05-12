#ifndef FOLDER_BROWSER_H
#define FOLDER_BROWSER_H

// superclass
#include "WindowContents.h"
#include <QWidget>

// Q_OBJECT
#include <QObject>

// AWEMC global settings
#include "settings/AWEGlobalSettings.h"

// Media items that can be opened
#include "items/AWEMediaItem.h"

// Folders that contain media items
#include "items/AWEFolder.h"

// internal data stuff
#include <QStack>

// the layouts used
#include <QStackedLayout>
#include <QHBoxLayout>

// a bunch of widget classes for displaying everything
#include <QLabel>
#include "ui/pane/ImagePane.h"
#include "ui/pane/InfoPane.h"
#include "ui/pane/FolderPane.h"
#include "ui/pane/TextPane.h"
#include "ui/widgets/ImageItemWidget.h"

namespace UI
{
	/**
	 * \brief A window contents pane designed for browsing files.
	 **/
	class FolderBrowser : public QObject, public WindowContents
	{
		Q_OBJECT

		public:
			/**
			 * \brief Construct using AWEMC's global settings.
			 *
			 * \param[in] settings The global settings of AWEMC.
			 **/
			FolderBrowser(AWE::GlobalSettings* settings);

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
			 * \param[in] askUser `true` if the user should be
			 *						prompted at appropriate times,
			 *						`false` if no prompting should occur.
			 * \param[in] import `true` if metadata files should be imported,
			 *						`false` if only absolutely necessary.
			 * \param[in] inheritMetadata `true` if the item should inherit
			 *								metadata from the containing folder,
			 *								`false` otherwise.
			 **/
			virtual void scrapeForMetadata(AWE::MediaItem* item,
											AWE::MetadataScraper* scraper,
											bool askUser, bool import,
											bool inheritMetadata);

		private slots:
			/**
			 * \brief Internal slot for refreshing the folder list.
			 *
			 * \param image The (ignored) icon image.
			 **/
			virtual void respondToIconChange(QPixmap image);

		private:
			// this is all data stuff
			/** \brief The global settings of AWEMC. **/
			AWE::GlobalSettings* myGlobalSettings;

			/** \brief The folder browsing history. **/
			QStack<AWE::Folder*> myBrowserHistory;

			// this is all UI stuff
			/** \brief The main widget for folder browsing. **/
			QWidget* myMainWidget;

			/** \brief The stacked layout with everything on it. **/
			QStackedLayout* myMainLayout;

			/** \brief The background image. **/
			ImageItemWidget* myBackgroundImage;

			/** \brief The foreground layouts. **/
			QWidget* myForegroundWidget;
			/** \brief The foreground layouts. **/
			QVBoxLayout* myForegroundMainLayout;
			/** \brief The foreground layouts. **/
			QHBoxLayout* myForegroundLayout;

			/** \brief The title bar. **/
			TextPane* myTitleBar;

			/** \brief The item image pane. **/
			ImagePane* myImagePane;

			/** \brief The folder pane. **/
			FolderPane* myFolderPane;

			/** \brief The item info pane. **/
			InfoPane* myInfoPane;
	};
}

#endif