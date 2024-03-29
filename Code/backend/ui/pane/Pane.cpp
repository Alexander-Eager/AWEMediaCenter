// header file
#include "Pane.h"

// global settings
#include "settings/AWEMC.h"

// for painting
#include <QPainter>

// debug
#include <QDebug>

using namespace JSON;
using namespace AWE;

namespace UI
{
	class PanePrivate
	{
		public:
			// parent
			Pane* p;

			// determines if this follows the skin's details
			bool usingSkin;

			// values to be applied
			QBrush brush;
			QPen outline;
			QPointF cornerRadius;

			// get values to apply
			inline void updateUIData();
			inline void configure(const JsonValue data);
	};
}

using namespace UI;

Pane::Pane(QWidget* parent)
	:	QWidget(parent),
		d(new PanePrivate)
{
	d->p = this;
	d->usingSkin = true;

	// connect skin adjustments
	auto refresh = [this] ()
		{
			d->updateUIData();
		};

	connect(AWEMC::settings(), &GlobalSettings::skinChanged,
			this, refresh);

	refresh();
}

Pane::~Pane()
{
	delete d;
}

void Pane::useConfig(JSON::JsonValue data)
{
	d->usingSkin = false;
	d->configure(data);
}

void Pane::useDefaultConfig()
{
	d->usingSkin = true;
	d->updateUIData();
}

void Pane::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	painter.setBrush(d->brush);
	painter.setPen(d->outline);
	QRect drawInMe(0, 0, width() - 1, height() - 1);
	painter.drawRoundedRect(drawInMe, d->cornerRadius.x(),
		d->cornerRadius.y(), Qt::AbsoluteSize);
}

void Pane::resizeEvent(QResizeEvent*)
{
	// nothing
}

void PanePrivate::updateUIData()
{
	if (usingSkin)
	{
		configure(AWEMC::settings()->getCurrentSkin()
			->getWidgetConfig("Pane"));
	}
}

void PanePrivate::configure(const JsonValue data)
{
	Skin* s = AWEMC::settings()->getCurrentSkin();
	const JsonObject obj = data.toObject();
	// corner curvature
	if (obj.contains("corner radius"))
	{
		cornerRadius = s->makePoint(obj["corner radius"]);
	}
	else
	{
		cornerRadius.setX(15.0);
		cornerRadius.setY(15.0);
	}
	// outline color
	if (obj.contains("outline"))
	{
		outline = s->makePen(obj["outline"]);
	}
	else
	{
		outline.setStyle(Qt::NoPen);
	}

	// update the parent's contents margins
	qreal horiz = cornerRadius.x();
	qreal vert = cornerRadius.y();
	p->setContentsMargins(horiz, vert, horiz, vert);

	// background brush
	if (obj.contains("background"))
	{
		brush = s->makeBrush(obj["background"]);
	}
	else
	{
		QRadialGradient gradient;
		// center
		gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
		gradient.setCenter(0, 0);
		gradient.setCenterRadius(0.5);
		// spread
		gradient.setSpread(QGradient::RepeatSpread);
		// colors
		QColor c("darkgray");
		c.setAlpha(200);
		gradient.setColorAt(0, c);
		c.setNamedColor("gray");
		c.setAlpha(200);
		gradient.setColorAt(1, c);
		brush = gradient;
	}

	// update the displayed image
	p->update();
}
