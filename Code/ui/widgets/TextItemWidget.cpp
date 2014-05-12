// header file
#include "TextItemWidget.h"

// debug
#include "debug_macros/debug.h"

// for determining minimum size
#include <QFontMetrics>
#include <cmath>

// for painting
#include <QStyle>
#include <QPainter>
#include <QPalette>
#include <QColor>

using namespace UI;

TextItemWidget::TextItemWidget(QWidget* parent, QString text, QFont font,
								bool highlightable)
	:	ItemWidget(parent, highlightable),
		myText(text),
		myFont(font),
		myAlignment(Qt::AlignLeft | Qt::AlignTop),
		myFitInSize(-1, -1)
{
	QFontMetrics met(myFont);
	setMinimumHeight(met.height() + 20);
}

bool TextItemWidget::fixSizeToFitIn(QSize size)
{
	myFitInSize = size;
	if (size.width() < 0 || size.height() < 0)
	{
		setMinimumWidth(0);
		setFont(myFont);
		return true;
	}
	int h = heightForWidth(size.width());
	int takeOff = (isHighlightable()) ? 21 : 1;
	QFontMetrics met(myFont);
	int w = met.boundingRect(0, 0, 16777215, h - takeOff,
				myAlignment | Qt::TextWordWrap,
				myText).width() + takeOff;
	setMinimumSize(w, h);
	setMaximumSize(size.width(), h);
	update();
	return h <= size.height();
}

QSize TextItemWidget::getSizeToFitIn() const
{
	return myFitInSize;
}

int TextItemWidget::heightForWidth(int w) const
{
	QFontMetrics met(myFont);
	int takeOff = (isHighlightable()) ? 21 : 1;
	int ans = met.boundingRect(0, 0, w - takeOff, 16777215, 
				myAlignment | Qt::TextWordWrap, 
				myText).height() + takeOff;
	return ans;
}

QString TextItemWidget::getItemType() const
{
	return "Text Item";
}

QString TextItemWidget::getText() const
{
	return myText;
}

QFont TextItemWidget::getFont() const
{
	return myFont;
}

void TextItemWidget::setAlignment(int alignment)
{
	myAlignment = alignment;
	setFont(myFont);
}

int TextItemWidget::getAlignment() const
{
	return myAlignment;
}

void TextItemWidget::setText(QString text)
{
	myText = text;
	setFont(myFont);
}

void TextItemWidget::setFont(QFont font)
{
	myFont = font;
	QFontMetrics met(font);
	if (myFitInSize.width() < 0 || myFitInSize.height() < 0)
	{
		setMinimumHeight(heightForWidth(width()));
	}
	update();
}

void TextItemWidget::resizeEvent(QResizeEvent* event)
{
	ItemWidget::resizeEvent(event);
	setFont(myFont);
}

void TextItemWidget::paintEvent(QPaintEvent* event)
{
	if (isHighlighted())
	{
		paintBackground(event);
	}
	QPainter p(this);
	p.setFont(myFont);
	// paint the text
	int loc = (isHighlightable()) ? 10 : 0;
	int takeOff = (isHighlightable()) ? 21 : 1;
	QRectF drawInMe(loc, loc, width() - takeOff, height() - takeOff);
	p.drawText(drawInMe, myAlignment | Qt::TextWordWrap, myText);
	if (isHighlighted())
	{
		paintOutline(event);
	}
}