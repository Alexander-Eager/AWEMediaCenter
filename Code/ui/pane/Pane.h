#ifndef PANE_H
#define PANE_H

// the superclass
#include <QWidget>

// for painting
#include <QPaintEvent>

namespace UI
{
	/**
	 * \brief A surface representing a pane of widgets.
	 *
	 * Panes have a frame and a semi-transparent background
	 * color. This class is meant to be subclassed for use
	 * in `WindowContents` objects.
	 **/
	class Pane : public QWidget
	{
		public:
			/**
			 * \brief Construct with the given parent widget.
			 *
			 * \param parent The parent widget.
			 **/
			Pane(QWidget* parent);

		protected:
			/**
			 * \brief Paints this pane.
			 *
			 * \param event The (ignored) paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);
	};
}

#endif