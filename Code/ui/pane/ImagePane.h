#ifndef IMAGE_PANE_H
#define IMAGE_PANE_H

// super class
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// MediaItem class
#include "items/AWEMediaItem.h"

// widgets and layouts to be used
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include "ui/widgets/ImageItemWidget.h"
#include "ui/widgets/collection/ItemListWidget.h"

namespace UI
{
	/**
	 * \brief Defines a class that holds icons and fanart images.
	 **/
	class ImagePane : public Pane
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given parent.
			 *
			 * \param parent The parent widget.
			 **/
			ImagePane(QWidget* parent);

			/**
			 * \brief Destroys this object
			 **/
			~ImagePane();

		public slots:
			/**
			 * \brief Set the item to display images for.
			 *
			 * \param item The item to display images for.
			 **/
			virtual void setItem(AWE::MediaItem* item);

		signals:
			/**
			 * \brief Sent when the fanart image is changed.
			 *
			 * \param[in] image The new fanart image.
			 **/
			void fanartChanged(QPixmap image);

			/**
			 * \brief Sent when the icon image is changed.
			 *
			 * \param[in] image The new icon image.
			 **/
			void iconChanged(QPixmap image);

		private slots:
			/**
			 * \brief Internal slot for handling icon image changes.
			 *
			 * \param icon The image item selected.
			 **/
			void respondToIconChange(ItemWidget* icon);

			/**
			 * \brief Internal slot for handling fanart image changes.
			 *
			 * \param fanart The image item selected.
			 **/
			void respondToFanartChange(ItemWidget* fanart);

			/**
			 * \brief Internal slot for handling temp icon image changes.
			 *
			 * \param icon The image item highlighted.
			 **/
			void respondToTempIconChange(ItemWidget* icon);

			/**
			 * \brief Internal slot for handling temp fanart image changes.
			 *
			 * \param fanart The image item highlighted.
			 **/
			void respondToTempFanartChange(ItemWidget* fanart);

		private:
			/** \brief The item to display images for. **/
			AWE::MediaItem* myMediaItem;

			/** \brief The main layout of this widget. **/
			QVBoxLayout* myMainLayout;

			/** \brief The icon image displayed. **/
			ImageItemWidget* myCurrentIcon;

			/** \brief The list of icon images the user can choose from. **/
			ItemListWidget* myIconList;

			/** \brief The fanart image displayed. **/
			ImageItemWidget* myCurrentFanart;

			/** \brief The list of fanart images the user can choose from. **/
			ItemListWidget* myFanartList;
	};
}

#endif