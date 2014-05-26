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
					pen(other.pen),
					fontMetrics(other.fontMetrics)
				{ }

			QFont font;
			QPen pen;
			QFontMetrics fontMetrics;
	};
}

using namespace UI;
using namespace JSON;

ColoredFont::ColoredFont(QFont font, QPen pen)
	:	d(new ColoredFontPrivate)
{
	d->font = font;
	d->pen = pen;
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

QPen ColoredFont::getPen() const
{
	return d->pen;
}

void ColoredFont::setPen(QPen pen)
{
	d->pen = pen;
}

QFontMetrics ColoredFont::getFontMetrics() const
{
	return d->fontMetrics;
}