Media Types
===========

The information for a media type is kept in a JSON file:

	{
		"metadata": {
			"type": "type name",
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
			}

			"details": {
				"_order": ["first detail", "second", ...],

				"first detail": <default value>,
				"second": <default value>,
				// more default details attributes
			}

			// other default metadata attributes
		}

		"organize by": [
			{ "prop": "property 1", "show": true or false },
			{ "prop": "property 2", "show": true or false },
			// more properties
		]
	}

The `"organize by"` tag indicates how the files should be organized by the folder generator. To better explain this, take TV episodes. The episodes should be organized by series and then season. So the `"organize by"` property would be:

	[
		{ "prop": "Series", "show": false },
		{ "prop": "Season", "show": true  },
	]

Then, when the folder is generated, the folder structure would look like this:

	All Items
	├── <name of series>
	│   ├── Season <#>
	│   │   └── <Episodes>
	│   └── Season <#>
	│       └── <Episodes>
	└── <name of series>
	    ├── Season <#>
	    │   └── <Episodes>
	    └── Season <#>
	        └── <Episodes>

So `"prop"` names the details property to use while `"show"` decides if the property name, followed by a space, should be prefixed to the value. In the above example, the series names should not be prefixed by "Series ", while the season numbers should be prefixed by "Season ".

`"prop"` can be a string, number, or boolean, but it cannot be an array or an object.

# Folder Structure Generation

In addition to the `All Items` folder described above, there are also folders for every member of `"metadata.details"` not indicated in `"organize by"`. If, for example, there were a `"metadata.details.Genre"` tag that was not indicated in `"organize by"`, the following folder structure would be generated:

	Genre
	├── Genre Value 1
	│   └── Files with that value
	└── Genre Value 2
	    └── Files with that value

If the detail is a string, integer, or boolean, it is displayed directly as one of the values. If the detail is an array, each element in that array is a value. So if a movie has two directors, Bob and Bill, that movie appears under both Bob and Bill. Bob and Bill are separate folders under the Director(s) folder.

All generated folder structures have an All Items folder that lists all of the items.