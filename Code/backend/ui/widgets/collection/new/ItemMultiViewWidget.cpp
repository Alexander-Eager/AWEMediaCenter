// header file
#include "ItemMultiViewWidget.h"

// widgets and layouts
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QComboBox>

namespace UI
{
	class ItemMultiViewWidgetPrivate
	{
		public:
			ItemMultiViewWidget* p;

			QVBoxLayout* mainLayout;
			QStackedLayout* collectionLayout;
			QComboBox* selections;
	};
}

using namespace UI;

ItemMultiViewWidget::ItemMultiViewWidget(QWidget* parent,
		bool direction, bool multiselection)
	:	ItemCollectionWidget(parent, direction, multiselection),
		d(new ItemMultiViewWidgetPrivate)
{
	d->p = this;
	d->mainLayout = new QVBoxLayout(this);
	d->collectionLayout = new QStackedLayout;
	d->selections = new QComboBox(this);
	d->mainLayout->addWidget(d->selections);
	d->mainLayout->addLayout(d->collectionLayout);
}

ItemMultiViewWidget::~ItemMultiViewWidget()
{
	delete d;
}

QString ItemMultiViewWidget::getLayoutType() const
{
	return "Multiple Views";
}

int ItemMultiViewWidget::numViews() const
{
	return d->collectionLayout->count();
}

void ItemMultiViewWidget::addItem(ItemWidget* item)
{
	QList<ItemWidget*> copies;
	for (int i = 0; i < d->collectionLayout->count(); ++ i)
	{
		ItemWidget* copy = item->copy();
		copies << copy;
		((ItemCollectionWidget*) d->collectionLayout->widget(i))
			->addItem(copy);
	}
	// connect all of the copies to each other
	for (int i = 1; i < copies.count(); ++ i)
	{
		connect(copies[0], (void (ItemWidget::*)(bool)) 
							&ItemWidget::highlightingChanged,
				copies[i], &ItemWidget::setHighlighting);
	}
	// delete the original item
	item->deleteLater();
}

void ItemMultiViewWidget::removeItem(ItemWidget* item)
{
	for (int i = 0; i < d->collectionLayout->count(); ++ i)
	{
		((ItemCollectionWidget*) d->collectionLayout->(widget(i)))
			->removeItem(item);
	}
	item->deleteLater();
}

void ItemMultiViewWidget::clear()
{
	for (int i = 0; i < d->collectionLayout->count(); ++ i)
	{
		((ItemCollectionWidget*) d->collectionLayout->widget(i))
			->clear();
	}
}

bool ItemMultiViewWidget::switchToView(ItemCollectionWidget* view)
{
	for (int i = 0; i < d->collectionLayout->count(); ++ i)
	{
		ItemCollectionWidget* coll = (ItemCollectionWidget*)
			d->collectionLayout->widget(i);
		if (coll == view)
		{
			// disconnect old connections
			disconnect(d->collectionLayout->currentWidget(), 0,
						this, 0);
			// change the current view
			d->collectionLayout->setCurrentWidget(i);
			// make new connections
			connect(coll, )
		}
	}
}