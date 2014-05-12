#ifndef WINDOW_CONTENTS_H
#define WINDOW_CONTENTS_H

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
	class WindowContents
	{
		public:
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

			/**
			 * \brief Gets the background canvas.
			 *
			 * Generally, this is where a fanart image is
			 * shown, but it might eventually be a place
			 * where a media file is being played.
			 *
			 * If there is no background for this contents
			 * pane, `nullptr` should be returned.
			 *
			 * This function means nothing yet, since I have
			 * not yet done any work with SFML.
			 *
			 * \returns The background canvas.
			 **/
			// virtual SFMLCanvas* getBackground() = 0;

			/**
			 * \brief Gets the small minimized video canvas.
			 *
			 * Generally, this is where a fanart image is
			 * shown, but it might eventually be a place
			 * where a media file is being played.
			 *
			 * If there is no minimized video widget for this
			 * contents pane, `nullptr` should be returned.
			 *
			 * This function means nothing yet, since I have
			 * not yet done any work with SFML.
			 *
			 * \returns The minimized video canvas.
			 **/
			// virtual SFMLCanvas* getMinimizedVideo() = 0;
	};
}

#endif