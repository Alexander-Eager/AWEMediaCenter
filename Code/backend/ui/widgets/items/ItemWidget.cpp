// header file
#include "ItemWidget.h"

// for painting
#include <QPainter>
#include <QPen>
#include <QBrush>
#include "settings/AWEMC.h"

using namespace AWE;
using namespace JSON;

namespace UI
{
	class ItemWidgetPrivate
	{
		public:
			ItemWidget* p;
			// describe highlighting states
			bool isHighlighted;
			bool highlightingEnabled;

			// stuff for painting
			QPen outline;
			QBrush brush;
			QPointF cornerRadius;
			bool usingSkin;

			inline void configure(const JsonValue config);
	};
}

using namespace UI;

ItemWidget::ItemWidget(QWidget* parent, bool canBeHighlighted)
	:	QWidget(parent),
		d(new ItemWidgetPrivate)
{
	d->p = this;
	d->usingSkin = true;
	d->isHighlighted = false;
	setHighlightable(canBeHighlighted);

	// the configuration for the background
	auto updateSkinData = [this] ()
		{
			if (d->usingSkin && d->highlightingEnabled)
			{
				d->configure(AWEMC::settings()->getCurrentSkin()
					->getWidgetConfig("Item Widget"));
			}
		};

	connect(AWEMC::settings(), &GlobalSettings::skinChanged,
			this, updateSkinData);
	updateSkinData();
}

ItemWidget::~ItemWidget()
{
	delete d;
}

bool ItemWidget::isHighlighted() const
{
	return d->isHighlighted;
}

bool ItemWidget::isHighlightable() const
{
	return d->highlightingEnabled;
}

void ItemWidget::setHighlightable(bool newState)
{
	// this needs a way to specify the fit-in size
	// to the subclasses again, but it is pure virtual
	d->highlightingEnabled = newState;
	if (d->highlightingEnabled)
	{
		setContentsMargins(d->cornerRadius.x(),
			d->cornerRadius.y(), d->cornerRadius.x(),
			d->cornerRadius.y());
		update();
	}
	else
	{
		setContentsMargins(0, 0, 0, 0);
		setHighlighting(false);
		update();
	}
}

void ItemWidget::highlight()
{
	setHighlighting(true);
}

void ItemWidget::unhighlight()
{
	setHighlighting(false);
}

void ItemWidget::setHighlighting(bool newState)
{
	if (d->highlightingEnabled && d->isHighlighted != newState)
	{
		// set the new state
		d->isHighlighted = newState;
		// update the widget's image
		update();
		// emit the appropriate signals
		emit highlightingChanged(newState);
		emit highlightingChanged(newState, this);
		if (newState)
		{
			emit highlighted();
			emit highlighted(this);
		}
		else
		{
			emit unhighlighted();
			emit unhighlighted(this);
		}
	}
}

void ItemWidget::useConfig(JsonValue data)
{
	d->usingSkin = false;
	d->configure(data);
}

void ItemWidget::useDefaultConfig()
{
	d->usingSkin = true;
	d->configure(AWEMC::settings()->getCurrentSkin()
		->getWidgetConfig("Item Widget"));
}

void ItemWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
	{
		// we only care about left-button clicks,
		// so propogate everything else up the list
		event->ignore();
	}
	else
	{
		event->accept();
		// highlight this item
		setHighlighting(!isHighlighted());
		// indicate that this was clicked
		emit clicked();
	}
}

void ItemWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
	{
		// we only care about left-button clicks,
		// so propogate everything else up the list
		event->ignore();
	}
	else
	{
		event->accept();
		// indicate that this item was selected
		if (d->highlightingEnabled)
		{
			emit selected();
			emit selected(this);
		}
		// indicate that this was double-clicked
		emit doubleClicked();
	}
}

void ItemWidget::paintEvent(QPaintEvent*)
{
	if (d->isHighlighted)
	{
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing);
		painter.setBrush(d->brush);
		painter.setPen(d->outline);
		QRect drawInMe(0, 0, width() - 1, height() - 1);
		painter.drawRoundedRect(drawInMe, d->cornerRadius.x(),
			d->cornerRadius.y(), Qt::AbsoluteSize);
	}
}

void ItemWidgetPrivate::configure(const JsonValue config)
{
	Skin* s = AWEMC::settings()->getCurrentSkin();
	const JsonObject obj = config.toObject();
	// corner curvature
	if (obj.contains("corner radius"))
	{
		cornerRadius = s->makePoint(obj["corner radius"]);
	}
	else
	{
		cornerRadius.setX(10.0);
		cornerRadius.setY(10.0);
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
		QColor c("lightskyblue");
		c.setAlpha(100);
		gradient.setColorAt(0, c);
		c.setNamedColor("blue");
		c.setAlpha(100);
		gradient.setColorAt(1, c);
		brush = gradient;
	}

	p->update();
}