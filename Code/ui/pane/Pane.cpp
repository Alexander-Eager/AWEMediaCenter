// header file
#include "Pane.h"

// debug
#include "debug_macros/debug.h"

// for painting
#include <QColor>
#include <QRadialGradient>
#include <QPalette>
#include <QPainter>
#include <cmath>

using namespace UI;

Pane::Pane(QWidget* parent)
	:	QWidget(parent)
{
	setMinimumSize(20, 20);
}

void Pane::paintEvent(QPaintEvent*)
{
	// set up the gradient settings
	qreal radius = sqrt(height() * height()
						+ width() * width()) / 2;
	QRadialGradient gradient(0, 0, radius, width()/4.0, height()/4.0);
	// get the gradient colors
	QColor firstColor("darkgray");
	firstColor.setAlpha(200);
	QColor secondColor("gray");
	secondColor.setAlpha(200);
	// set them
	gradient.setColorAt(0, firstColor);
	gradient.setColorAt(1, secondColor);
	// draw it
	QBrush background(gradient);
	QPainter painter(this);
	painter.setBrush(background);
	painter.setPen(Qt::NoPen);
	painter.drawRoundedRect(rect(), 10, 10, Qt::AbsoluteSize);
}