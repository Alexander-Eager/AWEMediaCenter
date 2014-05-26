#ifndef ITEM_WIDGET_H
#define ITEM_WIDGET_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QWidget>

// Q_OBJECT
#include <QObject>

// for the item type
#include <QString>

// for event handling
#include <QMouseEvent>

// for painting
#include <QPaintEvent>

namespace UI
{
	/**
	 * \brief Defines an abstract item widget
	 *			for lists.
	 *
	 * It behaves in a way similar to `QListWidgetItem`,
	 * but unfortunately `QListWidget` has an opaque
	 * background and does not work well with AWEMC. I
	 * took this opportunity to make a set of similar
	 * widgets that do not have this problem.
	 *
	 * Subclasses need to define:
	 *	- `getItemType()`: the type of `ItemWidget`
	 *								(for casting purposes).
	 *	- `paintEvent()`: to paint the widget.
	 *	- The minimum size of the widget (so that it shows up).
	 **/
	class AWEMC_BACKEND_LIBRARY ItemWidget : public QWidget
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make with the given parent widget.
			 *
			 * \param parent The parent widget.
			 * \param highlightable `true` if this widget
			 *						can be highlighted and
			 *						selected, `false` if not.
			 **/
			ItemWidget(QWidget* parent, bool highlightable);

			/**
			 * \brief Destroys this object.
			 **/
			virtual ~ItemWidget();

			/**
			 * \brief Get the item type (as a string).
			 *
			 * \returns The item type (as a string).
			 **/
			virtual QString getItemType() const = 0;

			/**
			 * \brief Make a copy of this item widget.
			 *
			 * \returns A dynamically allocated copy of this widget.
			 **/
			virtual ItemWidget* makeCopy() const = 0;

			/**
			 * \brief Determine if this item is highlighted.
			 *
			 * \returns `true` if this item is highlighted,
			 *			`false` otherwise.
			 **/
			virtual bool isHighlighted() const;

			/**
			 * \brief Determine if this item can be highlighted
			 *			and selected.
			 *
			 * \returns `true` if this item is highlightabel,
			 *			`false` otherwise.
			 **/
			virtual bool isHighlightable() const;

			/**
			 * \brief Make this item highlightable or not.
			 *
			 * \param newState `true` if this item should be
			 *					highlightable, `false` if not.
			 **/
			virtual void setHighlightable(bool newState);

			/**
			 * \brief Fix this item's size to fit in the given
			 *			size.
			 *
			 * If `size == QSize(-1, -1)`, the item should not
			 * fix its size.
			 *
			 * This is mostly used by `ItemCollectionWidget`s to
			 * make sure that the item does not get swallowed up
			 * by the spacers used to align the items.
			 *
			 * \param size The size to fit inside.
			 *
			 * \returns `true` if this item can fit in `size`,
			 *			`false` if it cannot.
			 **/
			virtual bool fixSizeToFitIn(QSize size) = 0;

			/**
			 * \brief Get the size this item has to fit in.
			 *
			 * This is the size set by `fixSizeToFitIn()`.
			 *
			 * \returns The size this item has to fit in.
			 **/
			virtual QSize getSizeToFitIn() const = 0;

		public slots:
			/**
			 * \brief Highlight this item.
			 *
			 * There are two steps to item selection:
			 * highlighting and selection. It is like
			 * click vs. double-click.
			 *
			 * Highlighting the item also causes a change in
			 * the appearance of the item.
			 **/
			virtual void highlight();

			/**
			 * \brief Unhighlight this item.
			 *
			 * There are two steps to item selection:
			 * highlighting and selection. It is like
			 * click vs. double-click.
			 *
			 * Unhighlighting the item also causes a change in
			 * the appearance of the item.
			 **/
			virtual void unhighlight();

			/**
			 * \brief Change the highlight state.
			 *
			 * There are two steps to item selection:
			 * highlighting and selection. It is like
			 * click vs. double-click.
			 *
			 * Highlighting/unhighlighting the item also
			 * causes a change in the appearance of the item.
			 *
			 * \param[in] newState The new highlighting state.
			 *						Sends the appropriate signal
			 *						depending on the value.
			 **/
			virtual void setHighlighting(bool newState);

		signals:
			/**
			 * \brief Sent when this item is highlighted.
			 **/
			void highlighted();

			/**
			 * \brief Sent when this item is highlighted.
			 *
			 * \param[in] item This item.
			 **/
			void highlighted(ItemWidget* item);

			/**
			 * \brief Sent when this item is unhighlighted.
			 **/
			void unhighlighted();

			/**
			 * \brief Sent when this item is unhighlighted.
			 *
			 * \param[in] item This item.
			 **/
			void unhighlighted(ItemWidget* item);

			/**
			 * \brief Sent when this item's highlighting state
			 *			changes.
			 *
			 * \param[in] newState The new highlighting state.
			 **/
			void highlightingChanged(bool newState);

			/**
			 * \brief Sent when this item's highlighting state
			 *			changes.
			 *
			 * \param[in] newState The new highlighting state.
			 * \param[in] item This item.
			 **/
			void highlightingChanged(bool newState, ItemWidget* item);

			/**
			 * \brief Sent when this item is selected.
			 **/
			void selected();

			/**
			 * \brief Sent when this item is selected.
			 *
			 * \param[in] item This item.
			 **/
			void selected(ItemWidget* item);

			/**
			 * \brief Sent when this item is clicked.
			 *
			 * Note that clicking this item also
			 * changes its highlighting state.
			 **/
			void clicked();

			/**
			 * \brief Sent when this item is double-clicked.
			 *
			 * Note that double-clicking causes two click events.
			 * The result is that both `highlighted()` and
			 * `unhighlighted()` are sent.
			 **/
			void doubleClicked();

		protected:
			/**
			 * \brief Handle mouse click events.
			 *
			 * Left-clicking on an item highlights it.
			 *
			 * \param event The mouse event.
			 **/
			virtual void mousePressEvent(QMouseEvent* event);

			/**
			 * \brief Handle mouse double-click events.
			 *
			 * Left-double-clicking on an item selects it.
			 *
			 * \param event The mouse event.
			 **/
			virtual void mouseDoubleClickEvent(QMouseEvent* event);

			/**
			 * \brief Paint the background for this item.
			 *
			 * Generally, the background is only painted
			 * if the item is highlighted, but it depends
			 * on the subclass.
			 *
			 * The background is a blue gradient.
			 *
			 * \param event The (unused) paint event.
			 **/
			virtual void paintBackground(QPaintEvent* event);

			/**
			 * \brief Paint the outline for this item.
			 *
			 * Generally, the outline is only painted
			 * if the item is highlighted, but it depends
			 * on the subclass.
			 *
			 * The outline is a solid black color.
			 *
			 * \param event The (unused) paint event.
			 **/
			virtual void paintOutline(QPaintEvent* event);

			/**
			 * \brief Paints the background and outline.
			 *
			 * \param event The paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);

		private:
			/** \brief The highlighting state. **/
			bool myHighlighting;

			/** \brief Can this be highlighted? **/
			bool myCanBeHighlighted;
	};
}

#endif