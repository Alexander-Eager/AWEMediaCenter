// header file
#include "MediaItemWidget.h"

// for getting the normal font size
#include "settings/AWEMC.h"

using namespace AWE;
using namespace UI;

MediaItemWidget::MediaItemWidget(QWidget* parent, MediaItem* item,
									bool highlightable)
	:	ItemWidget(parent, highlightable),
		myMediaItem(item),
		myDisplayMode(NameOnly),
		myLayout(new QBoxLayout(QBoxLayout::TopToBottom, this)),
		myName(new TextItemWidget(this, "", "normal")),
		myIcon(new ImageItemWidget(this, -1, QDir(""))),
		myFitInSize(-1, -1)
{
	// get the icon and name
	setMediaItem(item);
	// set up the layout
	setContentsMargins(10, 10, 10, 10);
	myLayout->setContentsMargins(0, 0, 0, 0);
	myLayout->addWidget(myName);
	myLayout->addWidget(myIcon);
	// make connections for propogating click events
	connect(myName, &ItemWidget::clicked,
			this, &MediaItemWidget::respondToClick);
	connect(myName, &ItemWidget::doubleClicked,
			this, &MediaItemWidget::respondToDoubleClick);
	connect(myIcon, &ItemWidget::clicked,
			this, &MediaItemWidget::respondToClick);
	connect(myIcon, &ItemWidget::doubleClicked,
			this, &MediaItemWidget::respondToDoubleClick);
	setDisplayMode(getDisplayMode());
}

bool MediaItemWidget::fixSizeToFitIn(QSize size)
{
	myFitInSize = size;
	bool ans;
	int minw, minh;
	switch (myDisplayMode)
	{
		case IconOnly:
			// set to the icon's size if it is valid
			if (!myIcon->getImage().isNull())
			{
				ans = myIcon->fixSizeToFitIn(QSize(size.width() - 20,
													size.height() - 20));
				minw = myIcon->minimumWidth() + 20;
				minh = myIcon->minimumHeight() + 20;
				break;
			}
			// set it to the text instead
		case NameOnly:
			// set to the text's size
			ans = myName->fixSizeToFitIn(QSize(size.width() - 20,
												size.height() - 20));
			minw = (myName->minimumWidth()) ? 
					myName->minimumWidth() : myName->maximumWidth();
			minw += 20;
			minh = myName->minimumHeight() + 20;
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
	if (minw > 16777215)
	{
		minw = 16777215;
	}
	if (minh > 16777215)
	{
		minh = 16777215;
	}
	setMinimumSize(minw, minh);
	if (size.width() == -1 || size.height() == -1)
	{
		setMaximumSize(16777215, 16777215);
	}
	else
	{
		setMaximumSize(size.width(), size.height());
	}
	return ans;
}

QSize MediaItemWidget::getSizeToFitIn() const
{
	return myFitInSize;
}

QString MediaItemWidget::getItemType() const
{
	return "Media Item";
}

MediaItemWidget* MediaItemWidget::makeCopy() const
{
	MediaItemWidget* ans = new MediaItemWidget(parentWidget(),
		getMediaItem(), isHighlightable());
	ans->setDisplayMode(getDisplayMode());
	return ans;
}

void MediaItemWidget::setDisplayMode(DisplayMode mode)
{
	myDisplayMode = mode;
	switch (myDisplayMode)
	{
		case NameAndIconLeftToRight:
		case NameOnly:
			myName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
			break;
		case IconOnly:
			myName->setAlignment(Qt::AlignCenter);
			break;
		case NameAndIconTopToBottom:
			myName->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	}
	fixSizeToFitIn(myFitInSize);
	enactDisplayMode();
}

MediaItemWidget::DisplayMode MediaItemWidget::getDisplayMode() const
{
	return myDisplayMode;
}

MediaItem* MediaItemWidget::getMediaItem() const
{
	return myMediaItem;
}

void MediaItemWidget::setMediaItem(MediaItem* item)
{
	// disconnect old media item connections
	if (myMediaItem)
	{
		disconnect(myMediaItem, 0, this, 0);
	}
	myMediaItem = item;
	// make connections for changing the icon image and name
	connect(myMediaItem, &MediaItem::defaultIconChanged,
			this, &MediaItemWidget::respondToIconChange);
	connect(myMediaItem, &MediaItem::nameChanged,
			this, &MediaItemWidget::respondToNameChange);
	// set the name
	respondToNameChange(item->getName());
	// set the icon
	respondToIconChange(item->getDefaultIconIndex());
}

void MediaItemWidget::respondToClick()
{
	// indicate that this was clicked
	emit clicked();
	// highlight this item
	setHighlighting(!isHighlighted());
}

void MediaItemWidget::respondToDoubleClick()
{
	// indicate that this was double-clicked
	emit doubleClicked();
	// indicate that this item was selected
	if (isHighlightable())
	{
		emit selected();
		emit selected(this);
	}
}

void MediaItemWidget::respondToIconChange(int index)
{
	myIcon->setImage(myMediaItem->getDefaultIcon());
	myIcon->setIndex(index);
}

void MediaItemWidget::respondToNameChange(QString name)
{
	myName->setText(name);
}

void MediaItemWidget::enactDisplayMode()
{
	switch (myDisplayMode)
	{
		case IconOnly:
			if (!myIcon->getImage().isNull())
			{
				myLayout->removeWidget(myName);
				myLayout->addWidget(myIcon);
				myName->hide();
				myIcon->show();
				break;
			}
			// null icon means go with name only
		case NameOnly:
			myLayout->removeWidget(myIcon);
			myLayout->addWidget(myName);
			myIcon->hide();
			myName->show();
			break;
		case NameAndIconLeftToRight:
			myLayout->setDirection(QBoxLayout::RightToLeft);
			myLayout->removeWidget(myName);
			myLayout->removeWidget(myIcon);
			myLayout->addWidget(myIcon, 1);
			myLayout->addWidget(myName, 5);
			myIcon->show();
			myName->show();
			break;
		case NameAndIconTopToBottom:
			myLayout->setDirection(QBoxLayout::BottomToTop);
			myLayout->removeWidget(myName);
			myLayout->removeWidget(myIcon);
			myLayout->addWidget(myIcon, 5);
			myLayout->addWidget(myName, 1);
			myIcon->show();
			myName->show();
			break;
		default:
			break;
	}
	update();
}