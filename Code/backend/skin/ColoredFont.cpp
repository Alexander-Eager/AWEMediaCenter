// header file
#include "ColoredFont.h"

// for implicit sharing
#include <QSharedData>

namespace UI
{
	class ColoredFontPrivate : public QSharedData
	{
		public:
			ColoredFontPrivate()
				:	fontMetrics(QFont("Helvetica", 12))
				{ }

			~ColoredFontPrivate() { }
			ColoredFontPrivate(const ColoredFontPrivate& other)
				:	font(other.font),
					color(other.color),
					fontMetrics(other.fontMetrics)
				{ }

			QFont font;
			QColor color;
			QFontMetrics fontMetrics;
	};
}

using namespace UI;
using namespace JSON;

ColoredFont::ColoredFont(QFont font, QColor color)
	:	d(new ColoredFontPrivate)
{
	d->font = font;
	d->color = color;
	d->fontMetrics = QFontMetrics(font);
}

ColoredFont::ColoredFont(const ColoredFont& other)
	:	d(other.d)
	{ }

ColoredFont::~ColoredFont() { }

ColoredFont& ColoredFont::operator= (const ColoredFont& other)
{
	if (d == other.d) return *this;
	d = other.d;
	return *this;
}

QFont ColoredFont::getFont() const
{
	return d->font;
}

void ColoredFont::setFont(QFont font)
{
	d->font = font;
	d->fontMetrics = QFontMetrics(font);
}

QColor ColoredFont::getColor() const
{
	return d->color;
}

void ColoredFont::setColor(QColor color)
{
	d->color = color;
}

QFontMetrics ColoredFont::getFontMetrics() const
{
	return d->fontMetrics;
}