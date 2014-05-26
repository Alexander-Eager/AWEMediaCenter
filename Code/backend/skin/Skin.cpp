// header file
#include "Skin.h"

// math
#include <cmath>

// debug
#include <QDebug>

using namespace JSON;
using namespace AWE;

namespace UI
{
	class SkinPrivate
	{
		public:
			// parent
			Skin* p;

			QHash<QString, ColoredFont> fonts;
			QHash<QString, QColor> colors;
			QHash<QString, JsonValue> widgetConfig;

			// this makes the gradient colors for the given config,
			// along with a few other common things
			void gradientCommon(const JsonObject obj, QGradient& grad) const
			{
				// coordinate mode
				if (obj.get("coordinate mode").isNumber())
				{
					int mode = obj.get("coordinate mode").toInteger();
					switch (mode)
					{
						case 0:
							grad.setCoordinateMode(QGradient::LogicalMode);
							break;
						case 1:
							grad.setCoordinateMode(QGradient::StretchToDeviceMode);
							break;
						case 2: default:
							grad.setCoordinateMode(QGradient::ObjectBoundingMode);
							break;
					}
				}
				else
				{
					grad.setCoordinateMode(QGradient::ObjectBoundingMode);
				}
				// spread
				if (obj.get("spread").isNumber())
				{
					int mode = obj.get("spread").toInteger();
					switch (mode)
					{
						case 2:
							grad.setSpread(QGradient::RepeatSpread);
							break;
						case 1:
							grad.setSpread(QGradient::ReflectSpread);
							break;
						case 0: default:
							grad.setSpread(QGradient::PadSpread);
							break;
					}
				}
				else
				{
					grad.setSpread(QGradient::PadSpread);
				}
				// colors
				if (obj.get("colors").isArray())
				{
					const JsonArray arr = obj["colors"].toArray();
					for (auto s : arr)
					{
						if (!s.isArray())
						{
							continue;
						}
						const JsonArray stop = s.toArray();
						if (stop.count() < 2)
						{
							continue;
						}
						grad.setColorAt(stop.at(0).toDouble(),
							p->makeColor(stop.at(1)));
					}
				}
				else
				{
					grad.setColorAt(0, p->getColor("default gradient 0"));
					grad.setColorAt(1, p->getColor("default gradient 1"));
				}
			}
	};
}

using namespace UI;

Skin::Skin(QString file)
	:	MetadataHolder(file),
		d(new SkinPrivate)
{
	d->p = this;

	// get the colors
	JsonObject colors = getConfigFile()->getMember({"colors"}).toObject();
	QList<QString> keys = colors.keys();
	for (auto color : keys)
	{
		d->colors[color] = makeColor(colors[color]);
	}

	// get the fonts
	JsonObject fonts = getConfigFile()->getMember({"fonts"}).toObject();
	keys = fonts.keys();
	for (auto font : keys)
	{
		d->fonts[font] = makeFont(fonts[font]);
	}

	// get the widget config
	JsonObject widgets = getConfigFile()
		->getMember({"widget settings"}).toObject();
	keys = widgets.keys();
	for (auto widget : keys)
	{
		d->widgetConfig[widget] = widgets[widget];
	}
}

Skin::~Skin()
{
	delete d;
}

ColoredFont Skin::getFont(QString font) const
{
	if (d->fonts.contains(font))
	{
		return d->fonts[font];
	}
	return d->fonts["normal"];
}

QColor Skin::getColor(QString color) const
{
	if (d->colors.contains(color))
	{
		return d->colors[color];
	}
	return d->colors["default"];
}

JsonValue Skin::getWidgetConfig(QString name) const
{
	if (d->widgetConfig.contains(name))
	{
		return d->widgetConfig[name];
	}
	return JsonValue::Null;
}

QColor Skin::makeColor(const JsonValue config) const
{
	if (config.isString())
	{
		// just get the color
		return getColor(config.toString());
	}
	else if (config.isArray())
	{
		const JsonArray arr = config.toArray();
		if (arr.count() == 0)
		{
			return getColor("default");
		}
		else if (arr.at(0).isString())
		{
			// named color
			QColor ans = arr.at(0).toString();
			if (arr.at(1).isNumber())
			{
				ans.setAlpha(arr.at(1).toInteger());
			}
			return ans;
		}
		else if (arr.at(0).isNumber() && arr.at(1).isNumber()
			&& arr.at(2).isNumber())
		{
			// rgb(a) color
			QColor ans(arr.at(0).toInteger(),
				arr.at(1).toInteger(), arr.at(2).toInteger());
			if (arr.at(3).isNumber())
			{
				ans.setAlpha(arr.at(3).toInteger());
			}
			return ans;
		}
	}
	else if (config.isObject())
	{
		const JsonObject obj = config.toObject();
		if (obj.get("name").isString())
		{
			// named color
			QColor ans = obj.get("name").toString();
			if (obj.get("a").isNumber())
			{
				ans.setAlpha(obj.get("a").toInteger());
			}
			else if (obj.get("alpha").isNumber())
			{
				ans.setAlpha(obj.get("alpha").toInteger());
			}
			return ans;
		}
		else
		{
			// potentially rgb(a) color
			QColor ans;
			// r
			if (obj.get("r").isNumber())
			{
				ans.setRed(obj.get("r").toInteger());
			}
			else if (obj.get("red").isNumber())
			{
				ans.setRed(obj.get("red").toInteger());
			}
			else
			{
				// no r
				return getColor("default");
			}
			// g
			if (obj.get("g").isNumber())
			{
				ans.setGreen(obj.get("g").toInteger());
			}
			else if (obj.get("green").isNumber())
			{
				ans.setGreen(obj.get("green").toInteger());
			}
			else
			{
				// no g
				return getColor("default");
			}
			// b
			if (obj.get("b").isNumber())
			{
				ans.setBlue(obj.get("b").toInteger());
			}
			else if (obj.get("blue").isNumber())
			{
				ans.setBlue(obj.get("blue").toInteger());
			}
			else
			{
				// no b
				return getColor("default");
			}
			// a (not required)
			if (obj.get("a").isNumber())
			{
				ans.setAlpha(obj.get("a").toInteger());
			}
			else if (obj.get("alpha").isNumber())
			{
				ans.setAlpha(obj.get("alpha").toInteger());
			}
			return ans;
		}
	}
	return getColor("default");
}

ColoredFont Skin::makeFont(const JsonValue config) const
{
	if (config.isString())
	{
		return getFont(config.toString());
	}
	else if (config.isObject())
	{
		const JsonObject obj = config.toObject();
		ColoredFont ans = getFont("normal");
		QFont font = ans.getFont();
		// name
		if (obj.get("name").isString())
		{
			font.setFamily(obj.get("name").toString());
		}
		else if (obj.get("family").isString())
		{
			font.setFamily(obj.get("family").toString());
		}
		// size
		if (obj.get("size").isNumber())
		{
			font.setPointSizeF(obj.get("size").toDouble());
		}
		// weight
		if (obj.get("weight").isNumber())
		{
			font.setWeight(obj.get("weight").toInteger());
		}
		// italic
		if (obj.get("italic").isBoolean())
		{
			font.setItalic(obj.get("italic").toBoolean());
		}
		ans.setFont(font);
		// color or pen
		if (obj.contains("pen"))
		{
			ans.setPen(makePen(obj.get("pen")));
		}
		else if (obj.contains("color"))
		{
			ans.setPen(makePen(obj.get("color")));
		}
		return ans;
	}
	return getFont("normal");
}

QPointF Skin::makePoint(const JsonValue config) const
{
	if (config.isNumber())
	{
		return QPointF(config.toDouble(), config.toDouble());
	}
	else if (config.isArray())
	{
		const JsonArray arr = config.toArray();
		if (arr.at(0).isNumber() && arr.at(1).isNumber())
		{
			return QPointF(arr.at(0).toDouble(),
				arr.at(1).toDouble());
		}
	}
	return QPointF(0, 0);
}

QPointF Skin::makePoint(const JsonValue config, QRectF rect) const
{
	QPointF ans = makePoint(config);
	ans.setX(ans.x() * rect.width() + rect.left());
	ans.setY(ans.y() * rect.height() + rect.top());
	return ans;
}

QSizeF Skin::makeSize(const JsonValue config) const
{
	QPointF point = makePoint(config);
	return QSizeF(point.x(), point.y());
}

QSizeF Skin::makeSize(const JsonValue config, QSizeF size) const
{
	QPointF point = makePoint(config, QRectF(QPointF(0, 0), size));
	return QSizeF(point.x(), point.y());
}

QRectF Skin::makeRect(const JsonValue config) const
{
	QRectF ans;
	if (config.isObject())
	{
		const JsonObject obj = config.toObject();
		// top left
		if (obj.contains("top left"))
		{
			ans.setTopLeft(makePoint(obj.get("top left")));
		}
		else
		{
			ans.setLeft(0);
			ans.setTop(0);
		}
		// size or bottom right
		if (obj.contains("size"))
		{
			ans.setSize(makeSize(obj.get("size")));
		}
		else if (obj.contains("bottom right"))
		{
			ans.setBottomRight(makePoint(obj.get("bottom right")));
		}
		else
		{
			ans.setWidth(0);
			ans.setHeight(0);
		}
	}
	else if (config.isArray())
	{
		const JsonArray arr = config.toArray();
		// [x, y, w, h]
		if (arr.count() >= 4)
		{
			ans.setLeft(arr.at(0).toDouble());
			ans.setTop(arr.at(1).toDouble());
			ans.setWidth(arr.at(2).toDouble());
			ans.setHeight(arr.at(3).toDouble());
		}
		// [<point>, <size>]
		else
		{
			ans.setTopLeft(makePoint(arr.at(0)));
			ans.setSize(makeSize(arr.at(1)));
		}
	}
	return ans;
}

QRectF Skin::makeRect(const JsonValue config, QRectF rect) const
{
	QRectF ans = makeRect(config);
	ans.setLeft(ans.left() * rect.width() + rect.left());
	ans.setTop(ans.top() * rect.height() + rect.top());
	ans.setWidth(ans.width() * rect.width());
	ans.setHeight(ans.height() * rect.height());
	return ans;
}

QRadialGradient Skin::makeRadialGradient(const JsonValue config) const
{
	QRadialGradient ans;
	if (!config.isObject())
	{
		return ans;
	}
	const JsonObject obj = config.toObject();
	// stuff common to all gradients
	d->gradientCommon(obj, ans);
	// central point
	ans.setCenter(makePoint(obj.get("center")));
	// central radius
	if (obj.get("radius").isNumber())
	{
		ans.setRadius(obj.get("radius").toDouble());
	}
	else if (obj.get("center radius").isNumber())
	{
		ans.setRadius(obj.get("center radius").toDouble());
	}
	// focal point
	if (obj.contains("focus"))
	{
		ans.setFocalPoint(makePoint(obj.get("focus")));
	}
	else if (obj.contains("focal point"))
	{
		ans.setFocalPoint(makePoint(obj.get("focal point")));
	}
	// focal radius
	if (obj.get("focal radius").isNumber())
	{
		ans.setFocalRadius(obj.get("focal radius").toDouble());
	}
	return ans;
}

QLinearGradient Skin::makeLinearGradient(const JsonValue config) const
{
	QLinearGradient ans;
	if (!config.isObject())
	{
		return ans;
	}
	const JsonObject obj = config.toObject();
	// stuff common to all gradients
	d->gradientCommon(obj, ans);
	// starting point
	if (obj.contains("start"))
	{
		ans.setStart(makePoint(obj.get("start")));
	}
	else if (obj.contains("starting point"))
	{
		ans.setStart(makePoint(obj.get("starting point")));
	}
	else if (obj.contains("first stop"))
	{
		ans.setStart(makePoint(obj.get("first stop")));
	}
	else
	{
		ans.setStart(0, 0);
	}
	// ending point
	if (obj.contains("end"))
	{
		ans.setFinalStop(makePoint(obj.get("end")));
	}
	else if (obj.contains("finish"))
	{
		ans.setFinalStop(makePoint(obj.get("finish")));
	}
	else if (obj.contains("final stop"))
	{
		ans.setFinalStop(makePoint(obj.get("final stop")));
	}
	else if (obj.contains("ending point"))
	{
		ans.setFinalStop(makePoint(obj.get("ending point")));
	}
	else if (obj.contains("finishing point"))
	{
		ans.setFinalStop(makePoint(obj.get("finishing point")));
	}
	else if (ans.coordinateMode() == QGradient::LogicalMode)
	{
		ans.setFinalStop(50, 50);
	}
	else
	{
		ans.setFinalStop(0.5, 0.5);
	}
	return ans;
}

QConicalGradient Skin::makeConicalGradient(const JsonValue config) const
{
	QConicalGradient ans;
	const JsonObject obj = config.toObject();
	// stuff common to all gradients
	d->gradientCommon(obj, ans);
	// get the center point
	if (obj.contains("center"))
	{
		ans.setCenter(makePoint(obj.get("center")));
	}
	else if (ans.coordinateMode() == QGradient::LogicalMode)
	{
		ans.setCenter(50, 50);
	}
	else
	{
		ans.setCenter(0.5, 0.5);
	}
	// get the angle
	if (obj.get("angle").isNumber())
	{
		ans.setAngle(obj.get("angle").toDouble());
	}
	else
	{
		ans.setAngle(0);
	}
	return ans;
}

QBrush Skin::makeBrush(const JsonValue config) const
{
	if (config.isNull())
	{
		// the configuration is wacko, so no brush
		return Qt::NoBrush;
	}
	if (!config.isObject())
	{
		// assume it was a color config
		return makeColor(config);
	}
	const JsonObject obj = config.toObject();
	int style = 0;
	if (obj.get("type").isNumber())
	{
		style = obj.get("type").toInteger();
	}
	else if (obj.get("style").isNumber())
	{
		style = obj.get("style").toInteger();
	}
	else if (obj.get("brush style").isNumber())
	{
		style = obj.get("brush style").toInteger();
	}
	else
	{
		return makeColor(config);
	}
	switch (style)
	{
		case 1: case 2: case 3: case 4: case 5: case 6:
		case 7: case 8: case 9: case 10: case 11: case 12:
		case 13: case 14: // these are all colored patterns
			return QBrush(makeColor(obj.get("color")),
				(Qt::BrushStyle) style);
		case 15: // linear gradient
			return makeLinearGradient(config);
		case 17: // conical gradient
			return makeConicalGradient(config);
		case 16: // radial gradient
			return makeRadialGradient(config);
		case 24: // texture pattern
			if (obj.get("texture").isString())
			{
				return QPixmap(obj.get("texture").toString());
			}
			else if (obj.get("pattern").isString())
			{
				return QPixmap(obj.get("pattern").toString());
			}
		case 0: default: // just no brush
			return Qt::NoBrush;
	}
}

QPen Skin::makePen(const JsonValue config) const
{
	if (!config.isObject())
	{
		return makeColor(config);
	}
	const JsonObject obj = config.toObject();
	QPen pen;
	// pen style
	int style = -1;
	if (obj.get("pen").isNumber())
	{
		style = obj.get("pen").toInteger();
	}
	else if (obj.get("pen style").isNumber())
	{
		style = obj.get("pen style").toInteger();
	}
	if (style < 0 || style > 6)
	{
		pen.setBrush(makeBrush(config));
		return pen;
	}
	pen.setStyle((Qt::PenStyle) style);
	// cap style
	style = 0;
	if (obj.get("cap").isNumber())
	{
		style = obj.get("cap").toInteger();
	}
	else if (obj.get("cap style").isNumber())
	{
		style = obj.get("cap style").toInteger();
	}
	switch (style)
	{
		case 16: case 32:
			pen.setCapStyle((Qt::PenCapStyle) style);
			break;
		case 0: default:
			pen.setCapStyle(Qt::SquareCap);
			break;
	}
	// join style
	style = 64;
	if (obj.get("join").isNumber())
	{
		style = obj.get("join").toInteger();
	}
	else if (obj.get("join style").isNumber())
	{
		style = obj.get("join style").toInteger();
	}
	switch (style)
	{
		case 0: case 128: case 256:
			pen.setJoinStyle((Qt::PenJoinStyle) style);
			break;
		case 64: default:
			pen.setJoinStyle(Qt::BevelJoin);
			break;
	}
	// width
	if (obj.get("width").isNumber())
	{
		pen.setWidthF(obj.get("width").toDouble());
	}
	else
	{
		pen.setWidthF(1.5);
	}
	// brush or color
	if (obj.contains("color"))
	{
		pen.setBrush(makeBrush(obj.get("color")));
	}
	else if (obj.contains("brush"))
	{
		pen.setBrush(makeBrush(obj.get("brush")));
	}
	else
	{
		pen.setBrush(getColor("default"));
	}
	// pattern for the line, if necessary
	if (pen.style() == Qt::CustomDashLine)
	{
		if (obj.get("pattern").isArray())
		{
			QVector<qreal> pattern;
			const JsonArray arr = obj.get("pattern").toArray();
			for (int i = 1; i < arr.count(); i += 2)
			{
				pattern << arr.at(i - 1).toDouble();
				pattern << arr.at(i).toDouble();
			}
			if (pattern.count())
			{
				pen.setDashPattern(pattern);
			}
			else
			{
				pen.setStyle(Qt::SolidLine);
			}
		}
		else
		{
			pen.setStyle(Qt::SolidLine);
		}
	}
	return pen;
}