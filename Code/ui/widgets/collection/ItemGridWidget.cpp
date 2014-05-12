// header file
#include "ItemGridWidget.h"

// debug
#include "debug_macros/debug.h"

using namespace UI;

ItemGridWidget::ItemGridWidget(QWidget* parent, bool direction,
								bool multiselection, int num)
	:	ItemCollectionWidget(parent, direction, multiselection),
		myLayout(new QGridLayout),
		myNum(num),
		myPos(0, 0)
{
	myLayout->setVerticalSpacing(5);
	myLayout->setHorizontalSpacing(5);
	// adjust row/col stretches to make it an even grid
	if (expandsLeftToRight())
	{
		for (int i = 0; i < myNum; ++ i)
		{
			myLayout->setRowStretch(i, 1);
		}
	}
	else
	{
		for (int i = 0; i < myNum; ++ i)
		{
			myLayout->setColumnStretch(i, 1);
		}
	}
	setContainerLayout(myLayout);
}

ItemGridWidget::~ItemGridWidget()
{
	clear();
	delete myLayout;
}

QString ItemGridWidget::getLayoutType() const
{
	return "Item Grid";
}

int ItemGridWidget::count() const
{
	if (!expandsLeftToRight())
	{
		return myNum * myPos.x() + myPos.y();
	}
	else
	{
		return myNum * myPos.y() + myPos.x();
	}
}

void ItemGridWidget::addItem(ItemWidget* item)
{
	// tell the item its size (and change stretch factors)
	// add the item
	registerItem(item);
	replaceItem(item, myPos);
	if (!expandsLeftToRight())
	{
		int w = (width() - myLayout->horizontalSpacing() * (myNum - 1))
					/ myNum;
		item->fixSizeToFitIn(QSize(QSize(w, 16777215)));
		myLayout->setRowStretch(myPos.y(), 1);
	}
	else
	{
		int h = (height() - myLayout->verticalSpacing() * (myNum - 1))
					/ myNum;
		item->fixSizeToFitIn(QSize(16777215, h));
		myLayout->setColumnStretch(myPos.x(), 1);
	}
	// increment
	incrementPos(myPos);
}

void ItemGridWidget::removeItem(ItemWidget* item)
{
	if (!item)
	{
		return;
	}
	// get the location
	QPoint pos(0, 0);
	while (pos != myPos 
			&& myLayout->itemAtPosition(pos.x(), pos.y())->widget() != item)
	{
		incrementPos(pos);
	}
	if (pos == myPos)
	{
		return;
	}
	// remove item
	myLayout->removeWidget(item);
	item->deleteLater();
	decrementPos(myPos);
	// shift everything down one
	while (pos != myPos)
	{
		// move the next item here
		incrementPos(pos);
		QPoint next = pos;
		decrementPos(pos);
		replaceItem(myLayout->itemAtPosition(next.x(), next.y())->widget(), pos);
		// increment
		pos = next;
	}
	// get rid of the last item
	QLayoutItem* temp = myLayout->itemAtPosition(myPos.x(), myPos.y());
	myLayout->removeItem(temp);
	delete temp;
}

void ItemGridWidget::clear()
{
	QPoint origin(0, 0);
	while (myPos != origin)
	{
		decrementPos(myPos);
		replaceItem(nullptr, myPos);
	}
}

void ItemGridWidget::resizeEvent(QResizeEvent* event)
{
	ItemCollectionWidget::resizeEvent(event);
	for (int i = 0; i < myLayout->count(); ++ i)
	{
		if (myLayout->itemAt(i)->widget())
		{
			ItemWidget* item = (ItemWidget*) myLayout->itemAt(i)->widget();
			if (!expandsLeftToRight())
			{
				int w = (width() - myLayout->horizontalSpacing() * (myNum - 1))
							/ myNum;
				item->fixSizeToFitIn(QSize(QSize(w, 16777215)));
			}
			else
			{
				int h = (height() - myLayout->verticalSpacing() * (myNum - 1))
							/ myNum;
				item->fixSizeToFitIn(QSize(16777215, h));
			}
		}
	}

}

void ItemGridWidget::incrementPos(QPoint& pos)
{
	if (!expandsLeftToRight())
	{
		pos.setY(pos.y() + 1);
		if (pos.y() == myNum)
		{
			pos.setX(pos.x() + 1);
			pos.setY(0);
		}
	}
	else
	{
		pos.setX(pos.x() + 1);
		if (pos.x() == myNum)
		{
			pos.setY(pos.y() + 1);
			pos.setX(0);
		}
	}
}

void ItemGridWidget::decrementPos(QPoint& pos)
{
	if (!expandsLeftToRight())
	{
		pos.setY(pos.y() - 1);
		if (pos.y() == -1)
		{
			pos.setX(pos.x() - 1);
			pos.setY(myNum - 1);
		}
	}
	else
	{
		pos.setX(pos.x() - 1);
		if (pos.x() == -1)
		{
			pos.setY(pos.y() - 1);
			pos.setX(myNum - 1);
		}
	}
}

void ItemGridWidget::replaceItem(QWidget* item, QPoint pos)
{
	QLayoutItem* temp = myLayout->itemAtPosition(pos.x(), pos.y());
	if (temp && temp->widget())
	{
		QWidget* widget = temp->widget();
		myLayout->removeWidget(widget);
		widget->deleteLater();
	}
	if (item)
	{
		myLayout->addWidget(item, pos.x(), pos.y(), Qt::AlignCenter);
	}
}