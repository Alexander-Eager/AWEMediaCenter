// header file
#include "TextPane.h"

// for painting
#include <QStyle>
#include <QPainter>
#include <QPalette>

using namespace UI;

TextPane::TextPane(QWidget* parent, QString text, QFont font)
	:	Pane(parent),
		myText(text),
		myFont(font),
		myAlignment(Qt::AlignHCenter | Qt::AlignVCenter),
		myMinimumWidth(0),
		mySizeHint(0, 0)
{
	// set minimum size and size hint
	adjustMinimumSize();
}

void TextPane::adjustMinimumSize()
{
	QFontMetrics m(myFont);
	// set the minimum size
	int w = (width() > myMinimumWidth) ? width() : myMinimumWidth;
	QRect r = m.boundingRect(10, 10, w - 20, height() - 20,
								myAlignment | Qt::TextWordWrap, myText);
	setMinimumSize(myMinimumWidth, r.height() + 20);
	// set the size hint
	int textWidth = m.width(myText);
	mySizeHint.setWidth(textWidth);
}

QSize TextPane::sizeHint() const
{
	return mySizeHint;
}

void TextPane::setAlignment(int alignment)
{
	myAlignment = alignment;
	update();
}

void TextPane::setMinimumTextWidth(int width)
{
	myMinimumWidth = width;
	adjustMinimumSize();
	update();
}

void TextPane::setText(QString text)
{
	myText = text;
	update();
}

QString TextPane::getText()
{
	return myText;
}

void TextPane::setFont(QFont font)
{
	myFont = font;
	adjustMinimumSize();
	update();
}

void TextPane::resizeEvent(QResizeEvent*)
{
	adjustMinimumSize();
}

void TextPane::paintEvent(QPaintEvent* event)
{
	Pane::paintEvent(event);
	// paint the text
	QPainter p(this);
	p.setFont(myFont);
	QRectF drawInMe(10, 10, width() - 20, height() - 20);
	p.drawText(drawInMe, myAlignment | Qt::TextWordWrap, myText);
}