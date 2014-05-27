#ifndef MEDIA_ITEM_WIDGET_H
#define MEDIA_ITEM_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "ItemWidget.h"

// parent widget class
#include <QWidget>

// MediaItem class
#include "items/MediaItem.h"

// for displaying text and images
#include <QBoxLayout>
#include "TextItemWidget.h"
#include "ImageItemWidget.h"

namespace UI
{
	// internal data class
	class MediaItemWidgetPrivate;

	/**
	 * \brief A list widget class that holds
	 *			a media item.
	 *
	 * This can be displayed as the name of the
	 * item, its default icon, or both.
	 **/
	class AWEMC_BACKEND_LIBRARY MediaItemWidget : public ItemWidget
	{
		Q_OBJECT

		public:
			/** \brief Values describing the display modes for this widget. **/
			enum DisplayMode { NameOnly, IconOnly,
				NameAndIconLeftToRight, NameAndIconTopToBottom };

			/**
			 * \brief Construct for the given media item.
			 *
			 * By default, this is displayed as the name of the file.
			 *
			 * \param[in] parent The parent widget.
			 * \param[in] item The media item this widget represents.
			 * \param highlightable `true` if this widget
			 *						can be highlighted and
			 *						selected, `false` if not.
			 **/
			MediaItemWidget(QWidget* parent, AWE::MediaItem* item,
							bool highlightable = false);

			/**
			 * \brief Fix this item's size to fit in the given
			 *			size.
			 *
			 * If `size == QSize(-1, -1)`, the item should not
			 * fix its size.
			 *
			 * This is mostly used by `ItemCollectionWidget`s to
			 * make sure that the item does not get swallowed up
			 * by the spacers used to align the items.
			 *
			 * \param size The size to fit inside.
			 *
			 * \returns `true` if this item can fit in `size`,
			 *			`false` if it cannot.
			 **/
			virtual bool fixSizeToFitIn(QSize size);

			/**
			 * \brief Get the size this item has to fit in.
			 *
			 * This is the size set by `fixSizeToFitIn()`.
			 *
			 * \returns The size this item has to fit in.
			 **/
			virtual QSize getSizeToFitIn() const;

			/**
			 * \brief Get the item type, "Media Item".
			 *
			 * \returns "Media Item".
			 **/
			virtual QString getItemType() const;

			/**
			 * \brief Make a copy of this item widget.
			 *
			 * \returns A dynamically allocated copy of this widget.
			 **/
			virtual MediaItemWidget* makeCopy() const;

			/**
			 * \brief Set the display mode for this widget.
			 *
			 * This can be any of the values from
			 * `MediaItemWidget::DisplayMode`:
			 *	- `NameOnly`: display the name as text.
			 *	- `IconOnly`: display the default icon image.
			 *	- `NameAndIconLeftToRight`: display both the name and the
			 *								default icon image, icon on left.
			 *	- `NameAndIconTopToBottom`: display both the name and the
			 *								default icon image, icon on top.
			 *
			 * \param[in] mode The display mode to use.
			 **/
			virtual void setDisplayMode(DisplayMode mode);

			/**
			 * \brief Get the display mode for this widget.
			 *
			 * \returns The display mode for this widget.
			 **/
			virtual DisplayMode getDisplayMode() const;

			/**
			 * \brief Gets the media item represented by this widget.
			 *
			 * \returns The media item represented by this widget.
			 **/
			virtual AWE::MediaItem* getMediaItem() const;

		public slots:
			/**
			 * \brief Change the media item.
			 *
			 * \param[in] item The new media item.
			 **/
			virtual void setMediaItem(AWE::MediaItem* item);

		private:
			MediaItemWidgetPrivate* d;
	};
}

#endif