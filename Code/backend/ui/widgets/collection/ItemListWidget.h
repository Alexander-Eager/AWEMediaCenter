#ifndef ITEM_LIST_WIDGET_H
#define ITEM_LIST_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "ItemCollectionWidget.h"

// layout to use
#include <QBoxLayout>

namespace UI
{
	/**
	 * \brief An item collection based off of
	 *			lists.
	 **/
	class AWEMC_BACKEND_LIBRARY ItemListWidget : public ItemCollectionWidget
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
			 **/
			ItemListWidget(QWidget* parent, bool direction = false,
							bool multiselection = false);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ItemListWidget();

			/**
			 * \brief Get the way these collections are
			 *			stored, "Item List".
			 *
			 * \returns "Item List".
			 **/
			virtual QString getLayoutType() const;

			/**
			 * \brief Get the item at the given index.
			 *
			 * \param index The index of the item to get.
			 *
			 * \returns The item at the given index.
			 **/
			virtual ItemWidget* at(int index);

			/**
			 * \brief Get the item at the given index.
			 *
			 * \param index The index of the item to get.
			 *
			 * \returns The item at the given index.
			 **/
			virtual const ItemWidget* at(int index) const;

		public slots:
			/**
			 * \brief Add an item to this list.
			 *
			 * \param[in] item The item to add.
			 **/
			virtual void addItem(ItemWidget* item);

			/**
			 * \brief Insert an item into this list.
			 *
			 * \param[in] index The index to place the
			 *					item at.
			 * \param[in] item The item to add.
			 **/
			virtual void insertItem(int index, ItemWidget* item);

			/**
			 * \brief Remove an item from this list.
			 *
			 * \param[in] item The item to remove (and delete).
			 **/
			virtual void removeItem(ItemWidget* item);

			/**
			 * \brief Remove the item at `index` this list.
			 *
			 * \param[in] index The index of the item to
			 *					remove (and delete).
			 **/
			virtual void removeItem(int index);

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
			 * \brief Changes the mandatory size for the
			 *			items.
			 *
			 * \param event The (ignored) size event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);

		private:
			/** \brief Layout that holds all of the items. **/
			QBoxLayout* myLayout;
	};
}

#endif