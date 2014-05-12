#ifndef INFO_PANE_H
#define INFO_PANE_H

// superclass
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// data related classes
#include "settings/AWEGlobalSettings.h"
#include "libs/json/json.h"
#include "items/AWEMediaItem.h"
#include "items/AWEMediaFile.h"
#include "items/AWEMediaService.h"
#include "items/AWEFolder.h"
#include "player/AWEMediaPlayer.h"
#include "scraper/AWEMetadataScraper.h"
#include "type/AWEFolderGenerator.h"

// UI related classes
#include <QString>
#include <QWidget>
#include "ui/widgets/TextItemWidget.h"
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QFrame>

// for painting the background color
#include <QPaintEvent>
#include <QColor>
#include <QPainter>

namespace UI
{
	/**
	 * \brief Displays the details and description
	 *			of a media item.
	 **/
	class InfoPane : public Pane
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given parent.
			 *
			 * \param parent The parent widget.
			 **/
			InfoPane(QWidget* parent, AWE::GlobalSettings* settings);

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
			void wantsToOpenFile(AWE::MediaFile* file, AWE::MediaPlayer* player);

			/**
			 * \brief Sent when the user asks to open
			 *			a media service.
			 *
			 * \param[in] service The service to open.
			 **/
			void wantsToOpenService(AWE::MediaService* service);

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
			 * \param[in] askUser `true` if the user should be
			 *						prompted at appropriate times,
			 *						`false` if no prompting should occur.
			 * \param[in] import `true` if metadata files should be imported,
			 *						`false` if only absolutely necessary.
			 * \param[in] inheritMetadata `true` if the item should inherit
			 *								metadata from the containing folder,
			 *								`false` otherwise.
			 **/
			void wantsToScrapeForMetadata(AWE::MediaItem* item,
											AWE::MetadataScraper* scraper,
											bool askUser, bool import,
											bool inheritMetadata);

		private slots:
			/**
			 * \brief Respond to the user clicking the play button.
			 **/
			void respondToPlayButton();

			/**
			 * \brief Respond to the user clicking the service open button.
			 **/
			void respondToOpenButton();

			/**
			 * \brief Respond to the user clicking the folder open button.
			 **/
			void respondToFolderOpen();

			/**
			 * \brief Respond to the user clicking the scrape button.
			 **/
			void respondToScrapeButton();

		private:
			/**
			 * \brief Helper function that creates the details
			 **/
			void makeDetailUIElements();

			/**
			 * \brief Helper funciton that fills the drop down menus.
			 **/
			void makeDropdownMenus();

			/**
			 * \brief Helper function that converts a Json::Value
			 *			into a `QString` for the UI.
			 *
			 * \param val The value to convert to a QString.
			 **/
			QString stringFor(Json::Value& val);

			/** \brief The global settings of AWEMC. **/
			AWE::GlobalSettings* myGlobalSettings;

			/** \brief The currently represented item. **/
			AWE::MediaItem* myMediaItem;

			/** \brief The main layout of this widget. **/
			QVBoxLayout* myMainLayout;

			/** \brief Name of the item. **/
			TextItemWidget* myName;

			/** \brief Media type of this item. **/
			TextItemWidget* myMediaType;

			/** \brief Separates the name and type from the details. **/
			QFrame* myFirstSeparator;

			/** \brief Scrollable area holding all of the details. **/
			QScrollArea* myDetailScrollArea;

			/** \brief Widget holding all of the details. **/
			QWidget* myDetailWidget;

			/** \brief Detail layout. **/
			QGridLayout* myDetailLayout;

			/** \brief List of the details. **/
			QList<TextItemWidget*> myDetails;

			/** \brief List of the detail values. **/
			QList<TextItemWidget*> myDetailValues;

			/** \brief Separates the details from the description. **/
			QFrame* mySecondSeparator;

			/** \brief Scroll area for the description. **/
			QScrollArea* myDescriptionScrollArea;

			/** \brief Description of the item. **/
			TextItemWidget* myDescription;

			/** \brief Metadata scraper button layout. **/
			QHBoxLayout* myScraperLayout;

			/** \brief Button to start scraping. **/
			QPushButton* myScrapeButton;

			/** \brief Drop down for selecting the scraper to use. **/
			QComboBox* myScraperSelections;

			/** \brief Layout for scraping options. **/
			QHBoxLayout* myScraperOptionsLayout;

			/** \brief Check box for user prompting. **/
			QCheckBox* myAskUserBox;

			/** \brief Check box for file importing. **/
			QCheckBox* myImportBox;

			/** \brief Check box for metadata inheritance. **/
			QCheckBox* myInheritMetadataBox;

			// depending on the displayed type, there can be different buttons
			/** \brief Switchable layout for different kinds of items. **/
			QStackedLayout* myButtonArea;

			// file type
			/** \brief Widget for media files. **/
			QWidget* myMediaFileButtons;

			/** \brief Layout for the media file buttons. **/
			QHBoxLayout* myMediaFileLayout;

			/** \brief Button for playing a media file. **/
			QPushButton* myPlayButton;

			/** \brief Drop down for choosing the desired media player. **/
			QComboBox* myPlayerSelections;

			// service type
			/** \brief Button for opening a media service. **/
			QPushButton* myServiceButton;

			// folder type
			/** \brief Button for opening a folder. **/
			QPushButton* myFolderButton;
	};
}

#endif