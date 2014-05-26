// header file
#include "ItemCollectionWidget.h"

using namespace UI;

ItemCollectionWidget::ItemCollectionWidget(QWidget* parent, bool direction,
											bool multiselection)
	:	TransparentScrollArea(parent),
		myDirection(direction),
		myMultiselection(multiselection),
		myContainerWidget(new QWidget(nullptr)),
		myItemAlignment(ItemCollectionWidget::StartAlign)
{
	myContainerWidget->setContentsMargins(0, 0, 0, 0);
	setWidget(myContainerWidget);
	setWidgetResizable(true);
	if (myDirection)
	{
		mySpacingLayout = new QHBoxLayout(myContainerWidget);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
	else
	{
		mySpacingLayout = new QVBoxLayout(myContainerWidget);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
	mySpacingLayout->setContentsMargins(0, 0, 0, 0);
	mySpacingLayout->addItem(new QSpacerItem(16777215, 16777215, QSizePolicy::Ignored,
														QSizePolicy::Ignored));
	mySpacingLayout->addItem(new QSpacerItem(16777215, 16777215, QSizePolicy::Ignored,
														QSizePolicy::Ignored));
	if (expandsLeftToRight())
	{
		myContainerWidget->setMinimumHeight(height());
		myContainerWidget->setMaximumHeight(height());
	}
	else
	{
		myContainerWidget->setMinimumWidth(width());
		myContainerWidget->setMaximumWidth(width());
	}
}

ItemCollectionWidget::~ItemCollectionWidget()
{
	delete mySpacingLayout;
	delete myContainerWidget;
}

bool ItemCollectionWidget::expandsLeftToRight() const
{
	return myDirection;
}

void ItemCollectionWidget::setItemAlignment(
	ItemCollectionWidget::ItemAlignment alignment)
{
	myItemAlignment = alignment;
	// add the ending spacer if necessary
	if (alignment & StartAlign)
	{
		mySpacingLayout->itemAt(2)->spacerItem()
						->changeSize(16777215, 16777215, QSizePolicy::Ignored,
												QSizePolicy::Ignored);
		mySpacingLayout->setStretch(2, 1);
	}
	// remove the ending spacer if necessary
	else
	{
		mySpacingLayout->itemAt(2)->spacerItem()
						->changeSize(0, 0, QSizePolicy::Fixed,
												QSizePolicy::Fixed);
		mySpacingLayout->setStretch(2, 0);
	}
	// add the starting spacer if necessary
	if (alignment & EndAlign)
	{
		mySpacingLayout->itemAt(0)->spacerItem()
						->changeSize(16777215, 16777215, QSizePolicy::Ignored,
												QSizePolicy::Ignored);
		mySpacingLayout->setStretch(0, 1);
	}
	// remove the starting spacer if necessary
	else
	{
		mySpacingLayout->itemAt(0)->spacerItem()
						->changeSize(0, 0, QSizePolicy::Fixed,
												QSizePolicy::Fixed);
		mySpacingLayout->setStretch(0, 0);
	}
}

ItemCollectionWidget::ItemAlignment
	ItemCollectionWidget::getItemAlignment() const
{
	return myItemAlignment;
}

bool ItemCollectionWidget::acceptsMultiselection() const
{
	return myMultiselection;
}

int ItemCollectionWidget::count() const
{
	return myItemLayout->count();
}

void ItemCollectionWidget::resizeEvent(QResizeEvent*)
{
	if (expandsLeftToRight())
	{
		myContainerWidget->setMinimumHeight(height());
		myContainerWidget->setMaximumHeight(height());
	}
	else
	{
		myContainerWidget->setMinimumWidth(width());
		myContainerWidget->setMaximumWidth(width());
	}
}

void ItemCollectionWidget::registerItem(ItemWidget* item)
{
	// set the parent widget
	item->setParent(myContainerWidget);
	// make a bunch of connections
	connect(item, SIGNAL(highlighted(ItemWidget*)),
			this, SLOT(respondToItemHighlighted(ItemWidget*)));
	connect(item, SIGNAL(unhighlighted(ItemWidget*)),
			this, SLOT(respondToItemUnhighlighted(ItemWidget*)));
	connect(item, SIGNAL(highlightingChanged(bool, ItemWidget*)),
			this, SLOT(respondToItemHighlightingChanged(bool, ItemWidget*)));
	connect(item, SIGNAL(selected(ItemWidget*)),
			this, SLOT(respondToItemSelected(ItemWidget*)));
}

void ItemCollectionWidget::unregisterItem(ItemWidget* item)
{
	// disconnect everything
	disconnect(item, 0, this, 0);
}

void ItemCollectionWidget::setContainerLayout(QLayout* layout)
{
	myItemLayout = layout;
	mySpacingLayout->insertLayout(1, layout);
	layout->setContentsMargins(0, 0, 0, 0);
	setItemAlignment(getItemAlignment());
}

void ItemCollectionWidget::respondToItemHighlighted(ItemWidget* item)
{
	if (!myMultiselection)
	{
		for (int i = 0; i < myItemLayout->count(); ++ i)
		{
			if (myItemLayout->itemAt(i)->widget())
			{
				ItemWidget* temp = (ItemWidget*) myItemLayout->itemAt(i)->widget();
				if (temp != item && temp->isHighlighted())
				{
					temp->unhighlight();
					break;
				}
			}
		}
	}
	emit itemHighlighted(item);
}

void ItemCollectionWidget::respondToItemUnhighlighted(ItemWidget* item)
{
	emit itemUnhighlighted(item);
}

void ItemCollectionWidget::respondToItemHighlightingChanged(bool newState,
															ItemWidget* item)
{
	emit itemHighlightingChanged(newState, item);
}

void ItemCollectionWidget::respondToItemSelected(ItemWidget* item)
{
	emit itemSelected(item);
}