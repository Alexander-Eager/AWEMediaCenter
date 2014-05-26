#ifndef SKIN_H
#define SKIN_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "settings/MetadataHolder.h"

// data that is returned
#include "ColoredFont.h"
#include <QColor>
#include <QSizeF>
#include <QRectF>
#include <QPointF>
#include <QRadialGradient>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QBrush>
#include <JsonDataTree/Json.h>

namespace UI
{
	// internal data class
	class SkinPrivate;

	/**
	 * \brief Class representing a skin for AWEMC.
	 **/
	class AWEMC_BACKEND_LIBRARY Skin : public AWE::MetadataHolder
	{
		public:
			/**
			 * \brief Make a skin from the given file.
			 *
			 * \param file The configuration file.
			 **/
			Skin(QString file);

			/**
			 * \brief Destroy this object.
			 **/
			virtual ~Skin();

			/**
			 * \brief Get the font with the given name.
			 *
			 * If the font could not be found, this
			 * returns the `"normal"` font.
			 *
			 * \param font The font to retrieve.
			 *
			 * \returns The desired font.
			 **/
			virtual ColoredFont getFont(QString font) const;

			/**
			 * \brief Get the color with the given name.
			 *
			 * If the color could not be found, this
			 * returns the `"default"` color.
			 *
			 * \param color The color to retrieve.
			 *
			 * \returns The desired color.
			 **/
			virtual QColor getColor(QString color) const;

			/**
			 * \brief Get the configuration for a widget.
			 *
			 * \param name The name of the widget, which
			 *			is usually the class name.
			 *
			 * \returns The configuration for the widget,
			 *			or `JsonValue::Null` if the widget
			 *			does not have any configuration.
			 **/
			virtual JSON::JsonValue getWidgetConfig(QString name) const;

			/**
			 * \brief Make a color from a configuration.
			 *
			 * If the configuration is bad, this returns the color
			 * of the `"normal"` font.
			 *
			 * \param config The configuration for the color.
			 *
			 * \returns The desired color.
			 **/
			virtual QColor makeColor(const JSON::JsonValue config) const;

			/**
			 * \brief Make a colored font from a configuration.
			 *
			 * If the configuration is bad, this returns this
			 * returns the `"normal"` font.
			 *
			 * \param config The configuration for the colored font.
			 *
			 * \returns The desired font.
			 **/
			virtual ColoredFont makeFont(const JSON::JsonValue config) const;

			/**
			 * \brief Make an absolute point from a configuration.
			 *
			 * If the configuration is bad, this returns (0, 0).
			 *
			 * \param config The configuration for the point.
			 *
			 * \returns The desired point in absolute coordinates.
			 **/
			virtual QPointF makePoint(const JSON::JsonValue config) const;

			/**
			 * \brief Make a point from a relative configuration.
			 *
			 * If the configuration is bad, this returns (0, 0).
			 *
			 * \param config The configuration for the point.
			 * \param rect The rectangle to fit the point into.
			 *
			 * \returns The desired point inside of the given rectangle.
			 **/
			virtual QPointF makePoint(const JSON::JsonValue config,
				QRectF rect) const;

			/**
			 * \brief Make a size from a configuration.
			 *
			 * If this configuration is bad, this returns (0, 0).
			 *
			 * \param config The configuration for the size.
			 *
			 * \returns The desired size.
			 **/
			virtual QSizeF makeSize(const JSON::JsonValue config) const;

			/**
			 * \brief Make a size from a relative configuration.
			 *
			 * If the configuration is bad, this returns (0, 0).
			 *
			 * \param config The configuration for the size.
			 * \param size The size to fit this size into.
			 *
			 * \returns The desired size inside of the given size.
			 **/
			virtual QSizeF makeSize(const JSON::JsonValue config,
				QSizeF size) const;

			/**
			 * \brief Make an absolute rectangle from a configuration.
			 *
			 * If the configuration is bad, this returns `QRectF()`.
			 *
			 * \param config The configuration for the rectangle.
			 *
			 * \returns The desired rectangle in absolute coordinates.
			 **/
			virtual QRectF makeRect(const JSON::JsonValue config) const;

			/**
			 * \brief Make a rectangle from a relative configuration.
			 *
			 * If the configuration is bad, this returns (0, 0).
			 *
			 * \param config The configuration for the rectangle.
			 * \param rect The rectangle to fit the new rectangle into.
			 *
			 * \returns The desired rectangle inside of the given rectangle.
			 **/
			virtual QRectF makeRect(const JSON::JsonValue config,
				QRectF rect) const;

			/**
			 * \brief Make a radial gradient from a configuration.
			 *
			 * \param config The configuration for the gradient.
			 *
			 * \returns The desired gradient.
			 **/
			virtual QRadialGradient makeRadialGradient(const JSON::JsonValue config) const;

			/**
			 * \brief Make a linear gradient from a configuration.
			 *
			 * \param config The configuration for the gradient.
			 *
			 * \returns The desired gradient.
			 **/
			virtual QLinearGradient makeLinearGradient(const JSON::JsonValue config) const;

			/**
			 * \brief Make a conical gradient from a configuration.
			 *
			 * \param config The configuration for the gradient.
			 *
			 * \returns The desired gradient.
			 **/
			virtual QConicalGradient makeConicalGradient(const JSON::JsonValue config) const;

			/**
			 * \brief Make a brush from a configuration.
			 *
			 * The brush can be a gradient, a solid background color,
			 * a tiled pixmap, or nothing.
			 *
			 * \param config The configuration for the brush.
			 *
			 * \returns The desired brush.
			 **/
			virtual QBrush makeBrush(const JSON::JsonValue config) const;

			/**
			 * \brief Make a pen from a configuration.
			 *
			 * \param config The configuration for the pen.
			 *
			 * \returns The desired pen.
			 **/
			virtual QPen makePen(const JSON::JsonValue config) const;

		private:
			SkinPrivate* d;
	};
}

#endif // SKIN_H