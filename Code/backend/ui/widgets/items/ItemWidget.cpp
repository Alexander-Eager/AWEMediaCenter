// header file
#include "ItemWidget.h"

// for painting
#include <QColor>
#include <QRadialGradient>
#include <QPalette>
#include <QPainter>

using namespace UI;

ItemWidget::ItemWidget(QWidget* parent, bool canBeHighlighted)
	:	QWidget(parent),
		myHighlighting(false),
		myCanBeHighlighted(canBeHighlighted)
	{ }

ItemWidget::~ItemWidget() { }

bool ItemWidget::isHighlighted() const
{
	return myHighlighting;
}

bool ItemWidget::isHighlightable() const
{
	return myCanBeHighlighted;
}

void ItemWidget::setHighlightable(bool newState)
{
	myCanBeHighlighted = newState;
}

void ItemWidget::highlight()
{
	setHighlighting(true);
}

void ItemWidget::unhighlight()
{
	setHighlighting(false);
}

void ItemWidget::setHighlighting(bool newState)
{
	if (myCanBeHighlighted && myHighlighting != newState)
	{
		// set the new state
		myHighlighting = newState;
		// update the widget's image
		update();
		// emit the appropriate signals
		emit highlightingChanged(newState);
		emit highlightingChanged(newState, this);
		if (newState)
		{
			emit highlighted();
			emit highlighted(this);
		}
		else
		{
			emit unhighlighted();
			emit unhighlighted(this);
		}
	}
}

void ItemWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
	{
		// we only care about left-button clicks,
		// so propogate everything else up the list
		event->ignore();
	}
	else
	{
		// indicate that this was clicked
		emit clicked();
		// highlight this item
		setHighlighting(!isHighlighted());
	}
}

void ItemWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
	{
		// we only care about left-button clicks,
		// so propogate everything else up the list
		event->ignore();
	}
	else
	{
		// indicate that this was double-clicked
		emit doubleClicked();
		// indicate that this item was selected
		if (myCanBeHighlighted)
		{
			emit selected();
			emit selected(this);
		}
	}
}

void ItemWidget::paintBackground(QPaintEvent*)
{
	// make the gradient
	qreal radius = (height() > width()) ? height() : width();
	QPointF center(width() / 2, height() / 2);
	QRadialGradient gradient(center, radius, center);
	// get the gradient colors
	QColor firstColor("lightskyblue");
	firstColor.setAlpha(100);
	QColor secondColor("blue");
	secondColor.setAlpha(100);
	// set them
	gradient.setColorAt(0, firstColor);
	gradient.setColorAt(1, secondColor);
	// draw it
	QBrush background(gradient);
	QPainter painter(this);
	painter.setBrush(background);
	painter.setPen(Qt::NoPen);
	QRect drawInMe(0, 0, width() - 1, height() - 1);
	painter.drawRoundedRect(drawInMe, 10, 10, Qt::AbsoluteSize);
}

void ItemWidget::paintOutline(QPaintEvent*)
{
	QPainter painter(this);
	painter.setBrush(Qt::NoBrush);
	QPen outline(QColor("blue"));
	outline.setStyle(Qt::SolidLine);
	outline.setJoinStyle(Qt::RoundJoin);
	outline.setWidth(1);
	painter.setPen(outline);
	QRect drawInMe(0, 0, width() - 1, height() - 1);
	painter.drawRoundedRect(drawInMe, 10, 10, Qt::AbsoluteSize);
}

void ItemWidget::paintEvent(QPaintEvent* event)
{
	if (isHighlighted())
	{
		paintBackground(event);
		paintOutline(event);
	}
}