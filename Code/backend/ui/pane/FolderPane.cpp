// header file
#include "FolderPane.h"

// widgets and layouts
#include <QWidget>
#include <QStackedLayout>
#include "ui/widgets/items/MediaItemWidget.h"
#include "ui/widgets/collection/ItemListWidget.h"
#include "ui/widgets/collection/ItemGridWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

using namespace AWE;

namespace UI
{
	class FolderPanePrivate
	{
		public:
			/* this is data stuff */
			// The folder whose contents are displayed.
			Folder* folder;

			/* this is UI stuff */
			// The main layout for this widget.
			QVBoxLayout* mainLayout;

			// The back button.
			QPushButton* backButton;

			// View selection menu.
			QComboBox* viewSelectionMenu;

			// The layout to switch between item view modes.
			QStackedLayout* mediaItemLayout;

			// The list of contained media items.
			ItemListWidget* mediaItemList;

			// The grid of contained media items.
			ItemGridWidget* mediaItemGrid;
	};
}

using namespace UI;

FolderPane::FolderPane(QWidget* parent)
	:	Pane(parent),
		d(new FolderPanePrivate)
{
	/* Create everything */
	d->folder = nullptr;
	d->mainLayout = new QVBoxLayout(this);
	d->backButton = new QPushButton(tr("Back"), this);
	d->viewSelectionMenu = new QComboBox(this);
	d->mediaItemLayout = new QStackedLayout;
	d->mediaItemList = new ItemListWidget(this, false, false);
	d->mediaItemGrid = new ItemGridWidget(this, false, false, 3);

	/* set up layouts/widgets */
	d->mainLayout->addWidget(d->backButton);
	d->viewSelectionMenu->addItem("Grid");
	d->viewSelectionMenu->addItem("List");
	d->viewSelectionMenu->setCurrentIndex(0);
	d->mainLayout->addWidget(d->viewSelectionMenu);
	d->mainLayout->addLayout(d->mediaItemLayout);
	d->mediaItemLayout->setContentsMargins(0, 0, 0, 0);
	d->mediaItemLayout->addWidget(d->mediaItemGrid);
	d->mediaItemLayout->addWidget(d->mediaItemList);

	/* connections */
	// item highlight and selection
	auto respondToItemHighlight = [this] (ItemWidget* item)
		{
			emit itemHighlighted(((MediaItemWidget*) item)->getMediaItem());
		};

	auto respondToItemSelected = [this] (ItemWidget* item)
		{
			emit itemSelected(((MediaItemWidget*) item)->getMediaItem());
		};

	connect(d->mediaItemGrid, &ItemGridWidget::itemHighlighted,
			this, respondToItemHighlight);
	connect(d->mediaItemGrid, &ItemGridWidget::itemSelected,
			this, respondToItemSelected);

	// switching view layout
	connect(d->viewSelectionMenu, static_cast<void (QComboBox::*)(int)>
			(&QComboBox::activated), this,
		[this, respondToItemHighlight, respondToItemSelected] (int mode)
		{
			disconnect(d->mediaItemLayout->currentWidget(), 0,
				this, 0);
			d->mediaItemLayout->setCurrentIndex(mode);
			ItemCollectionWidget* coll = (ItemCollectionWidget*)
				d->mediaItemLayout->currentWidget();
			connect(coll, &ItemCollectionWidget::itemHighlighted,
					this, respondToItemHighlight);
			connect(coll, &ItemCollectionWidget::itemSelected,
					this, respondToItemSelected);
		} );

	// back button
	connect(d->backButton, &QPushButton::clicked,
			this,	[this] ()
					{
						emit goUpOne();
					} );
}

FolderPane::~FolderPane()
{
	delete d->mediaItemGrid;
	delete d->mediaItemList;
	delete d->mediaItemLayout;
	delete d->viewSelectionMenu;
	delete d->backButton;
	delete d->mainLayout;
	delete d;
}

void FolderPane::setFolder(Folder* folder)
{
	// quick speed check
	if (d->folder == folder)
	{
		return;
	}
	// set the folder variable
	d->folder = folder;

	/* change the contents of the item list */
	d->mediaItemList->clear();
	d->mediaItemGrid->clear();
	for (int i = 0; i < d->folder->getItems().count(); ++ i)
	{
		// add to the list
		MediaItemWidget* toAdd = new MediaItemWidget(d->mediaItemList,
			d->folder->getItems().at(i), true);
		toAdd->setDisplayMode(MediaItemWidget::NameOnly);
		d->mediaItemList->addItem(toAdd);

		// add to the grid
		MediaItemWidget* toAdd2 = new MediaItemWidget(d->mediaItemGrid,
			d->folder->getItems().at(i), true);
		toAdd2->setDisplayMode(MediaItemWidget::IconOnly);
		d->mediaItemGrid->addItem(toAdd2);

		// connect highlighting/unhighlighting
		toAdd->connect(toAdd, static_cast<void (ItemWidget::*)(bool)>
			(&ItemWidget::highlightingChanged), toAdd2,
			&ItemWidget::setHighlighting);
		toAdd2->connect(toAdd2, static_cast<void (ItemWidget::*)(bool)>
			(&ItemWidget::highlightingChanged), toAdd,
			&ItemWidget::setHighlighting);
	}
}