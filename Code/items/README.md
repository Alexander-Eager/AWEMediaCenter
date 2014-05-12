Media Items
===========

There are three kinds of media items:

 + `Folder`s, which contain other media items.
 + `MediaFile`s, which represent media to be played by a media player.
 + `MediaService`s, which represent standalone apps for media.

All media items have relevant metadata and a `"type"`, which is either `"folder"`, `"file"`, or `"service"`. The `metadata` tag is defined in the corresponding media type. Note that there is an item type and a media type, which are two separate things.

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

Unlike `Folder`s and `MediaFile`s, `MediaService`s are not found in the `root` folder. They are found inside the `services` folder. The JSON file found in `root` is very simple as follows:

	{
		"type": "service",

		"name": "service name"
	}

The `"name"` points to the specific service to place in that `Folder`.

Inside of the `services` folder, there are two sub folders: `json` and `plugin`. 

## External JSON Services

The `json` folder contains a set of JSON files that represent external applications to launch. Each of these JSON files look like this:

	{
		"name": "service name",

		"command": "terminal command to run"
	}

## Internal Plugin Services

The `plugin` folder contains a set of JSON files and associated dynamic libraries. In order to create the plugin you should implement the `MediaService` interface. The accompanying JSON file looks like this:

	{
		"name": "service name",

		"library": "dynamic library file"
	}

[media player]: <../player/README.md>
