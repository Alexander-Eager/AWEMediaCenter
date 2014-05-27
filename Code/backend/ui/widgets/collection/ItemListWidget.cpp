// header file
#include "ItemListWidget.h"

// layout to use
#include <QBoxLayout>

// the two kinds of box layout
#include <QVBoxLayout>
#include <QHBoxLayout>

// for retrieving items
#include <QLayoutItem>

namespace UI
{
	class ItemListWidgetPrivate
	{
		public:
			QBoxLayout* layout;
	};
}

using namespace UI;

ItemListWidget::ItemListWidget(QWidget* parent, bool direction,
								bool multiselection)
	:	ItemCollectionWidget(parent, direction, multiselection),
		d(new ItemListWidgetPrivate)
{
	if (expandsLeftToRight())
	{
		d->layout = new QHBoxLayout;
	}
	else
	{
		d->layout = new QVBoxLayout;
	}
	setContainerLayout(d->layout);
}

ItemListWidget::~ItemListWidget()
{
	clear();
	delete d->layout;
}

QString ItemListWidget::getLayoutType() const
{
	return "Item List";
}

ItemWidget* ItemListWidget::at(int index)
{
	if (index >= count() || index < 0)
	{
		return nullptr;
	}
	return (ItemWidget*) d->layout->itemAt(index)->widget();
}

const ItemWidget* ItemListWidget::at(int index) const
{
	if (index >= count() || index < 0)
	{
		return nullptr;
	}
	return (ItemWidget*) d->layout->itemAt(index)->widget();
}

void ItemListWidget::addItem(ItemWidget* item)
{
	registerItem(item);
	d->layout->insertWidget(count(), item);
	if (expandsLeftToRight())
	{
		item->fixSizeToFitIn(QSize(16777215, height()));
	}
	else
	{
		item->fixSizeToFitIn(QSize(width(), 16777215));
	}
}

void ItemListWidget::insertItem(int index, ItemWidget* item)
{
	registerItem(item);
	d->layout->insertWidget(index, item);
}

void ItemListWidget::removeItem(ItemWidget* item)
{
	d->layout->removeWidget(item);
	item->deleteLater();
}

void ItemListWidget::removeItem(int index)
{
	if (index >= count() || index < 0)
	{
		return;
	}
	ItemWidget* item = at(index);
	d->layout->removeWidget(item);
	item->deleteLater();
}

void ItemListWidget::clear()
{
	while (count() > 0)
	{
		removeItem(0);
	}
}

void ItemListWidget::resizeEvent(QResizeEvent* event)
{
	ItemCollectionWidget::resizeEvent(event);
	for (int i = 0; i < count(); ++ i)
	{
		if (expandsLeftToRight())
		{
			at(i)->fixSizeToFitIn(QSize(16777215, height()));
			at(i)->setMaximumHeight(height());
			at(i)->setMinimumHeight(height());
		}
		else
		{
			at(i)->fixSizeToFitIn(QSize(width(), 16777215));
			at(i)->setMaximumWidth(width());
			at(i)->setMinimumWidth(width());
		}
	}
}