// header file
#include "TransparentScrollArea.h"

// for changing the background color
#include <QColor>
#include <QPalette>

using namespace UI;

TransparentScrollArea::TransparentScrollArea(QWidget* parent)
	:	QScrollArea(parent)
{
	// change the palette's background color to be
	// completely transparent
	QPalette p = viewport()->palette();
	QColor transparent("white"); // actual color doesn't matter
	transparent.setAlpha(0); // because now you won't see it anyway
	p.setColor(QPalette::Window, transparent);
	viewport()->setPalette(p);
	// now get rid of the frame
	setFrameShape(QFrame::NoFrame);
}