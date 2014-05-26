#ifndef IMAGE_PANE_H
#define IMAGE_PANE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// super class
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// MediaItem class
#include "items/MediaItem.h"

// images
#include <QPixmap>

// for slots
#include "ui/widgets/items/ItemWidget.h"

namespace UI
{
	// internal data class
	class ImagePanePrivate;

	/**
	 * \brief Defines a class that holds icons and fanart images.
	 **/
	class AWEMC_BACKEND_LIBRARY ImagePane : public Pane
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

		private:
			friend class ImagePanePrivate;
			ImagePanePrivate* d;
	};
}

#endif