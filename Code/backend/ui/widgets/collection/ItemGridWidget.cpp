// header file
#include "ItemGridWidget.h"

// layout stuff
#include <QGridLayout>
#include <QPoint>

namespace UI
{
	class ItemGridWidgetPrivate
	{
		public:
			ItemGridWidget* p;

			// Increment the position.
			void incrementPos(QPoint& pos);

			// Decrement pos.
			void decrementPos(QPoint& pos);

			// Replace the item at pos.
			void replaceItem(QWidget* item, QPoint pos);

			// The grid layout.
			QGridLayout* layout;

			// The number of rows or columns (depending on the direction).
			int num;
			
			// The current position.
			QPoint currPos;
	};
}

using namespace UI;

ItemGridWidget::ItemGridWidget(QWidget* parent, bool direction,
								bool multiselection, int num)
	:	ItemCollectionWidget(parent, direction, multiselection),
		d(new ItemGridWidgetPrivate)
{
	// make everything
	d->p = this;
	d->layout = new QGridLayout;
	d->num = num;
	d->currPos = QPoint(0, 0);

	// set up column/row spacing and stretching
	d->layout->setVerticalSpacing(5);
	d->layout->setHorizontalSpacing(5);
	// adjust row/col stretches to make it an even grid
	if (expandsLeftToRight())
	{
		for (int i = 0; i < d->num; ++ i)
		{
			d->layout->setRowStretch(i, 1);
		}
	}
	else
	{
		for (int i = 0; i < d->num; ++ i)
		{
			d->layout->setColumnStretch(i, 1);
		}
	}
	setContainerLayout(d->layout);
}

ItemGridWidget::~ItemGridWidget()
{
	clear();
	delete d->layout;
}

QString ItemGridWidget::getLayoutType() const
{
	return "Item Grid";
}

int ItemGridWidget::count() const
{
	if (!expandsLeftToRight())
	{
		return d->num * d->currPos.x() + d->currPos.y();
	}
	else
	{
		return d->num * d->currPos.y() + d->currPos.x();
	}
}

void ItemGridWidget::addItem(ItemWidget* item)
{
	// tell the item its size (and change stretch factors)
	// add the item
	registerItem(item);
	d->replaceItem(item, d->currPos);
	if (!expandsLeftToRight())
	{
		int w = (width() - d->layout->horizontalSpacing() * (d->num - 1))
					/ d->num;
		item->fixSizeToFitIn(QSize(QSize(w, 16777215)));
		d->layout->setRowStretch(d->currPos.y(), 1);
	}
	else
	{
		int h = (height() - d->layout->verticalSpacing() * (d->num - 1))
					/ d->num;
		item->fixSizeToFitIn(QSize(16777215, h));
		d->layout->setColumnStretch(d->currPos.x(), 1);
	}
	// increment
	d->incrementPos(d->currPos);
}

void ItemGridWidget::removeItem(ItemWidget* item)
{
	if (!item)
	{
		return;
	}
	// get the location
	QPoint pos(0, 0);
	while (pos != d->currPos 
			&& d->layout->itemAtPosition(pos.x(), pos.y())->widget() != item)
	{
		d->incrementPos(pos);
	}
	if (pos == d->currPos)
	{
		return;
	}
	// remove item
	d->layout->removeWidget(item);
	item->deleteLater();
	d->decrementPos(d->currPos);
	// shift everything down one
	while (pos != d->currPos)
	{
		// move the next item here
		d->incrementPos(pos);
		QPoint next = pos;
		d->decrementPos(pos);
		d->replaceItem(d->layout->itemAtPosition(next.x(), next.y())->widget(), pos);
		// increment
		pos = next;
	}
	// get rid of the last item
	QLayoutItem* temp = d->layout->itemAtPosition(d->currPos.x(), d->currPos.y());
	d->layout->removeItem(temp);
	delete temp;
}

void ItemGridWidget::clear()
{
	QPoint origin(0, 0);
	while (d->currPos != origin)
	{
		d->decrementPos(d->currPos);
		d->replaceItem(nullptr, d->currPos);
	}
}

void ItemGridWidget::resizeEvent(QResizeEvent* event)
{
	ItemCollectionWidget::resizeEvent(event);
	for (int i = 0; i < d->layout->count(); ++ i)
	{
		if (d->layout->itemAt(i)->widget())
		{
			ItemWidget* item = (ItemWidget*) d->layout->itemAt(i)->widget();
			if (!expandsLeftToRight())
			{
				int w = (width() - d->layout->horizontalSpacing() * (d->num - 1))
							/ d->num;
				item->fixSizeToFitIn(QSize(QSize(w, 16777215)));
			}
			else
			{
				int h = (height() - d->layout->verticalSpacing() * (d->num - 1))
							/ d->num;
				item->fixSizeToFitIn(QSize(16777215, h));
			}
		}
	}

}

void ItemGridWidgetPrivate::incrementPos(QPoint& pos)
{
	if (!p->expandsLeftToRight())
	{
		pos.setY(pos.y() + 1);
		if (pos.y() == num)
		{
			pos.setX(pos.x() + 1);
			pos.setY(0);
		}
	}
	else
	{
		pos.setX(pos.x() + 1);
		if (pos.x() == num)
		{
			pos.setY(pos.y() + 1);
			pos.setX(0);
		}
	}
}

void ItemGridWidgetPrivate::decrementPos(QPoint& pos)
{
	if (!p->expandsLeftToRight())
	{
		pos.setY(pos.y() - 1);
		if (pos.y() == -1)
		{
			pos.setX(pos.x() - 1);
			pos.setY(num - 1);
		}
	}
	else
	{
		pos.setX(pos.x() - 1);
		if (pos.x() == -1)
		{
			pos.setY(pos.y() - 1);
			pos.setX(num - 1);
		}
	}
}

void ItemGridWidgetPrivate::replaceItem(QWidget* item, QPoint pos)
{
	QLayoutItem* temp = layout->itemAtPosition(pos.x(), pos.y());
	if (temp && temp->widget())
	{
		QWidget* widget = temp->widget();
		layout->removeWidget(widget);
		widget->deleteLater();
	}
	if (item)
	{
		layout->addWidget(item, pos.x(), pos.y(), Qt::AlignCenter);
	}
}