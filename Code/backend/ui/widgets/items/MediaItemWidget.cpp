// header file
#include "MediaItemWidget.h"

// for getting the normal font size
#include "settings/AWEMC.h"

using namespace AWE;

namespace UI
{
	class MediaItemWidgetPrivate
	{
		public:
			// parent
			MediaItemWidget* p;

			// Helper function to switch display modes.
			inline void enactDisplayMode();

			// The media item.
			MediaItem* mediaItem;

			// The display mode.
			MediaItemWidget::DisplayMode displayMode;

			// The layout for the name and icon.
			QBoxLayout* layout;

			// The name of the item.
			TextItemWidget* name;

			// The icon of the item.
			ImageItemWidget* icon;

			// The size to fit in.
			QSize fitInSize;
	};
}

using namespace UI;

MediaItemWidget::MediaItemWidget(QWidget* parent, MediaItem* item,
									bool highlightable)
	:	ItemWidget(parent, highlightable),
		d(new MediaItemWidgetPrivate)
{
	d->p = this;
	// make everything
	d->mediaItem = item;
	d->displayMode = NameOnly;
	d->layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	d->name = new TextItemWidget(this, "", "normal");
	d->icon = new ImageItemWidget(this, -1, "");
	fixSizeToFitIn(QSize(-1, -1));

	// get the icon and name
	setMediaItem(item);
	// set up the layout
	d->layout->setContentsMargins(0, 0, 0, 0);
	d->layout->addWidget(d->name);
	d->layout->addWidget(d->icon);
	// make connections for propogating click events
	auto respondToClick = [this] ()
		{
			// indicate that this was clicked
			emit clicked();
			// highlight this item
			setHighlighting(!isHighlighted());
		};

	auto respondToDoubleClick = [this] ()
		{
			// indicate that this was double-clicked
			emit doubleClicked();
			// indicate that this item was selected
			if (isHighlightable())
			{
				emit selected();
				emit selected(this);
			}
		};

	connect(d->name, &ItemWidget::clicked,
			this, respondToClick);
	connect(d->name, &ItemWidget::doubleClicked,
			this, respondToDoubleClick);
	connect(d->icon, &ItemWidget::clicked,
			this, respondToClick);
	connect(d->icon, &ItemWidget::doubleClicked,
			this, respondToDoubleClick);

	setDisplayMode(getDisplayMode());
}

bool MediaItemWidget::fixSizeToFitIn(QSize size)
{
	d->fitInSize = size;
	if (size.width() < 0 || size.height() < 0)
	{
		d->fitInSize.setWidth(-1);
		d->fitInSize.setHeight(-1);
		d->icon->fixSizeToFitIn(d->fitInSize);
		d->name->fixSizeToFitIn(d->fitInSize);
		setMinimumSize(0, 0);
		setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
		return true;
	}
	bool ans;
	int left, top, right, bottom;
	getContentsMargins(&left, &top, &right, &bottom);
	int minw, minh;
	switch (d->displayMode)
	{
		case IconOnly:
			// set to the icon's size if it is valid
			if (!d->icon->getImage().isNull())
			{
				ans = d->icon->fixSizeToFitIn(QSize(
					size.width() - left - right,
					size.height() - top - bottom));
				minw = d->icon->minimumWidth() + left + right;
				minh = d->icon->minimumHeight() + top + bottom;
				break;
			}
			// set it to the text instead
		case NameOnly:
			// set to the text's size
			ans = d->name->fixSizeToFitIn(QSize(
				size.width() - left - right,
				size.height() - top - bottom));
			minw = d->name->minimumWidth() + left + right;
			minh = d->name->minimumHeight() + top + bottom;
			break;
		case NameAndIconLeftToRight:
			ans = false;
			// todo
			//break;
		case NameAndIconTopToBottom:
			ans = false;
			// todo
			//break;
		default:
			minw = 0;
			minh = 0;
			break;
	}
	if (minw > QWIDGETSIZE_MAX)
	{
		minw = QWIDGETSIZE_MAX;
	}
	if (minh > QWIDGETSIZE_MAX)
	{
		minh = QWIDGETSIZE_MAX;
	}
	setMinimumSize(minw, minh);
	setMaximumSize(d->fitInSize);
	return ans;
}

QSize MediaItemWidget::getSizeToFitIn() const
{
	return d->fitInSize;
}

QString MediaItemWidget::getItemType() const
{
	return "Media Item";
}

MediaItemWidget* MediaItemWidget::makeCopy() const
{
	MediaItemWidget* ans = new MediaItemWidget(nullptr,
		getMediaItem(), isHighlightable());
	ans->setDisplayMode(getDisplayMode());
	return ans;
}

void MediaItemWidget::setDisplayMode(DisplayMode mode)
{
	d->displayMode = mode;
	switch (d->displayMode)
	{
		case NameAndIconLeftToRight:
		case NameOnly:
			d->name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			break;
		case IconOnly:
			d->name->setAlignment(Qt::AlignCenter);
			break;
		case NameAndIconTopToBottom:
			d->name->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	}
	fixSizeToFitIn(d->fitInSize);
	d->enactDisplayMode();
}

MediaItemWidget::DisplayMode MediaItemWidget::getDisplayMode() const
{
	return d->displayMode;
}

MediaItem* MediaItemWidget::getMediaItem() const
{
	return d->mediaItem;
}

void MediaItemWidget::setMediaItem(MediaItem* item)
{
	// disconnect old media item connections
	if (d->mediaItem)
	{
		disconnect(d->mediaItem, 0, this, 0);
	}
	d->mediaItem = item;
	// make connections for changing the icon image and name
	auto respondToIconChange = [this] (int index)
		{
			d->icon->setImage(d->mediaItem->getDefaultIcon());
			d->icon->setIndex(index);
		};
	auto respondToNameChange = [this] (QString name)
		{
			d->name->setText(name);
		};
	connect(d->mediaItem, &MediaItem::defaultIconChanged,
			this, respondToIconChange);

	connect(d->mediaItem, &MediaItem::nameChanged,
			this, respondToNameChange);

	// set the name
	respondToNameChange(item->getName());
	// set the icon
	respondToIconChange(item->getDefaultIconIndex());
}

void MediaItemWidgetPrivate::enactDisplayMode()
{
	switch (displayMode)
	{
		case MediaItemWidget::IconOnly:
			if (!icon->getImage().isNull())
			{
				layout->removeWidget(name);
				layout->addWidget(icon);
				name->hide();
				icon->show();
				break;
			}
			// null icon means go with name only
		case MediaItemWidget::NameOnly:
			layout->removeWidget(icon);
			layout->addWidget(name);
			icon->hide();
			name->show();
			break;
		case MediaItemWidget::NameAndIconLeftToRight:
			layout->setDirection(QBoxLayout::RightToLeft);
			layout->removeWidget(name);
			layout->removeWidget(icon);
			layout->addWidget(icon, 1);
			layout->addWidget(name, 5);
			icon->show();
			name->show();
			break;
		case MediaItemWidget::NameAndIconTopToBottom:
			layout->setDirection(QBoxLayout::BottomToTop);
			layout->removeWidget(name);
			layout->removeWidget(icon);
			layout->addWidget(icon, 5);
			layout->addWidget(name, 1);
			icon->show();
			name->show();
			break;
		default:
			break;
	}
	p->update();
}