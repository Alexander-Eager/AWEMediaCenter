// header file
#include "ImagePane.h"

// widgets and layouts to be used
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "ui/widgets/items/ImageItemWidget.h"
#include "ui/widgets/collection/ItemListWidget.h"

using namespace AWE;

namespace UI
{
	class ImagePanePrivate : public QObject
	{
		public:
			// The item to display images for.
			MediaItem* mediaItem;

			// The main layout of this widget.
			QVBoxLayout* mainLayout;

			// The icon image displayed.
			ImageItemWidget* currentIcon;

			// The list of icon images the user can choose from.
			ItemListWidget* iconList;

			// The fanart image displayed.
			ImageItemWidget* currentFanart;

			// The list of fanart images the user can choose from.
			ItemListWidget* fanartList;
	};
}

using namespace UI;

ImagePane::ImagePane(QWidget* parent)
	:	Pane(parent),
		d(new ImagePanePrivate)
{
	/* Create everything */
	d->mediaItem = nullptr;
	d->mainLayout = new QVBoxLayout(this);
	d->currentIcon = new ImageItemWidget(this, -1, QPixmap());
	d->iconList = new ItemListWidget(this, true, false);
	d->currentFanart = new ImageItemWidget(this, -1, QPixmap());
	d->fanartList = new ItemListWidget(this, true, false);

	/* set up layouts/widgets */
	d->iconList->setItemAlignment(ItemListWidget::MiddleAlign);
	d->fanartList->setItemAlignment(ItemListWidget::MiddleAlign);
	d->mainLayout->addWidget(d->currentIcon, 4);
	d->mainLayout->addWidget(d->iconList, 1);
	d->mainLayout->addWidget(d->currentFanart, 2);
	d->mainLayout->addWidget(d->fanartList, 1);

	/* connections */
	connect(d->iconList, &ItemListWidget::itemSelected,
		[this] (ItemWidget* item)
		{
			ImageItemWidget* image = (ImageItemWidget*) item;
			d->mediaItem->setDefaultIconIndex(image->getIndex());
			emit iconChanged(image->getImage());
		} );

	connect(d->fanartList, &ItemListWidget::itemSelected,
		[this] (ItemWidget* item)
		{
			ImageItemWidget* image = (ImageItemWidget*) item;
			d->mediaItem->setDefaultFanartIndex(image->getIndex());
			emit fanartChanged(image->getImage());
		} );

	connect(d->iconList, &ItemListWidget::itemHighlighted,
		[this] (ItemWidget* item)
		{
			ImageItemWidget* image = (ImageItemWidget*) item;
			d->currentIcon->setImage(image->getImage());
			d->currentIcon->setIndex(image->getIndex());
		} );

	connect(d->fanartList, &ItemListWidget::itemHighlighted,
		[this] (ItemWidget* item)
		{
			ImageItemWidget* image = (ImageItemWidget*) item;
			d->currentFanart->setImage(image->getImage());
			d->currentFanart->setIndex(image->getIndex());
		} );
}

ImagePane::~ImagePane()
{
	delete d->currentIcon;
	delete d->iconList;
	delete d->currentFanart;
	delete d->fanartList;
	delete d->mainLayout;
	delete d;
}

void ImagePane::setItem(MediaItem* item)
{
	// clear everything
	d->iconList->clear();
	d->fanartList->clear();
	// set the item
	d->mediaItem = item;
	// icon images
	for (int i = 0; i < item->numIcons(); ++ i)
	{
		ImageItemWidget* item = new ImageItemWidget(d->iconList, i,
			d->mediaItem->getIcon(i), true, QSize(d->iconList->height(), 0));
		d->iconList->addItem(item);
	}
	d->currentIcon->setImage(d->mediaItem->getDefaultIcon());
	d->currentIcon->setIndex(d->mediaItem->getDefaultIconIndex());
	emit iconChanged(d->mediaItem->getDefaultIcon());
	// fanart images
	for (int i = 0; i < item->numFanarts(); ++ i)
	{
		ImageItemWidget* item = new ImageItemWidget(d->fanartList, i,
			d->mediaItem->getFanart(i), true, QSize(d->fanartList->height(), 0));
		d->fanartList->addItem(item);
	}
	d->currentFanart->setImage(d->mediaItem->getDefaultFanart());
	d->currentFanart->setIndex(d->mediaItem->getDefaultFanartIndex());
	emit fanartChanged(d->mediaItem->getDefaultFanart());
}