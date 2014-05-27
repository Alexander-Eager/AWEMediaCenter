// header file
#include "ItemCollectionWidget.h"

// for holding items
#include <QLayout>
#include <QBoxLayout>

namespace UI
{
	class ItemCollectionWidgetPrivate
	{
		public:
			// parent
			ItemCollectionWidget* p;

			// Does this expand left-to-right?
			bool direction;

			// Does this allow multiselection?
			bool multiselection;

			// The widget held inside of the scroll area.
			QWidget* containerWidget;

			// The item alignment.
			ItemCollectionWidget::ItemAlignment itemAlignment;

			// A box layout to adjust spacing.
			QBoxLayout* spacingLayout;

			// The layout holding all of the items.
			QLayout* itemLayout;

			// ensures that only one item is highlighted if multiselection
			// is disabled
			inline void respondToItemHighlighted(ItemWidget* item);
	};
}

using namespace UI;

ItemCollectionWidget::ItemCollectionWidget(QWidget* parent, bool direction,
											bool multiselection)
	:	TransparentScrollArea(parent),
		d(new ItemCollectionWidgetPrivate)
{
	d->p = this;
	// make everything
	d->direction = direction;
	d->multiselection = multiselection;
	d->containerWidget = new QWidget(nullptr);
	d->itemAlignment = ItemCollectionWidget::StartAlign;

	// set up the widgets and layouts
	d->containerWidget->setContentsMargins(0, 0, 0, 0);
	setWidget(d->containerWidget);
	setWidgetResizable(true);
	if (d->direction)
	{
		d->spacingLayout = new QHBoxLayout(d->containerWidget);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
	else
	{
		d->spacingLayout = new QVBoxLayout(d->containerWidget);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
	d->spacingLayout->setContentsMargins(0, 0, 0, 0);
	d->spacingLayout->addItem(new QSpacerItem(16777215, 16777215, QSizePolicy::Ignored,
														QSizePolicy::Ignored));
	d->spacingLayout->addItem(new QSpacerItem(16777215, 16777215, QSizePolicy::Ignored,
														QSizePolicy::Ignored));
	if (expandsLeftToRight())
	{
		d->containerWidget->setMinimumHeight(height());
		d->containerWidget->setMaximumHeight(height());
	}
	else
	{
		d->containerWidget->setMinimumWidth(width());
		d->containerWidget->setMaximumWidth(width());
	}
}

ItemCollectionWidget::~ItemCollectionWidget()
{
	delete d->spacingLayout;
	delete d->containerWidget;
}

bool ItemCollectionWidget::expandsLeftToRight() const
{
	return d->direction;
}

void ItemCollectionWidget::setItemAlignment(
	ItemCollectionWidget::ItemAlignment alignment)
{
	d->itemAlignment = alignment;
	// add the ending spacer if necessary
	if (alignment & StartAlign)
	{
		d->spacingLayout->itemAt(2)->spacerItem()
						->changeSize(16777215, 16777215, QSizePolicy::Ignored,
												QSizePolicy::Ignored);
		d->spacingLayout->setStretch(2, 1);
	}
	// remove the ending spacer if necessary
	else
	{
		d->spacingLayout->itemAt(2)->spacerItem()
						->changeSize(0, 0, QSizePolicy::Fixed,
												QSizePolicy::Fixed);
		d->spacingLayout->setStretch(2, 0);
	}
	// add the starting spacer if necessary
	if (alignment & EndAlign)
	{
		d->spacingLayout->itemAt(0)->spacerItem()
						->changeSize(16777215, 16777215, QSizePolicy::Ignored,
												QSizePolicy::Ignored);
		d->spacingLayout->setStretch(0, 1);
	}
	// remove the starting spacer if necessary
	else
	{
		d->spacingLayout->itemAt(0)->spacerItem()
						->changeSize(0, 0, QSizePolicy::Fixed,
												QSizePolicy::Fixed);
		d->spacingLayout->setStretch(0, 0);
	}
}

ItemCollectionWidget::ItemAlignment
	ItemCollectionWidget::getItemAlignment() const
{
	return d->itemAlignment;
}

bool ItemCollectionWidget::acceptsMultiselection() const
{
	return d->multiselection;
}

int ItemCollectionWidget::count() const
{
	return d->itemLayout->count();
}

void ItemCollectionWidget::resizeEvent(QResizeEvent*)
{
	if (expandsLeftToRight())
	{
		d->containerWidget->setMinimumHeight(height());
		d->containerWidget->setMaximumHeight(height());
	}
	else
	{
		d->containerWidget->setMinimumWidth(width());
		d->containerWidget->setMaximumWidth(width());
	}
}

void ItemCollectionWidget::registerItem(ItemWidget* item)
{
	// set the parent widget
	item->setParent(d->containerWidget);
	// make a bunch of connections
	connect(item, static_cast<void (ItemWidget::*)(ItemWidget*)>
			(&ItemWidget::highlighted), this,
			[this] (ItemWidget* item)
			{
				d->respondToItemHighlighted(item);
				emit itemHighlighted(item);
			} );

	connect(item, static_cast<void (ItemWidget::*)(ItemWidget*)>
			(&ItemWidget::unhighlighted), this,
			[this] (ItemWidget* item)
			{
				emit itemUnhighlighted(item);
			} );

	connect(item, static_cast<void (ItemWidget::*)(bool, ItemWidget*)>
			(&ItemWidget::highlightingChanged), this,
			[this] (bool newState, ItemWidget* item)
			{
				emit itemHighlightingChanged(newState, item);
			} );

	connect(item, static_cast<void (ItemWidget::*)(ItemWidget*)>
			(&ItemWidget::selected), this,
			[this] (ItemWidget* item)
			{
				emit itemSelected(item);
			} );
}

void ItemCollectionWidget::unregisterItem(ItemWidget* item)
{
	// disconnect everything
	disconnect(item, 0, this, 0);
}

void ItemCollectionWidget::setContainerLayout(QLayout* layout)
{
	d->itemLayout = layout;
	d->spacingLayout->insertLayout(1, layout);
	layout->setContentsMargins(0, 0, 0, 0);
	setItemAlignment(getItemAlignment());
}

void ItemCollectionWidgetPrivate::respondToItemHighlighted(ItemWidget* item)
{
	if (!multiselection)
	{
		for (int i = 0; i < itemLayout->count(); ++ i)
		{
			if (itemLayout->itemAt(i)->widget())
			{
				ItemWidget* temp = qobject_cast<ItemWidget*>(itemLayout
					->itemAt(i)->widget());
				if (temp && temp != item && temp->isHighlighted())
				{
					temp->unhighlight();
					break;
				}
			}
		}
	}
	p->ensureWidgetVisible(item, 0, 0);
}