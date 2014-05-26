#ifndef COLORED_FONT_H
#define COLORED_FONT_H

// for library
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QObject>

// for holding data
#include <QFont>
#include <QPen>
#include <QFontMetrics>
#include <JsonDataTree/Json.h>

// for implicit sharing
#include <QSharedDataPointer>

namespace UI
{
	// internal data
	class ColoredFontPrivate;

	/**
	 * \brief A simple container class for a font and a color.
	 *
	 * This is used in most of the UI text-based classes to
	 * adjust the font size based on user preferences.
	 *
	 * For all methods for manipulating font details, see
	 * the documentation for `QFont`.
	 **/
	class AWEMC_BACKEND_LIBRARY ColoredFont : public QObject
	{
		Q_OBJECT

		Q_PROPERTY(QFont font
					READ getFont
					WRITE setFont)
		Q_PROPERTY(QFontMetrics fontMetrics
					READ getFontMetrics
					STORED false)
		Q_PROPERTY(QPen pen
					READ getPen
					WRITE setPen)

		public:
			/**
			 * \brief Make a font with the given characteristics.
			 *
			 * \param font The font to use.
			 * \param color The color for the font (defaults to black).
			 **/
			ColoredFont(QFont font = QFont(), QPen color = QColor("black"));

			/**
			 * \brief Make a copy of `other`.
			 *
			 * \param other The colored font to copy.
			 **/
			ColoredFont(const ColoredFont& other);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ColoredFont();

			/**
			 * \brief Assign the font and color of `other`
			 *			to this object.
			 *
			 * \param other The colored font to copy.
			 **/
			ColoredFont& operator= (const ColoredFont& other);

			/**
			 * \brief Get the font.
			 *
			 * \returns The font.
			 **/
			virtual QFont getFont() const;

			/**
			 * \brief Set the font.
			 *
			 * \param font The new font to use.
			 **/
			virtual void setFont(QFont font);

			/**
			 * \brief Get the pen.
			 *
			 * \returns The text's pen.
			 **/
			virtual QPen getPen() const;

			/**
			 * \brief Set the pen.
			 *
			 * \param pen The new pen to use.
			 **/
			virtual void setPen(QPen pen);

			/**
			 * \brief Get the font metrics.
			 *
			 * \returns The font metrics for the current font.
			 **/
			virtual QFontMetrics getFontMetrics() const;

		private:
			QSharedDataPointer<ColoredFontPrivate> d;
	};
}

#endif // COLORED_FONT_H