// header file
#include "ImageItemWidget.h"

// for painting
#include <QPainter>

namespace UI
{
	class ImageItemWidgetPrivate
	{
		public:
			// parent
			ImageItemWidget* p;

			// Helper function that scales the image.
			inline void makeImageIcon(QSize size);
			
			// The index of this file in the item's config file.
			int index;

			// The image (in full size).
			QPixmap image;

			// The icon (scaled down).
			QPixmap iconImage;

			// The aspect ratio mode.
			Qt::AspectRatioMode ratioMode;

			// The target icon size.
			QSize fitInSize;
	};
}

using namespace UI;

ImageItemWidget::ImageItemWidget(QWidget* parent, int index, QString file,
									bool highlightable, QSize size)
	:	ItemWidget(parent, highlightable),
		d(new ImageItemWidgetPrivate)
{
	d->p = this;
	// make everything
	d->index = index;
	d->ratioMode = Qt::KeepAspectRatio;

	fixSizeToFitIn(size);
	setImage(file);
}

ImageItemWidget::ImageItemWidget(QWidget* parent, int index, QPixmap image,
									bool highlightable, QSize size)
	:	ItemWidget(parent, highlightable),
		d(new ImageItemWidgetPrivate)
{
	d->p = this;
	// make everything
	d->index = index;
	d->ratioMode = Qt::KeepAspectRatio;

	fixSizeToFitIn(size);
	setImage(image);
}

ImageItemWidget::~ImageItemWidget()
{
	delete d;
}

bool ImageItemWidget::fixSizeToFitIn(QSize size)
{
	d->fitInSize = size;
	if (size.width() < 0 || size.height() < 0)
	{
		d->fitInSize.setWidth(-1);
		d->fitInSize.setHeight(-1);
		setMinimumSize(0, 0);
		setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
		return true;
	}
	int left, top, right, bottom;
	getContentsMargins(&left, &top, &right, &bottom);
	d->makeImageIcon(QSize(size.width() - left - right,
		size.height() - top - bottom));
	setMaximumSize(d->iconImage.width() + left + right,
		d->iconImage.height() + top + bottom);
	setMinimumSize(d->iconImage.width() + left + right,
		d->iconImage.height() + top + bottom);
	return true;
}

QSize ImageItemWidget::getSizeToFitIn() const
{
	return d->fitInSize;
}

int ImageItemWidget::heightForWidth(int w) const
{
	QSize imageSize(d->image.size());
	imageSize.scale(QSize(w, QWIDGETSIZE_MAX), Qt::KeepAspectRatio);
	return imageSize.height();
}

void ImageItemWidget::setAspectRatioMode(Qt::AspectRatioMode mode)
{
	d->ratioMode = mode;
	setImage(getImage());
}

Qt::AspectRatioMode ImageItemWidget::getAspectRatioMode() const
{
	return d->ratioMode;
}

QString ImageItemWidget::getItemType() const
{
	return "Image Item";
}

ImageItemWidget* ImageItemWidget::makeCopy() const
{
	return new ImageItemWidget(nullptr, getIndex(),
		getImage(), isHighlightable(), getSizeToFitIn());
}

QPixmap ImageItemWidget::getImage() const
{
	return d->image;
}

int ImageItemWidget::getIndex() const
{
	return d->index;
}

void ImageItemWidget::setImage(QString file)
{
	setImage(QPixmap(file));
}

void ImageItemWidget::setImage(QPixmap image)
{
	d->image = image;
	int left, top, right, bottom;
	getContentsMargins(&left, &top, &right, &bottom);
	if (d->fitInSize.width() < 0)
	{
		d->makeImageIcon(QSize(width() - left - right,
			height() - top - bottom));
	}
	else
	{
		d->makeImageIcon(QSize(d->fitInSize.width() - left - right,
			d->fitInSize.height() - top - bottom));
	}
}

void ImageItemWidget::setIndex(int index)
{
	d->index = index;
}

void ImageItemWidget::paintEvent(QPaintEvent* event)
{
	ItemWidget::paintEvent(event);
	QPainter p(this);
	p.drawPixmap(QPointF(width() / 2.0 - d->iconImage.width() / 2.0,
		height() / 2.0 - d->iconImage.height() / 2.0),
		d->iconImage);
}

void ImageItemWidget::resizeEvent(QResizeEvent* event)
{
	ItemWidget::resizeEvent(event);
	if (d->fitInSize.width() < 0)
	{
		int left, top, right, bottom;
		getContentsMargins(&left, &top, &right, &bottom);
		d->makeImageIcon(QSize(width() - left - right,
			height() - top - bottom));
	}
}

void ImageItemWidgetPrivate::makeImageIcon(QSize size)
{
	int w = image.width();
	int h = image.height();
	if (w == 0 || h == 0)
	{
		iconImage = QPixmap(0, 0);
		iconImage.fill(QColor(0, 0, 0, 0));
	}
	else
	{
		QSize iconSize(w, h);
		iconSize.scale(size, ratioMode);
		iconImage = image.scaled(iconSize, ratioMode,
			Qt::SmoothTransformation);
	}
	p->update();
}