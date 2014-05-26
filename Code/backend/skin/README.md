Skins
===============

Skins in AWEMC contain configuration for fonts, colors, and widgets. Skins have metadata, so be sure to check out [the settings README][settings] for info on that.

## Terminology Notes

When this document says that a configuration is "invalid", it means that it is there, but it is not correct. If I had a point with the configuration `"taco"`, it would be considered an invalid point.

When this document says that a configuration "does not exist" or is "nonexistant", it means that it just isn't there. The configuration asks for a value, but there isn't one.

## Primitive Geometry Types

There are 3 main primitive geometry types: points, sizes, and rectangles. Note that coordinates are not what you learn about in math class, where *x* increases to the right and *y* increases upward. With computers, the top left corner is the origin (0, 0), and *x* increases moving right and *y* increases moving down.

### Points

Points are 2D and represented in the configuration file in the following ways:

 - `num`: the point (num, num).
 - `[x, y]`: the point (x, y).
 - Invalid configurations become (0, 0).

Sometimes, a point is not absolute but instead represents a point inside of a rectangle. These are called *relative points*. They are represented in the configuration file in the exact same way, but they are scaled and translated to fit inside of the rectangle they are meant for, such that (0, 0) is the top left corner and (1, 1) is the bottom right.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makePoint()`.

### Sizes

Sizes are 2D and represented in exactly the same way as points. Just like points, sizes can also be relative, where (0, 0) is nothing and (1, 1) is the entire rectangle.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeSize()`.

### Rectangles

Rectangles are defined by the top left point and their size. They are represented in a skin's configuration file in the following ways:

 - `[<point>, <size>]`: `<point>` is the top left point and `<size>` is the size of the rectangle.
 - `[x, y, w, h]`: the top left point is (x, y) and the size is (w, h).
 - 

		{
			"top left": <point>,
			"size": <size>
		}

 -

		{
			"top left": <point>,
			"bottom right": <point>
		}

 - Invalid or nonexistant points are assumed to be (0, 0), and invalid sizes also (0, 0).

Just like sizes and points, rectangles can also be relative to other rectangles. The top left point is scaled and translated for the rectangle, as is the size.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeRect()`.

## Colors

In AWEMC, skins specify a set of colors that are used. Some of these colors are:

 - `"default"`: the default color for text and pretty much everything else in the foreground.
 - `"transparent"`: a completely transparent color, or slightly tinted if the skin prefers.
 - `"default gradient 0"`: the first color to be displayed in a gradient.
 - `"default gradient 1"`: the second color to be displayed in a gradient.

There are several ways to define a color in a configuration file, all of which center around a few properties:

 - Name: a color name, which can be an encoded string with RGB values, or it could be one of [these names][SVG colors].
 - Red: the red value for the color, ranging from `0` to `255`. This will never accompany the Name attribute, and will always be accompanied by Green and Blue. Tags that represent Red are `"red"` and `"r"`.
 - Green: the green value for the color, ranging from `0` to `255`. This will never accompany the Name attribute, and will always be accompanied by Red and Blue. Tags that represent Green are `"green"` and `"g"`.
 - Blue: the blue value for the color, ranging from `0` to `255`. This will never accompany the Name attribute, and will always be accompanied by Green and Red. Tags that represent Blue are `"blue"` and `"b"`.
 - Alpha: the transparency for the color, ranging from `0` (completely transparent) to `255` (opaque). This is optional; if it is not there, it is assumed to be `255`. Tags that represent Alpha are `"alpha"` and `"a"`.

Every color will have either the Name property specified, or all three of Red, Green, and Blue. Alpha is optional.

Colors can be configured in the following ways:

 - `"name"`: gets the color from the skin's predefined colors, as described above.
 - `["name", alpha]`: creates the color with the given name (usually [one of these][SVG colors]) and alpha.
 - `[r, g, b, a]`: creates the color with the given red, green, blue, and alpha values.
 - An object, like so:

 		{
 			"name": "name of the color",
 			<Alpha tag>: alpha value
 		}

 - An object, like so:

 		{
 			<Red tag>: red value,
 			<Blue tag>: blue value,
 			<Green tag>: green value,
 			<Alpha tag>: alpha value
 		}

 - Invalid or nonexistant colors are assumed to be the `"default"` color for the skin.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeColor()` and `Skin::getColor()`.

## Fonts

Fonts in AWEMC are always accompanied by a color.

Fonts, like colors, are specified by each skin. Some of these fonts are:

 - `"normal"`: the font used for normal text.
 - `"big"`: a large font used in subtitles.
 - `"biggest"`: a very large font used in title bars.

Fonts have following properties:

 - Family: the look of the font (think Times New Roman vs. Helvetica). Tags that represent Family are `"name"` and `"family"`.
 - Size: the point size of the font. Only one tag represents size: `"size"`.
 - Weight: describes the varying levels of boldness of the font, ranging from `0` (barely there) to `100` (super thick). Only one tag represents weight: `"weight"`.
 - Italic: a boolean stating whether or not the font should be italicized. Only one tag represents italic: `"italic"`.
 - Color: the color of the text. Only one tag represents color: `"color"`.

Fonts can be configured in the following ways:

 - `"name"`: get the font from the skin's predefined collection.
 - An object, like so:

 		{
 			<Family tag>: "family name, like Helvetica",
 			<Size tag>: point size of the font,
 			<Weight tag>: weight of the font,
 			<Italic tag>: true or false,
 			<Color tag>: <color>
 		}

 - Invalid configurations become the `"normal"` font, which is then changed to fit the properties that were specified.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeFont()` and `Skin::getFont()`.

## Gradients

This is *very* advanced looking stuff that took me a while to figure out, but I finally did so. The best way to understand all of this is to mess around with it and see what happens.

### Common Properties

All gradients have these properties:

 - Spread: describes what happens to the points not impacted directly by the gradient. 
 	- `0` indicates that the color closest to that point is used. 
 	- `1` indicates that the gradient is reflected, creating a sort of ripple effect.
 	- `2` indicates that the gradient is repeated, which has a folding effect.
 - Coordinate mode: describes how all of the points and distances should be treated.
 	- `0` indicates that they are absolute pixel values.
 	- `1` indicates that they are relative to the object being drawn. So if a widget draws a rectangle in the bottom right corner of its area, all of the points lie inside of that rectangle.
 	- `2` indicates that they are relative to the widget being drawn. So even if a widget is drawing a rectangle in the bottom right corner of its area, the specified points are relative to the widget as a whole, not just the rectangle being drawn.
 - Colors: a set of pairs between numbers between `0` and `1` and colors describing the transition of the gradient. A gradient from black to white would have `0` paired with black and `1` with white, while a gradient from black to red to white would have `0.5` paired with red in addition to `0` with black and `1` with white. Associating `0.3` with red would cause the gradient to become red more quickly, and then take its time becoming white.

These properties are represented in the following way:

	{
		"spread": 0 or 1 or 2,
		"coordinate mode": 0 or 1 or 2,
		"colors": [
			[0 to 1, <color>],
			[0 to 1, <color>],
			// more pairs here
		],
		// properties specific to the type of gradient go here
	}

### Linear Gradients

Linear gradients change color uniformly from one point to another.

In addition to the properties common to all gradients, linear gradients have the following properties:

 - Starting point: the point the gradient starts at, specified by `"start"`, `"starting point"`, or
 `"first stop"`.
 - Ending point: the point the gradient ends at, specified by `"end"`, `"finish"`, `"ending point"`, `"finishing point"` or `"final stop"`.

These properties are represented in the following way:

	{
		// properties common to all gradients go here
		<Starting point tag>: <point>,
		<Ending point tag>: <point>
	}

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeLinearGradient()`.

### Radial Gradients

Radial gradients change color from a central point outward a certain distance.

In addition to the properties common to all gradients, radial gradients have the following properties:

 - Center: the center of the gradient, specified by `"center"`.
 - Center radius: the center radius of the gradient, specified by `"radius"` or `"center radius"`.
 - Focus: the focus of the gradient, specified by `"focus"` or `"focal point"`.
 - Focal radius: the focal radius of the gradient, specified by `"focal radius"`.

Only Center and Center radius are required.

These properties are represented in the following way:

	{
		// properties common to all gradients go here
		<Center>: <point>,
		<Center radius>: number,
		<Focus>: <point>,
		<Focal radius>: number
	}

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeRadialGradient()`.

### Conical Gradients

Conical gradients change color from an angle around a central point.

In addition to the properties common to all gradients, conical gradients have the following properties:

 - Center: the center of the gradient, specified by `"center"`.
 - Angle: the angle the gradient starts and ends at in degrees, specified by `"angle"`.

These properties are represented in the following way:

	{
		// properties common to all gradients go here
		<Center>: <point>,
		<Angle>: number
	}

Note that, because conical gradients cover the entire area that they are drawn in, the Spread does not actually matter.

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeConicalGradient()`.

## Brushes

Brushes describe the way an area is filled.

There is only one property common to all brushes: the Brush Style, which determines what kind of fill will be used. It is specified by the `"type"`, `"style"`, or `"brush style"` tag, and can take any of the following values:

 - `1` to `8`: Solid fill (`1`) to very sparse fill (`8`). This is accompanied by a `"color"` tag, which specifies the color. If it not there, it is assumed to be the skin's default color.
 - `9`: Horizontal lines, accompanied by a `"color"` tag.
 - `10`: Vertical lines, accompanied by a `"color"` tag.
 - `11`: Cross horizontal and vertical lines, accompanied by a `"color"` tag.
 - `12`: Backward diagonal lines, accompanied by a `"color"` tag.
 - `13`: Forward diagonal lines, accompanied by a `"color"` tag.
 - `14`: Crossing diagonal lines, accompanied by a `"color"` tag.
 - `15`: Linear gradient, accompanied by all of the tags describing a linear gradient.
 - `16`: Radial gradient, accompanied by all of the tags describing a radial gradient.
 - `17`: Conical gradient, accompanied by all of the tags describing a conical gradient.
 - `24`: Textured fill. The area is textured with an image taken from the file (absolue path) specified in the `"texture"` or `"pattern"` tags.
 - Anything else: no brush (no fill).

There are several ways to create a brush:

 - If the configuration does not exist or is `null`, it is assumed to be no brush (no fill).
 - If the configuration is not an object (i.e. not surrounded by `{}`), or does not contain any of the Brush Style tags, it is assumed to be a solid color, created according the the Color rules.
 - If the above conditions are not satisfied, it follows this syntax:

	 	{
	 		<Brush Style>: number,
	 		// accompanying tags go here
	 	}

If you are writing a widget class for AWEMC, the methods you will want to look at are named `Skin::makeBrush()`.

[SVG colors]: <http://www.w3.org/TR/SVG/types.html#ColorKeywords>