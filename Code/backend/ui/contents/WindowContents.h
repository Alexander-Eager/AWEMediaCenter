#ifndef WINDOW_CONTENTS_H
#define WINDOW_CONTENTS_H

// library macros
#include "macros/BackendLibraryMacros.h"

// general data
#include <QString>

// UI widget
#include <QWidget>

namespace UI
{
	// forward declaration
	class MainWindow;

	/**
	 * \brief An interface that describes what could be
	 *			the contents of the main window.
	 **/
	class AWEMC_BACKEND_LIBRARY WindowContents : public QObject
	{
		public:
			/**
			 * \brief Destroy this object.
			 **/
			virtual ~WindowContents() { }

			/**
			 * \brief Describes the type of contents.
			 *
			 * For a `FileBrowser`, for example, this would
			 * return `"File Browser"`.
			 *
			 * \returns A string describing the contents.
			 **/
			virtual QString getType() = 0;

			/**
			 * \brief Set the parent of this
			 *			contents pane (i.e., the main window).
			 *
			 * \param window The `MainWindow` of AWEMC.
			 **/
			virtual void setParent(MainWindow* window) = 0;

			/**
			 * \brief Gets the main widget for this screen.
			 *
			 * All of the UI elements for this window pane
			 * should be contained inside this widget (usually,
			 * this widget has a designated layout).
			 *
			 * \returns The main widget for this contents pane.
			 **/
			virtual QWidget* getWidget() = 0;

			/**
			 * \brief Called after the widget is added to the
			 *			window for additional setup.
			 **/
			virtual void open() = 0;
	};
}

#endif