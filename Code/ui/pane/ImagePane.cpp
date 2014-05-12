// header file
#include "ImagePane.h"

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace UI;
using namespace Json;

ImagePane::ImagePane(QWidget* parent)
	:	Pane(parent),
		myMediaItem(nullptr),
		myMainLayout(new QVBoxLayout(this)),
		myCurrentIcon(new ImageItemWidget(this, -1, QPixmap(),
							false, QSize(-1, -1))),
		myIconList(new ItemListWidget(this, true, false)),
		myCurrentFanart(new ImageItemWidget(this, -1, QPixmap(),
							false, QSize(-1, -1))),
		myFanartList(new ItemListWidget(this, true, false))
{
	/* set up layouts/widgets */
	myIconList->setItemAlignment(ItemListWidget::MiddleAlign);
	myFanartList->setItemAlignment(ItemListWidget::MiddleAlign);
	myMainLayout->addWidget(myCurrentIcon, 4);
	myMainLayout->addWidget(myIconList, 1);
	myMainLayout->addWidget(myCurrentFanart, 2);
	myMainLayout->addWidget(myFanartList, 1);

	/* connections */
	connect(myIconList, &ItemListWidget::itemSelected,
			this, &ImagePane::respondToIconChange);
	connect(myFanartList, &ItemListWidget::itemSelected,
			this, &ImagePane::respondToFanartChange);
	connect(myIconList, &ItemListWidget::itemHighlighted,
			this, &ImagePane::respondToTempIconChange);
	connect(myFanartList, &ItemListWidget::itemHighlighted,
			this, &ImagePane::respondToTempFanartChange);
}

ImagePane::~ImagePane()
{
	delete myCurrentIcon;
	delete myIconList;
	delete myCurrentFanart;
	delete myFanartList;
	delete myMainLayout;
}

void ImagePane::setItem(MediaItem* item)
{
	// clear everything
	myIconList->clear();
	myFanartList->clear();
	// set the item
	myMediaItem = item;
	// icon images
	for (int i = 0; i < item->numIcons(); ++ i)
	{
		ImageItemWidget* item = new ImageItemWidget(myIconList, i,
										myMediaItem->getIcon(i),
										true, QSize(myIconList->height(), 0));
		myIconList->addItem(item);
	}
	myCurrentIcon->setImage(myMediaItem->getDefaultIcon());
	myCurrentIcon->setIndex(myMediaItem->getDefaultIconIndex());
	//emit iconChanged(QPixmap());
	// fanart images
	for (int i = 0; i < item->numFanarts(); ++ i)
	{
		ImageItemWidget* item = new ImageItemWidget(myFanartList, i,
										myMediaItem->getFanart(i),
										true, QSize(myFanartList->height(), 0));
		myFanartList->addItem(item);
	}
	myCurrentFanart->setImage(myMediaItem->getDefaultFanart());
	myCurrentFanart->setIndex(myMediaItem->getDefaultFanartIndex());
	emit fanartChanged(myMediaItem->getDefaultFanart());
}

void ImagePane::respondToIconChange(ItemWidget* icon)
{
	ImageItemWidget* image = (ImageItemWidget*) icon;
	myMediaItem->setDefaultIconIndex(image->getIndex());
	//emit iconChanged(image->getImage());
}

void ImagePane::respondToFanartChange(ItemWidget* fanart)
{
	ImageItemWidget* image = (ImageItemWidget*) fanart;
	myMediaItem->setDefaultFanartIndex(image->getIndex());
	emit fanartChanged(image->getImage());
}

void ImagePane::respondToTempIconChange(ItemWidget* icon)
{
	ImageItemWidget* image = (ImageItemWidget*) icon;
	myCurrentIcon->setImage(image->getImage());
	myCurrentIcon->setIndex(image->getIndex());
}

void ImagePane::respondToTempFanartChange(ItemWidget* fanart)
{
	ImageItemWidget* image = (ImageItemWidget*) fanart;
	myCurrentFanart->setImage(image->getImage());
	myCurrentFanart->setIndex(image->getIndex());
}