#ifndef PANE_H
#define PANE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the superclasses
#include <QWidget>
#include "ui/Configurable.h"

// for painting
#include <QPaintEvent>

namespace UI
{
	// internal data class
	class PanePrivate;

	/**
	 * \brief A surface representing a pane of widgets.
	 *
	 * Panes have a frame and a semi-transparent background
	 * color. This class is meant to be subclassed for use
	 * in `WindowContents` objects.
	 *
	 * If your subclass depends on the amount of space available
	 * to the contents of the pane, make sure to check via
	 * `getContentsMargins()`.
	 **/
	class AWEMC_BACKEND_LIBRARY Pane : public QWidget, public Configurable
	{
		public:
			/**
			 * \brief Construct with the given parent widget.
			 *
			 * \param parent The parent widget.
			 **/
			Pane(QWidget* parent);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~Pane();

			/**
			 * \brief Make from the given configuration.
			 *
			 * Once you call this function, the pane will
			 * no longer change when the skin is changed.
			 *
			 * \param data The configuration to use.
			 **/
			virtual void useConfig(JSON::JsonValue data);

			/** 
			 * \brief Call this to make the pane
			 *			use the current skin's
			 *			configuration.
			 **/
			virtual void useDefaultConfig();

		protected:
			/**
			 * \brief Paints this pane.
			 *
			 * \param event The (ignored) paint event.
			 **/
			virtual void paintEvent(QPaintEvent* event);

			/**
			 * \brief Updates painting details.
			 *
			 * \param event The (ignored) resize event.
			 **/
			virtual void resizeEvent(QResizeEvent* event);

		private:
			PanePrivate* d;
	};
}

#endif