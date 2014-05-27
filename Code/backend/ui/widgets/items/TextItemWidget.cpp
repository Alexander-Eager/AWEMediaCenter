// header file
#include "TextItemWidget.h"

// global settings
#include "settings/AWEMC.h"

// for determining minimum size
#include <cmath>

// for painting
#include "skin/ColoredFont.h"
#include <QStyle>
#include <QPainter>
#include <QPalette>
#include <QColor>

namespace UI
{
	class TextItemWidgetPrivate
	{
		public:
			// The text to display.
			QString text;

			// The font to use.
			QString font;

			// The alignment of text.
			Qt::Alignment alignment;

			// The containing size.
			QSize fitInSize;
	};
}

using namespace UI;
using namespace AWE;

TextItemWidget::TextItemWidget(QWidget* parent, QString text, QString font,
								bool highlightable)
	:	ItemWidget(parent, highlightable),
		d(new TextItemWidgetPrivate)
{
	d->text = text;
	d->alignment = Qt::AlignLeft | Qt::AlignTop;
	d->fitInSize = QSize(-1, -1);

	setFont(font);
	connect(AWEMC::settings(), &GlobalSettings::skinChanged,
			this,	[this] ()
					{
						setFont(d->font);
					} );
}

bool TextItemWidget::fixSizeToFitIn(QSize size)
{
	d->fitInSize = size;
	if (size.width() < 0 || size.height() < 0)
	{
		setMinimumWidth(0);
		setFont(d->font);
		return true;
	}
	int h = heightForWidth(size.width());
	int takeOff = (isHighlightable()) ? 21 : 1;
	ColoredFont cf = AWEMC::settings()->getCurrentSkin()
		->getFont(getFont());
	QFontMetrics met = cf.getFontMetrics();
	int w = met.boundingRect(0, 0, 16777215, h - takeOff,
				d->alignment | Qt::TextWordWrap,
				d->text).width() + takeOff;
	setMinimumSize(w, h);
	setMaximumSize(size.width(), h);
	update();
	return h <= size.height();
}

QSize TextItemWidget::getSizeToFitIn() const
{
	return d->fitInSize;
}

int TextItemWidget::heightForWidth(int w) const
{
	ColoredFont cf = AWEMC::settings()->getCurrentSkin()
		->getFont(getFont());
	QFontMetrics met = cf.getFontMetrics();
	int takeOff = (isHighlightable()) ? 21 : 1;
	int ans = met.boundingRect(0, 0, w - takeOff, 16777215, 
				d->alignment | Qt::TextWordWrap, 
				d->text).height() + takeOff;
	return ans;
}

QString TextItemWidget::getItemType() const
{
	return "Text Item";
}

TextItemWidget* TextItemWidget::makeCopy() const
{
	return new TextItemWidget(parentWidget(), getText(),
		getFont(), isHighlightable());
}

QString TextItemWidget::getText() const
{
	return d->text;
}

QString TextItemWidget::getFont() const
{
	return d->font;
}

void TextItemWidget::setAlignment(Qt::Alignment alignment)
{
	d->alignment = alignment;
	setFont(d->font);
}

Qt::Alignment TextItemWidget::getAlignment() const
{
	return d->alignment;
}

void TextItemWidget::setText(QString text)
{
	d->text = text;
	setFont(d->font);
}

void TextItemWidget::setFont(QString font)
{
	d->font = font;
	if (d->fitInSize.width() < 0 || d->fitInSize.height() < 0)
	{
		setMinimumHeight(heightForWidth(width()));
	}
	update();
}

void TextItemWidget::resizeEvent(QResizeEvent* event)
{
	ItemWidget::resizeEvent(event);
	setFont(d->font);
}

void TextItemWidget::paintEvent(QPaintEvent* event)
{
	ItemWidget::paintEvent(event);
	// make the painter with the correct font/color
	QPainter p(this);
	ColoredFont cf = AWEMC::settings()->getCurrentSkin()
		->getFont(d->font);
	p.setFont(cf.getFont());
	p.setPen(cf.getPen());
	// paint the text
	int left, top, right, bottom;
	getContentsMargins(&left, &top, &right, &bottom);
	QRectF drawInMe(left, top, width() - left - right - 1,
		height() - top - bottom - 1);
	p.drawText(drawInMe, d->alignment | Qt::TextWordWrap, d->text);
}