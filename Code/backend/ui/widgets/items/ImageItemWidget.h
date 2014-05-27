#ifndef IMAGE_ITEM_WIDGET_H
#define IMAGE_ITEM_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "ItemWidget.h"

// parent widget
#include <QWidget>

// data
#include <QPixmap>
#include <QString>

// for size
#include <QSize>
#include <QResizeEvent>

namespace UI
{
	// internal data class
	class ImageItemWidgetPrivate;

	/**
	 * \brief A `QListWidgetItem` that holds an image.
	 **/
	class AWEMC_BACKEND_LIBRARY ImageItemWidget : public ItemWidget
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given image file.
			 *
			 * \param[in] parent The parent widget.
			 * \param[in] file The image file to open.
			 * \param[in] highlightable `true` if this widget
			 *						can be highlighted and
			 *						selected, `false` if not.
			 * \param[in] size The width and height of the image.
			 **/
			ImageItemWidget(QWidget* parent, int index, QString file,
							bool highlightable = false,
							QSize size = QSize(-1, -1));

			/**
			 * \brief Make with the given image.
			 *
			 * \param[in] parent The parent widget.
			 * \param[in] file The image file to open.
			 * \param[in] highlightable `true` if this widget
			 *						can be highlighted and
			 *						selected, `false` if not.
			 * \param[in] size The width and height of the image.
			 **/
			ImageItemWidget(QWidget* parent, int index, QPixmap image,
							bool highlightable = false,
							QSize size = QSize(-1, -1));

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ImageItemWidget();

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
			 * \brief Returns the recommended height for the
			 *			given width.
			 *
			 * \param w The width to use.
			 *
			 * \returns The recommended height for a widget
			 *			with width `w`.
			 **/
			virtual int heightForWidth(int w) const;

			/** 
			 * \brief Set the aspect ratio mode used to
			 *			scale the pixmap.
			 *
			 * \param mode The new aspect ratio mode.
			 **/
			virtual void setAspectRatioMode(Qt::AspectRatioMode mode);

			/**
			 * \brief Get the aspect ratio mode used to
			 *			scale the pixmap.
			 *
			 * By default, this is set to `Qt::KeepAspectRatio`.
			 *
			 * \returns The aspect ratio mode used to scale the image.
			 **/
			virtual Qt::AspectRatioMode getAspectRatioMode() const;

			/**
			 * \brief Get the type of this item, "Image Item".
			 *
			 * \returns "Image Item".
			 **/
			virtual QString getItemType() const;

			/**
			 * \brief Make a copy of this item widget.
			 *
			 * \returns A dynamically allocated copy of this widget.
			 **/
			virtual ImageItemWidget* makeCopy() const;

			/**
			 * \brief Get the image held by this widget.
			 *
			 * \returns The image held by this widget.
			 **/
			virtual QPixmap getImage() const;

			/**
			 * \brief Get the index for the image.
			 *
			 * \returns The index for the image.
			 **/
			virtual int getIndex() const;

		public slots:
			/**
			 * \brief Sets the image held by this widget.
			 *
			 * \param[in] file The file holding the image.
			 **/
			virtual void setImage(QString file);

			/**
			 * \brief Sets the image held by this widget.
			 *
			 * \param[in] image The new image.
			 **/
			virtual void setImage(QPixmap image);

			/**
			 * \brief Set the index for the image.
			 *
			 * \param[in] index The index for the image.
			 **/
			virtual void setIndex(int index);

		protected:
			/**
			 * \brief Paints this widget.
			 *
			 * \param[in] event The paint event (ignored).
			 **/
			virtual void paintEvent(QPaintEvent* event);

			/**
			 * \brief Resizes the icon if necessary.
			 *
			 * \param[in] event The resize event (ignored).
			 **/
			virtual void resizeEvent(QResizeEvent* event);

		private:
			ImageItemWidgetPrivate* d;
	};
}

#endif