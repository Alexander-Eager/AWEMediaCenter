#ifndef ITEM_MULTI_VIEW_WIDGET_H
#define ITEM_MULTI_VIEW_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QWidget>

// item container class
#include "ItemCollectionWidget.h"

namespace UI
{
	// internal data class
	class ItemMultiViewWidgetPrivate;

	/**
	 * \brief A collection of items that
	 *			can be displayed in multiple ways.
	 *
	 * This lets the user switch the way the items
	 * are displayed. A group of icons could be
	 * displayed in a list, and changed to be
	 * displayed via a grid.
	 **/
	class AWEMC_BACKEND_LIBRARY ItemMultiViewWidget : public ItemCollectionWidget
	{
		Q_OBJECT

		public:
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
			ItemMultiViewWidget(QWidget* parent, bool direction = false,
				bool multiselection = false);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~ItemMultiViewWidget();

			/**
			 * \brief Get the way these collections are
			 *			stored.
			 *
			 * \returns `"Multiple Views"`.
			 **/
			virtual QString getLayoutType() const;

			/**
			 * \brief Get the number of views.
			 *
			 * \returns The number of views.
			 **/
			virtual int numViews() const;

		public slots:
			/**
			 * \brief Add an item to this collection.
			 *
			 * \param[in] item The item to add.
			 **/
			virtual void addItem(ItemWidget* item);

			/**
			 * \brief Remove an item from this collection.
			 *
			 * \param[in] item The item to remove (and delete).
			 **/
			virtual void removeItem(ItemWidget* item);

			/**
			 * \brief Remove all items in a safe way.
			 **/
			virtual void clear();

			/**
			 * \brief Switch to the given view.
			 *
			 * \param view The view to switch to.
			 *
			 * \returns `true` if the view exists,
			 *			`false` otherwise.
			 **/
			virtual bool switchToView(ItemCollectionWidget* view);

			/**
			 * \brief Switch to the `i`th view.
			 *
			 * \param i The index of the view to switch to.
			 *
			 * \returns `true` if the index was valid,
			 *			`false` otherwise.
			 **/
			virtual bool switchToView(int i);

			/**
			 * \brief Switch to the view with the given name.
			 *
			 * \param name The name of the view to switch to.
			 *
			 * \returns `true` if the name was valid,
			 *			`false` otherwise.
			 **/
			virtual bool switchToView(QString name);

			/**
			 * \brief Add a new possible view.
			 *
			 * The view is now owned by this widget. It will
			 * be deleted when this widget is deleted.
			 *
			 * \param name The name to assign to the view in
			 *				the selection menu.
			 *
			 * \param view The view to add.
			 **/
			virtual void addView(QString name, ItemCollectionWidget* view);

			/**
			 * \brief Remove (and delete) a view.
			 *
			 * \param view The view to remove.
			 *
			 * \returns `true` if the view exists and was removed,
			 *			`false` otherwise.
			 **/
			virtual bool removeView(ItemCollectionWidget* view);

			/**
			 * \brief Remove (and delete) the `i`th view.
			 *
			 * \param i The index of the view to remove.
			 *
			 * \returns `true` if the index was valid,
			 *			`false` otherwise.
			 **/
			virtual bool removeView(int i);

			/**
			 * \brief Remove (and delete) the view with the given name.
			 *
			 * \param name The name of the view to remove.
			 *
			 * \returns `true` if the name was valid,
			 *			`false` otherwise.
			 **/
			virtual bool removeView(QString name);

		private:
			friend class ItemMultiViewWidgetPrivate;

			ItemMultiViewWidgetPrivate* d;
	};
}

#endif // ITEM_MULTI_VIEW_WIDGET_H