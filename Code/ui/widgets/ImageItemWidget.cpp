// header file
#include "ImageItemWidget.h"

// debug
#include "debug_macros/debug.h"

// for painting
#include <QPainter>

using namespace UI;

ImageItemWidget::ImageItemWidget(QWidget* parent, int index, QDir file,
									bool highlightable, QSize size)
	:	ItemWidget(parent, highlightable),
		myIndex(index),
		myImage(),
		myRatioMode(Qt::KeepAspectRatio),
		myFitInSize(size)
{
	fixSizeToFitIn(size);
	setImage(file);
}

ImageItemWidget::ImageItemWidget(QWidget* parent, int index, QPixmap image,
									bool highlightable, QSize size)
	:	ItemWidget(parent, highlightable),
		myIndex(index),
		myImage(),
		myRatioMode(Qt::KeepAspectRatio),
		myFitInSize(size)
{
	fixSizeToFitIn(size);
	setImage(image);
}

bool ImageItemWidget::fixSizeToFitIn(QSize size)
{
	myFitInSize = size;
	if (size.width() < 0 || size.height() < 0)
	{
		setMinimumSize(0, 0);
		setMaximumSize(16777215, 16777215);
		return true;
	}
	int takeOff = (isHighlightable()) ? 20 : 0;
	makeImageIcon(QSize(size.width() - takeOff, size.height() - takeOff));
	setMaximumSize(myIconImage.width() + takeOff, myIconImage.height() + takeOff);
	setMinimumSize(myIconImage.width() + takeOff, myIconImage.height() + takeOff);
	return true;
}

QSize ImageItemWidget::getSizeToFitIn() const
{
	return myFitInSize;
}

int ImageItemWidget::heightForWidth(int w) const
{
	QSize size(w, 16777215);
	QSize imageSize(myImage.size());
	imageSize.scale(size, Qt::KeepAspectRatio);
	return imageSize.height();
}

void ImageItemWidget::setAspectRatioMode(Qt::AspectRatioMode mode)
{
	myRatioMode = mode;
}

Qt::AspectRatioMode ImageItemWidget::getAspectRatioMode() const
{
	return myRatioMode;
}

QString ImageItemWidget::getItemType() const
{
	return "Image Item";
}

QPixmap ImageItemWidget::getImage() const
{
	return myImage;
}

int ImageItemWidget::getIndex() const
{
	return myIndex;
}

void ImageItemWidget::setImage(QDir file)
{
	setImage(QPixmap(file.absolutePath()));
}

void ImageItemWidget::setImage(QPixmap image)
{
	myImage = image;
	int takeOff = (isHighlightable()) ? 20 : 0;
	if (myFitInSize.width() < 0 || myFitInSize.height() < 0)
	{
		makeImageIcon(QSize(width() - takeOff,
							height() - takeOff));
	}
	else
	{
		makeImageIcon(QSize(myFitInSize.width() - takeOff,
							myFitInSize.height() - takeOff));
	}
}

void ImageItemWidget::makeImageIcon(QSize size)
{
	int w = myImage.width();
	int h = myImage.height();
	if (w == 0 || h == 0)
	{
		QColor c("white");
		c.setAlpha(0);
		myIconImage = QPixmap(0, 0);
		myIconImage.fill(c);
	}
	else
	{
		QSize iconSize(w, h);
		iconSize.scale(size, myRatioMode);
		myIconImage = myImage.scaled(iconSize, myRatioMode,
										Qt::SmoothTransformation);
	}
	update();
}

void ImageItemWidget::setIndex(int index)
{
	myIndex = index;
}

void ImageItemWidget::paintEvent(QPaintEvent* event)
{
	if (isHighlighted())
	{
		paintBackground(event);
		paintOutline(event);
	}
	QPainter p(this);
	int x = width() / 2 - myIconImage.width() / 2;
	int y = height() / 2 - myIconImage.height() / 2;
	p.drawPixmap(x, y, myIconImage);
}

void ImageItemWidget::resizeEvent(QResizeEvent* event)
{
	ItemWidget::resizeEvent(event);
	if (myFitInSize.width() == -1 || myFitInSize.height() == -1)
	{
		int takeOff = (isHighlightable()) ? 20 : 0;
		makeImageIcon(QSize(width() - takeOff, height() - takeOff));
	}
}