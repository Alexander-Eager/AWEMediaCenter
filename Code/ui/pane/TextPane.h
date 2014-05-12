#ifndef TEXT_PANE_H
#define TEXT_PANE_H

// super class
#include "Pane.h"

// for text
#include <QString>
#include <QFont>

// for painting
#include <QPaintEvent>
#include <QPainter>

// for size
#include <QResizeEvent>
#include <QSize>

namespace UI
{
	/**
	 * \brief This class acts as a replacement
	 *			for `QLabel` when text is needed
	 *			in a particular font.
	 **/
	class TextPane : public Pane
	{
		public:
			/**
			 * \brief Make with the given text and font.
			 *
			 * If you do not know what font to use,
			 * consider `QFont("Helvetica", 30)`,
			 * which is Helvetica with point size 30.
			 *
			 * \param parent The parent widget.
			 * \param text The text to display.
			 * \param font The font to use with that text.
			 **/
			TextPane(QWidget* parent, QString text,
						QFont font);

			/**
			 * \brief Set the alignment for the text.
			 *
			 * For more information on the available
			 * values, see [`Qt::Alignment`](http://qt-project.org/doc/qt-4.8/qt.html#AlignmentFlag-enum).
			 *
			 * By default, the alignment is
			 * `Qt::AlignHCenter | Qt::AlignVCenter`.
			 *
			 * \param alignment The desired alignment.
			 **/
			virtual void setAlignment(int alignment);

			/**
			 * \brief Set the minimum width for the text box.
			 *
			 * Here is the general meaning of this parameter:
			 * 	- The text box must be at least this wide.
			 *	- Text will not cause the width of the widget
			 *		to expand past this size.
			 *	- If the widget is inside a layout wider than
			 *		this, text can move past this.
			 *
			 * \param width The minimum width.
			 **/
			virtual void setMinimumTextWidth(int width);
			
			/**
			 * \brief Change the text displayed.
			 *
			 * \param text The new text to display.
			 **/
			virtual void setText(QString text);

			/**
			 * \brief Get the text displayed.
			 *
			 * \returns The displayed text.
			 **/
			virtual QString getText();

			/**
			 * \brief Change the font to use.
			 *
			 * \param font The new font to use.
			 **/
			virtual void setFont(QFont font);

			/**
			 * \brief The size hint for this widget.
			 *
			 * For `TextPane`s, the size hint is
			 * a rectangle for single-line of text.
			 **/
			virtual QSize sizeHint() const;

		protected:
			/**
			 * \brief Paints the text.
			 *
			 * \param event The (ignored) paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);

			/**
			 * \brief Changes the minimum height requirements.
			 *
			 * \param event The (ignored) resize event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);

		private:
			/** \brief Helper function to fix the minimum size. **/
			void adjustMinimumSize();
			
			/** \brief The text. **/
			QString myText;

			/** \brief The font. **/
			QFont myFont;

			/** \brief The alignment of text. **/
			int myAlignment;

			/** \brief The maximum width of the text. **/
			int myMinimumWidth;

			/** \brief The size hint for this widget. **/
			QSize mySizeHint;
	};
}

#endif