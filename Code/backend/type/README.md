Media Types
===========

The information for a media type is kept in a JSON file:

	{
		"type": <"folder" or "file">,

		"metadata": {
			"type": <type name>,
			"name": "",
			"location": "",

			"description": "",

			"icons": {
				"default": 0,
				"files": []
			},

			"fanarts": {
				"default": 0,
				"files": []
			},

			"details": {
				"_order": [<first detail>, <second detail>, ...],

				<first detail>: <default value>,
				<second detail>: <default value>,
				// more default details attributes
			}
		},

		"matching files": [
			<file expression you could use in terminal>,
			// more file expressions that also match
		]

		"contains": [
			// nested media types
		]
	}

# Metadata Default Values

Sometimes, a property cannot be given a value. In these instances, the value should be specified as the default value. Specified by `""` or `[]`.

A metadata scraper can decide to inherit a property from the parent folder, which is another kind of default property, but that is not explicity defined in type or file JSON configurations.

# Folder Structure Generation

## Explanation of File Organization

The `"contains"` tag indicates how the files should be organized by the folder generator. To better explain this, take TV episodes. The episodes should be organized by series and then season. So the `"contains"` property of the `"TV Series"` type would contain the `"TV Season"` type, which would contain the `"TV Episode"` type.

Then, when the folder is generated, the folder structure would look like this:

	All Items
	├── <name of series>
	│   ├── <season #>
	│   │   └── <Episodes>
	│   └── <season #>
	│       └── <Episodes>
	└── <name of series>
	    ├── <season #>
	    │   └── <Episodes>
	    └── <season #>
	        └── <Episodes>

You can instantiate the sub-type only if you so desire. You can instantiate the `"TV Episode"` type by itself. Because of this, you should list the properties from the hierarchy, like `"Season"` and `"Series"`, in the `"metadata.details"` tag.

## Root directories for the type

In addition to the `All Items` folder described above, there are also folders for every member of `"metadata.details"`. If, for example, there were a `"metadata.details.Genre"`, the following folder structure would be generated:

	Genre
	├── Genre Value 1
	│   └── Files with that value
	└── Genre Value 2
	    └── Files with that value

If the detail is a string, integer, or boolean, it is displayed directly as one of the values. If the detail is an array, each element in that array is a value. So if a movie has two directors, `Bob` and `Bill`, that movie appears under both `Bob` and `Bill`. `Bob` and `Bill` are separate folders under the `Director` folder. Also note that the actual property name is `Director(s)`, but the folder name is `Director`. If a section of text is contained in `()`, `{}`, or `[]` in a detail's name, that text along with the `()`, `{}`, or `[]`, is removed. In addition, other special characters that are not allowed in file names are removed individually. When defining a new type, you should name your detail properties carefully to avoid awkward folder names.

All generated folder structures have an `All Items` folder that lists all of the items.