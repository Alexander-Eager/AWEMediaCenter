#ifndef ITEM_COLLECTION_WIDGET_H
#define ITEM_COLLECTION_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "ui/widgets/TransparentScrollArea.h"

// Q_OBJECT
#include <QObject>

// items to be held
#include "ui/widgets/items/ItemWidget.h"

namespace UI
{
	// internal data class
	class ItemCollectionWidgetPrivate;

	/**
	 * \brief An abstract, scrollable collection
	 * 			of item widgets.
	 *
	 * Provides convenience functions for
	 * displaying a collection of `ItemWidget`s
	 * and receiving information on their state.
	 *
	 * When using this class (or a sub-class),
	 * you should never need to call any of
	 * `QScrollArea`'s functions.
	 **/
	class AWEMC_BACKEND_LIBRARY ItemCollectionWidget : public TransparentScrollArea
	{
		Q_OBJECT

		public:
			enum ItemAlignment
			{
				StartAlign = 1,
				EndAlign = 2,
				MiddleAlign = 3
			};

			/**
			 * \brief Make for the given parent
			 *			in the given direction.
			 *
			 * \param[in] parent The parent widget.
			 * \param[in] direction The direction of expansion;
			 *						`true` if left-right,
			 *						`false` if up-down.
			 * \param[in] multiselection `true` if multiple items
			 *								should be selectable
			 *								at once, `false` if
			 *								only one should be
			 *								at a time.
			 **/
			ItemCollectionWidget(QWidget* parent, bool direction,
				bool multiselection);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ItemCollectionWidget();

			/**
			 * \brief Get the way these collections are
			 *			stored.
			 *
			 * \returns The type of layout used as a string.
			 **/
			virtual QString getLayoutType() const = 0;

			/**
			 * \brief Get the direction of expansion,
			 *			left-right or up-down.
			 *
			 * \returns `true` if this collection expands
			 *			from left to right, `false` if it
			 *			expands from top to bottom.
			 **/
			virtual bool expandsLeftToRight() const;

			/**
			 * \brief Change how the items are presented.
			 *
			 * If `StartAlign`, the items will be aligned
			 * to the left (if `expandsLeftToRight()`) or
			 * top. If `MiddleAlign`, the items will be
			 * aligned horizontally in the middle or vertically.
			 * If `EndAlign`, the items will be aligned to
			 * the right or the bottom.
			 *
			 * \param alignment The alignment to use.
			 **/
			virtual void setItemAlignment(ItemAlignment alignment);

			/**
			 * \brief Get the item alignment.
			 *
			 * By default, this value is `StartAlign`.
			 *
			 * \returns The item alignment.
			 **/
			virtual ItemAlignment getItemAlignment() const;

			/**
			 * \brief Does this widget accept multiselection?
			 *
			 * \returns `true` if this widget accepts multiselection,
			 *			`false` otherwise.
			 **/
			virtual bool acceptsMultiselection() const;

			/**
			 * \brief Get the number of items in this collection.
			 *
			 * \returns The number of items in this colleciton.
			 **/
			virtual int count() const;

		public slots:
			/**
			 * \brief Add an item to this collection.
			 *
			 * The exact location of this addition
			 * is specific to the layout type.
			 *
			 * When writing this method in a sub-class,
			 * you must first call
			 * `registerItem(item)`
			 * so that the item can be registered for
			 * signals.
			 *
			 * \param[in] item The item to add.
			 **/
			virtual void addItem(ItemWidget* item) = 0;

			/**
			 * \brief Remove an item from this collection.
			 *
			 * \param[in] item The item to remove (and delete).
			 **/
			virtual void removeItem(ItemWidget* item) = 0;

			/**
			 * \brief Remove all items in a safe way.
			 *
			 * Unlike `QListWidget`'s clear function,
			 * this one uses `deleteLater()` to avoid
			 * segmentation faults if this function
			 * is called as a result of an item activation.
			 **/
			virtual void clear() = 0;

		signals:
			/**
			 * \brief Sent when an item has been highlighted.
			 *
			 * \param[in] item The highlighted item.
			 **/
			void itemHighlighted(ItemWidget* item);

			/**
			 * \brief Sent when an item has been unhighlighted.
			 *
			 * \param[in] item The unhighlighted item.
			 **/
			void itemUnhighlighted(ItemWidget* item);

			/**
			 * \brief Sent when an item's highlighting state
			 *			has changed.
			 *
			 * \param[in] newState `true` if the item is now
			 *						highlighted, `false` if
			 *						unhighlighted.
			 * \param[in] item The altered item.
			 **/
			void itemHighlightingChanged(bool newState, ItemWidget* item);

			/**
			 * \brief Sent when an item has been selected.
			 *
			 * \param[in] item The selected item.
			 **/
			void itemSelected(ItemWidget* item);

		protected:
			/**
			 * \brief Responds to resize events.
			 *
			 * \param event The (unused) resize event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);
			
			/**
			 * \brief Registers the item for signal monitoring.
			 *
			 * \param[in] item The item to register.
			 **/
			virtual void registerItem(ItemWidget* item);

			/**
			 * \brief Removes the registration for the given item.
			 *
			 * \param[in] item The item to unregister.
			 **/
			virtual void unregisterItem(ItemWidget* item);

			/**
			 * \brief Set the layout that will hold all of the items.
			 *
			 * \param[in] layout The layout that should hold everything.
			 **/
			virtual void setContainerLayout(QLayout* layout);

		private:
			ItemCollectionWidgetPrivate* d;
	};
}

#endif