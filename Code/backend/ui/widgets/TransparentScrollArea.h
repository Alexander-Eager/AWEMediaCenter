#ifndef TRANSPARENT_SCROLL_AREA_H
#define TRANSPARENT_SCROLL_AREA_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QScrollArea>

namespace UI
{
	/**
	 * \brief Essentially `QScrollArea`, but
	 *			with a transparent background.
	 *
	 * Unfortuneately, Qt's built-in scroll
	 * area classes all have a frame and a
	 * solid background, which does not work
	 * well with AWEMC's UI. So this class
	 * takes all of that extra stuff away
	 * and leaves behind only the scroll
	 * bars and the widget inside.
	 *
	 * If you want meaningful documentation
	 * on how to use this class, see
	 * [`QScrollArea`](http://qt-project.org/doc/qt-4.8/qscrollarea.html).
	 **/
	class AWEMC_BACKEND_LIBRARY TransparentScrollArea : public QScrollArea
	{
		public:
			/**
			 * \brief Make with the given parent.
			 *
			 * \param parent The parent widget.
			 **/
			TransparentScrollArea(QWidget* parent);
	};
}

#endif