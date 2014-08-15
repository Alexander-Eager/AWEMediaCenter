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
				if (obj["coordinate mode"].isNumber())
				{
					int mode = obj["coordinate mode"].toInteger();
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
				if (obj["spread"].isNumber())
				{
					int mode = obj["spread"].toInteger();
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
				if (obj["colors"].isArray())
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
						grad.setColorAt(stop.value(0).toDouble(),
							p->makeColor(stop.value(1)));
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
    qDebug() << "Font" << font << "does not exist.";
	return d->fonts["normal"];
}

QColor Skin::getColor(QString color) const
{
	if (d->colors.contains(color))
	{
		return d->colors[color];
	}
    qDebug() << "Color" << color << "does not exist.";
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
		else if (arr.value(0).isString())
		{
			// named color
			QColor ans = arr.value(0).toString();
			if (arr.value(1).isNumber())
			{
				ans.setAlpha(arr.value(1).toInteger());
			}
			return ans;
		}
		else if (arr.value(0).isNumber() && arr.value(1).isNumber()
			&& arr.value(2).isNumber())
		{
			// rgb(a) color
			QColor ans(arr.value(0).toInteger(),
				arr.value(1).toInteger(), arr.value(2).toInteger());
			if (arr.value(3).isNumber())
			{
				ans.setAlpha(arr.value(3).toInteger());
			}
			return ans;
		}
	}
	else if (config.isObject())
	{
		const JsonObject obj = config.toObject();
		if (obj["name"].isString())
		{
			// named color
			QColor ans = obj["name"].toString();
			if (obj["a"].isNumber())
			{
				ans.setAlpha(obj["a"].toInteger());
			}
			else if (obj["alpha"].isNumber())
			{
				ans.setAlpha(obj["alpha"].toInteger());
			}
			return ans;
		}
		else
		{
			// potentially rgb(a) color
			QColor ans;
			// r
			if (obj["r"].isNumber())
			{
				ans.setRed(obj["r"].toInteger());
			}
			else if (obj["red"].isNumber())
			{
				ans.setRed(obj["red"].toInteger());
			}
			else
			{
				// no r
				return getColor("default");
			}
			// g
			if (obj["g"].isNumber())
			{
				ans.setGreen(obj["g"].toInteger());
			}
			else if (obj["green"].isNumber())
			{
				ans.setGreen(obj["green"].toInteger());
			}
			else
			{
				// no g
				return getColor("default");
			}
			// b
			if (obj["b"].isNumber())
			{
				ans.setBlue(obj["b"].toInteger());
			}
			else if (obj["blue"].isNumber())
			{
				ans.setBlue(obj["blue"].toInteger());
			}
			else
			{
				// no b
				return getColor("default");
			}
			// a (not required)
			if (obj["a"].isNumber())
			{
				ans.setAlpha(obj["a"].toInteger());
			}
			else if (obj["alpha"].isNumber())
			{
				ans.setAlpha(obj["alpha"].toInteger());
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
		if (obj["name"].isString())
		{
			font.setFamily(obj["name"].toString());
		}
		else if (obj["family"].isString())
		{
			font.setFamily(obj["family"].toString());
		}
		// size
		if (obj["size"].isNumber())
		{
			font.setPointSizeF(obj["size"].toDouble());
		}
		// weight
		if (obj["weight"].isNumber())
		{
			font.setWeight(obj["weight"].toInteger());
		}
		// italic
		if (obj["italic"].isBoolean())
		{
			font.setItalic(obj["italic"].toBoolean());
		}
		ans.setFont(font);
		// color or pen
		if (obj.contains("pen"))
		{
			ans.setPen(makePen(obj["pen"]));
		}
		else if (obj.contains("color"))
		{
			ans.setPen(makePen(obj["color"]));
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
		if (arr.value(0).isNumber() && arr.value(1).isNumber())
		{
			return QPointF(arr.value(0).toDouble(),
				arr.value(1).toDouble());
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
			ans.setTopLeft(makePoint(obj["top left"]));
		}
		else
		{
			ans.setLeft(0);
			ans.setTop(0);
		}
		// size or bottom right
		if (obj.contains("size"))
		{
			ans.setSize(makeSize(obj["size"]));
		}
		else if (obj.contains("bottom right"))
		{
			ans.setBottomRight(makePoint(obj["bottom right"]));
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
			ans.setLeft(arr.value(0).toDouble());
			ans.setTop(arr.value(1).toDouble());
			ans.setWidth(arr.value(2).toDouble());
			ans.setHeight(arr.value(3).toDouble());
		}
		// [<point>, <size>]
		else
		{
			ans.setTopLeft(makePoint(arr.value(0)));
			ans.setSize(makeSize(arr.value(1)));
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
	ans.setCenter(makePoint(obj["center"]));
	// central radius
	if (obj["radius"].isNumber())
	{
		ans.setRadius(obj["radius"].toDouble());
	}
	else if (obj["center radius"].isNumber())
	{
		ans.setRadius(obj["center radius"].toDouble());
	}
	// focal point
	if (obj.contains("focus"))
	{
		ans.setFocalPoint(makePoint(obj["focus"]));
	}
	else if (obj.contains("focal point"))
	{
		ans.setFocalPoint(makePoint(obj["focal point"]));
	}
	else
	{
		ans.setFocalPoint(ans.center());
	}
	// focal radius
	if (obj["focal radius"].isNumber())
	{
		ans.setFocalRadius(obj["focal radius"].toDouble());
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
		ans.setStart(makePoint(obj["start"]));
	}
	else if (obj.contains("starting point"))
	{
		ans.setStart(makePoint(obj["starting point"]));
	}
	else if (obj.contains("first stop"))
	{
		ans.setStart(makePoint(obj["first stop"]));
	}
	else
	{
		ans.setStart(0, 0);
	}
	// ending point
	if (obj.contains("end"))
	{
		ans.setFinalStop(makePoint(obj["end"]));
	}
	else if (obj.contains("finish"))
	{
		ans.setFinalStop(makePoint(obj["finish"]));
	}
	else if (obj.contains("final stop"))
	{
		ans.setFinalStop(makePoint(obj["final stop"]));
	}
	else if (obj.contains("ending point"))
	{
		ans.setFinalStop(makePoint(obj["ending point"]));
	}
	else if (obj.contains("finishing point"))
	{
		ans.setFinalStop(makePoint(obj["finishing point"]));
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
		ans.setCenter(makePoint(obj["center"]));
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
	if (obj["angle"].isNumber())
	{
		ans.setAngle(obj["angle"].toDouble());
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
	if (obj["type"].isNumber())
	{
		style = obj["type"].toInteger();
	}
	else if (obj["style"].isNumber())
	{
		style = obj["style"].toInteger();
	}
	else if (obj["brush style"].isNumber())
	{
		style = obj["brush style"].toInteger();
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
			return QBrush(makeColor(obj["color"]),
				(Qt::BrushStyle) style);
		case 15: // linear gradient
			return makeLinearGradient(config);
		case 17: // conical gradient
			return makeConicalGradient(config);
		case 16: // radial gradient
			return makeRadialGradient(config);
		case 24: // texture pattern
			if (obj["texture"].isString())
			{
				return QPixmap(obj["texture"].toString());
			}
			else if (obj["pattern"].isString())
			{
				return QPixmap(obj["pattern"].toString());
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
	if (obj["pen"].isNumber())
	{
		style = obj["pen"].toInteger();
	}
	else if (obj["pen style"].isNumber())
	{
		style = obj["pen style"].toInteger();
	}
	if (style < 0 || style > 6)
	{
		pen.setBrush(makeBrush(config));
		return pen;
	}
	pen.setStyle((Qt::PenStyle) style);
	// cap style
	style = 0;
	if (obj["cap"].isNumber())
	{
		style = obj["cap"].toInteger();
	}
	else if (obj["cap style"].isNumber())
	{
		style = obj["cap style"].toInteger();
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
	if (obj["join"].isNumber())
	{
		style = obj["join"].toInteger();
	}
	else if (obj["join style"].isNumber())
	{
		style = obj["join style"].toInteger();
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
	if (obj["width"].isNumber())
	{
		pen.setWidthF(obj["width"].toDouble());
	}
	else
	{
		pen.setWidthF(1.5);
	}
	// brush or color
	if (obj.contains("color"))
	{
		pen.setBrush(makeBrush(obj["color"]));
	}
	else if (obj.contains("brush"))
	{
		pen.setBrush(makeBrush(obj["brush"]));
	}
	else
	{
		pen.setBrush(getColor("default"));
	}
	// pattern for the line, if necessary
	if (pen.style() == Qt::CustomDashLine)
	{
		if (obj["pattern"].isArray())
		{
			QVector<qreal> pattern;
			const JsonArray arr = obj["pattern"].toArray();
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
