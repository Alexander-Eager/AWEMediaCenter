#ifndef TEXT_PANE_H
#define TEXT_PANE_H

// library macros
#include "macros/BackendLibraryMacros.h"

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
	// internal data class
	class TextPanePrivate;

	/**
	 * \brief This class acts as a replacement
	 *			for `QLabel` when text is needed
	 *			in a particular font.
	 **/
	class AWEMC_BACKEND_LIBRARY TextPane : public Pane
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
						QString font = "biggest");

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~TextPane();

			/**
			 * \brief Get the text displayed by this widget.
			 *
			 * \returns The displayed text.
			 **/
			virtual QString getText() const;

			/**
			 * \brief Get the font used by this widget.
			 *
			 * \returns The name font used to display text
			 *			(as it would be accessed in a `Skin`).
			 **/
			virtual QString getFont() const;

			/**
			 * \brief Get the text alignment.
			 *
			 * \returns The text alignment.
			 **/
			virtual Qt::Alignment getAlignment() const;

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
			virtual void setFont(QString font);

			/**
			 * \brief Set the alignment for the text.
			 *
			 * For more information on the available
			 * values, see 
			 * [`Qt::Alignment`](http://qt-project.org/doc/qt-4.8/qt.html#AlignmentFlag-enum).
			 *
			 * By default, the alignment is
			 * `Qt::AlignHCenter | Qt::AlignVCenter`.
			 *
			 * \param alignment The desired alignment.
			 **/
			virtual void setAlignment(Qt::Alignment alignment);

		private:
			TextPanePrivate* d;
	};
}

#endif