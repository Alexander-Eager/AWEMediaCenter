#ifndef ITEM_GRID_WIDGET_H
#define ITEM_GRID_WIDGET_H

// superclass
#include "ItemCollectionWidget.h"

// layout stuff
#include <QGridLayout>
#include <QPoint>

namespace UI
{
	/**
	 * \brief An item collection based on a grid layout.
	 **/
	class ItemGridWidget : public ItemCollectionWidget
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make for the given parent
			 *			in the given direction.
			 *
			 * \param[in] parent The parent widget.
			 * \param[in] direction The direction of expansion;
			 *					`true` if left-right,
			 *					`false` if up-down.
			 * \param[in] multiselection `true` if multiple items
			 *								should be selectable
			 *								at once, `false` if
			 *								only one should be
			 *								at a time.
			 * \param[in] num This is the number of not expandable
			 *					columns/rows.
			 **/
			ItemGridWidget(QWidget* parent, bool direction,
							bool multiselection, int num);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ItemGridWidget();

			/**
			 * \brief Get the way these collections are
			 *			stored, "Item Grid".
			 *
			 * \returns "Item Grid".
			 **/
			virtual QString getLayoutType() const;

			/**
			 * \brief Get the number of items in this grid.
			 *
			 * \returns The number of items in this grid.
			 **/
			virtual int count() const;

		public slots:
			/**
			 * \brief Add an item to this list.
			 *
			 * \param[in] item The item to add.
			 **/
			virtual void addItem(ItemWidget* item);

			/**
			 * \brief Remove an item from this list.
			 *
			 * \param[in] item The item to remove (and delete).
			 **/
			virtual void removeItem(ItemWidget* item);

			/**
			 * \brief Remove all items in a safe way.
			 *
			 * Unlike `QListWidget`'s clear function,
			 * this one uses `deleteLater()` to avoid
			 * segmentation faults if this function
			 * is called as a result of an item activation.
			 **/
			virtual void clear();

		protected:
			/**
			 * \brief Changes the item's fixed size
			 *			to fit this grid.
			 *
			 * \param event The (unused) resize event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);

		private:
			/** \brief Increment the position. **/
			void incrementPos(QPoint& pos);

			/** \brief Decrement pos. **/
			void decrementPos(QPoint& pos);

			/** \brief Replace the item at pos. **/
			void replaceItem(QWidget* item, QPoint pos);

			/** \brief The grid layout. **/
			QGridLayout* myLayout;

			/** \brief The number of rows or columns (depending on the direction). **/
			int myNum;
			
			/** \brief The current position. **/
			QPoint myPos;
	};
}

#endif