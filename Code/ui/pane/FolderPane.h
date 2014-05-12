#ifndef FOLDER_PANE_H
#define FOLDER_PANE_H

// widgets and layouts
#include <QWidget>
#include <QStackedLayout>
#include "ui/widgets/MediaItemWidget.h"
#include "ui/widgets/collection/ItemListWidget.h"
#include "ui/widgets/collection/ItemGridWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

// superclass
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// the Folder class
#include "items/AWEFolder.h"

// the MediaItem class
#include "items/AWEMediaItem.h"

// for painting the background color
#include <QPaintEvent>
#include <QColor>
#include <QPainter>

namespace UI
{
	/**
	 * \brief Allows the user to browse through
	 *			the items of a folder.
	 *
	 * This is a collection of UI items holding
	 * a list of `AWE::MediaItem`s and a back button.
	 *
	 * \todo Other layout options, possibly with icons.
	 **/
	class FolderPane : public Pane
	{
		Q_OBJECT

		public:
			/**
			 * \brief Construct with the given parent widget.
			 *
			 * \param[in] parent The parent widget.
			 **/
			FolderPane(QWidget* parent);

			/**
			 * \brief Destroys this object.
			 **/
			virtual ~FolderPane();

		public slots:
			/**
			 * \brief Change the folder to the given folder.
			 *
			 * Changes the list of items that the user can select.
			 *
			 * \param[in] folder The folder to change to.
			 **/
			virtual void setFolder(AWE::Folder* folder);

			/**
			 * \brief Refresh the item lists.
			 **/
			virtual void refresh();

		signals:
			/**
			 * \brief Sent when an item is highlighted, but not
			 *			selected.
			 *
			 * \param[in] item The item that was highlighted.
			 **/
			void itemHighlighted(AWE::MediaItem* item);

			/**
			 * \brief Sent when the user has opened an item.
			 *
			 * \param[in] item The item that was chosen.
			 **/
			void itemSelected(AWE::MediaItem* item);

			/**
			 * \brief Sent when the user wants to go back one
			 *			folder.
			 **/
			void goUpOne();

		private slots:
			/**
			 * \brief Internal slot for emitting item highlighting.
			 *
			 * \param[in] curr The highlighted item.
			 **/
			void respondToItemHighlight(ItemWidget* curr);

			/**
			 * \brief Internal slot for emitting item selection.
			 *
			 * \param[in] item The chosen item.
			 **/
			void respondToItemSelected(ItemWidget* item);

			/**
			 * \brief Internal slot for changing the view mode.
			 *
			 * \param[in] mode The new view mode.
			 **/
			void respondToViewModeChoice(int mode);

			/**
			 * \brief Internal slot for emitting back button events.
			 **/
			void respondToBackButton();

		private:
			// this is data stuff
			/** \brief The folder whose contents are displayed. **/
			AWE::Folder* myFolder;

			// this is UI stuff
			/** \brief The main layout for this widget. **/
			QVBoxLayout* myMainLayout;

			/** \brief The back button. **/
			QPushButton* myBackButton;

			/** \brief View selection menu. **/
			QComboBox* myViewSelectionMenu;

			/** \brief The layout to switch between item view modes. **/
			QStackedLayout* myMediaItemLayout;

			/** \brief The list of contained media items. **/
			ItemListWidget* myMediaItemList;

			/** \brief The grid of contained media items. **/
			ItemGridWidget* myMediaItemGrid;
	};
}

#endif