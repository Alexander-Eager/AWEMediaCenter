Media Items
===========

There are three kinds of media items:

 + `Folder`s, which contain other media items.
 + `MediaFile`s, which represent media to be played by a media player.
 + `MediaServiceHandler`s, which represent standalone apps for media.

All media items have relevant metadata and a `"type"`, which is either `"folder"`, `"file"`, or `"service"`. All media items are `MetadataHolder`s, so check out [the settings README][settings] for more information on the `"metadata"` tag.

# Folders

`Folder`s are rather self explanatory: they contain other items. The JSON file structure is as follows:

	{
		"type": "folder",

		"metadata": {
			// metadata for the specific media type goes here
		},

		"items": [
			// list of relative paths to the contained items' JSON files
		]
	}

# Media Files

`MediaFile`s represent a file with a default [media player][], as follows:

	{
		"type": "file",

		"metadata": {
			// metadata for the specific media type goes here
		},

		"player": "player name",
	}

# Media Services

Unlike `Folder`s and `MediaFile`s, `MediaServiceHandler`s are not found in the `root` folder. They are found inside the `services` folder. The JSON file found in `root` is very simple as follows:

	{
		"type": "service",

		"name": "service name"
	}

The `"name"` points to the specific service to place in that `Folder`.

For more information on media services, see [the media services README][media service].

[media service]: <../service/README.md>
[settings]: <../settings/README.md>
