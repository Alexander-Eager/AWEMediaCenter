// header file
#include "FolderPane.h"

// debug
#include "debug_macros/debug.h"

using namespace UI;
using namespace AWE;

FolderPane::FolderPane(QWidget* parent)
	:	Pane(parent),
		myFolder(nullptr),
		myMainLayout(new QVBoxLayout(this)),
		myBackButton(new QPushButton(tr("Back"), this)),
		myViewSelectionMenu(new QComboBox(this)),
		myMediaItemLayout(new QStackedLayout),
		myMediaItemList(new ItemListWidget(this, false, false)),
		myMediaItemGrid(new ItemGridWidget(this, false, false, 3))
{
	/* set up layouts/widgets */
	myMainLayout->addWidget(myBackButton);
	myViewSelectionMenu->addItem("Grid");
	myViewSelectionMenu->addItem("List");
	myViewSelectionMenu->setCurrentIndex(0);
	myMainLayout->addWidget(myViewSelectionMenu);
	myMainLayout->addLayout(myMediaItemLayout);
	myMediaItemLayout->setContentsMargins(0, 0, 0, 0);
	myMediaItemLayout->addWidget(myMediaItemGrid);
	myMediaItemLayout->addWidget(myMediaItemList);

	/* connections */
	// item highlight and selection
	connect(myMediaItemList, &ItemListWidget::itemHighlighted,
			this, &FolderPane::respondToItemHighlight);
	connect(myMediaItemList, &ItemListWidget::itemSelected,
			this, &FolderPane::respondToItemSelected);
	connect(myMediaItemGrid, &ItemGridWidget::itemHighlighted,
			this, &FolderPane::respondToItemHighlight);
	connect(myMediaItemGrid, &ItemGridWidget::itemSelected,
			this, &FolderPane::respondToItemSelected);
	// switching view layout
	connect(myViewSelectionMenu, SIGNAL(currentIndexChanged(int)),
			this, SLOT(respondToViewModeChoice(int)));
	// back button
	connect(myBackButton, &QPushButton::clicked,
			this, &FolderPane::respondToBackButton);
}

FolderPane::~FolderPane()
{
	delete myMediaItemGrid;
	delete myMediaItemList;
	delete myMediaItemLayout;
	delete myViewSelectionMenu;
	delete myBackButton;
	delete myMainLayout;
}

void FolderPane::setFolder(Folder* folder)
{
	// quick speed check
	if (myFolder == folder)
	{
		return;
	}
	// set the folder variable
	myFolder = folder;
	// refresh the item lists
	refresh();
}

void FolderPane::refresh()
{
	/* change the contents of the item list */
	myMediaItemList->clear();
	myMediaItemGrid->clear();
	for (int i = 0; i < myFolder->getItems().count(); ++ i)
	{
		MediaItemWidget* toAdd = new MediaItemWidget(myMediaItemList,
									myFolder->getItems().takeAt(i), true);
		toAdd->setDisplayMode(MediaItemWidget::NameOnly);
		myMediaItemList->addItem(toAdd);
		toAdd = new MediaItemWidget(myMediaItemGrid,
									myFolder->getItems().takeAt(i), true);
		toAdd->setDisplayMode(MediaItemWidget::IconOnly);
		myMediaItemGrid->addItem(toAdd);
	}
}

void FolderPane::respondToItemHighlight(ItemWidget* curr)
{
	emit itemHighlighted(((MediaItemWidget*) curr)->getMediaItem());
}

void FolderPane::respondToItemSelected(ItemWidget* item)
{
	emit itemSelected(((MediaItemWidget*) item)->getMediaItem());
}

void FolderPane::respondToViewModeChoice(int mode)
{
	myMediaItemLayout->setCurrentIndex(mode);
}

void FolderPane::respondToBackButton()
{
	emit goUpOne();
}