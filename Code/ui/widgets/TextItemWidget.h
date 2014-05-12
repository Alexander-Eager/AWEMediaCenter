#ifndef TEXT_ITEM_WIDGET_H
#define TEXT_ITEM_WIDGET_H

// super class
#include "ItemWidget.h"

// Q_OBJECT
#include <QObject>

// for text
#include <QString>
#include <QFont>

// for painting
#include <QPaintEvent>
#include <QPainter>

// for size
#include <QSize>
#include <QResizeEvent>

namespace UI
{
	/**
	 * \brief Displays text in a specific font.
	 *
	 * Unlike `TextPane`, no background is drawn,
	 * so it is safe to use in lists and in `Pane`s.
	 *
	 * In addition, this class signals mouse click
	 * events
	 **/
	class TextItemWidget : public ItemWidget
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given text and font.
			 *
			 * If you do not know what font to use,
			 * consider `QFont("Helvetica", 15)`,
			 * which is Helvetica with point size 15.
			 *
			 * \param parent The parent widget.
			 * \param text The text to display.
			 * \param font The font to use with that text.
			 * \param highlightable `true` if this item
			 *						can be highlighted,
			 *						`false` otherwise.
			 **/
			TextItemWidget(QWidget* parent, QString text,
							QFont font, bool highlightable = false);

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
			 * \brief Get the item type, "Text Item".
			 *
			 * \returns "Text Item".
			 **/
			virtual QString getItemType() const;

			/**
			 * \brief Get the text displayed by this widget.
			 *
			 * \returns The displayed text.
			 **/
			virtual QString getText() const;

			/**
			 * \brief Get the font used by this widget.
			 *
			 * \returns The font used to display text.
			 **/
			virtual QFont getFont() const;

			/**
			 * \brief Set the alignment for the text.
			 *
			 * For more information on the available
			 * values, see [`Qt::Alignment`](http://qt-project.org/doc/qt-4.8/qt.html#AlignmentFlag-enum).
			 *
			 * By default, the alignment is
			 * `Qt::AlignLeft | Qt::AlignVCenter`.
			 *
			 * \param alignment The desired alignment.
			 **/
			virtual void setAlignment(int alignment);

			/**
			 * \brief Get the text alignment.
			 *
			 * \returns The text alignment.
			 **/
			virtual int getAlignment() const;
		
		public slots:
			/**
			 * \brief Change the text displayed.
			 *
			 * \param text The new text to display.
			 **/
			virtual void setText(QString text);

			/**
			 * \brief Change the font to use.
			 *
			 * \param font The new font to use.
			 **/
			virtual void setFont(QFont font);

		protected:
			/**
			 * \brief Responds to size events.
			 *
			 * \param event The (ignored) size event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);
			
			/**
			 * \brief Paint this widget.
			 *
			 * \param event The (ignored) paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);

		private:
			/** \brief The text to display. **/
			QString myText;

			/** \brief The font to use. **/
			QFont myFont;

			/** \brief The alignment of text. **/
			int myAlignment;

			/** \brief The containing size. **/
			QSize myFitInSize;
	};
}

#endif