// header file
#include "TransparentScrollArea.h"

// for changing the background color
#include "settings/AWEMC.h"
#include <QPalette>

using namespace UI;
using namespace AWE;

TransparentScrollArea::TransparentScrollArea(QWidget* parent)
	:	QScrollArea(parent)
{
	// changes the palette's background color to be transparent
	auto makeTransparent = [this] ()
		{
			QPalette p = viewport()->palette();
			p.setColor(QPalette::Window, AWEMC::settings()
				->getCurrentSkin()->getColor("transparent"));
			viewport()->setPalette(p);
		};

	// get rid of the frame
	setFrameShape(QFrame::NoFrame);
	// make the background transparent
	makeTransparent();
	// make sure the background transparency will change with the the skin
	connect(AWEMC::settings(), &GlobalSettings::skinChanged,
			this, makeTransparent);
}