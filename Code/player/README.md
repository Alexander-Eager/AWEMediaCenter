Media Players
=============

Media players play [media files][], using either a terminal command or a plugin.

# External JSON Players

The JSON file for a media player looks like this:

	{
		"name": <player name>,

		"program": <program to run>,

		"args": <arguments to pass to the program with file references>,

		"filetypes": [
			<list of file extensions, excluding the ".">
		]
	}

The file references to `"args"` can be:

	{1} - the absolute path to the media file

# Internal Plugin Players

Internal media players must implement the `MediaPlayer` interface and fill out the accompanying JSON file:

	{
		"name": <player name>,

		"library": <dynamic library file>,

		<any other entries you want for configuration>
	}

[media files]: <../items/README.md>
