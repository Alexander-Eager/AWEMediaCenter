AWE Media Center
==============

Media center for OS X, Linux, and Windows based on generalized file launchers.

# Features

The idea behind AWE Media Center (AWEMC) is simple: using players, built in or otherwise, to launch media.  That sounds simple, but many media centers make the issue much more complicated than they need to.

 + Supports the creation of media players based on external executables and command line arguments.
 + Sometimes, a media player might be something other than a file launcher, e.g. an online video service. In such a case, a developer can release an extension of AWE Media Center to support that service. The service is launched much like a file.
 + Media files are organized via folders and collected from other places on the computer. A folder's contents can be displayed and sorted in different ways, e.g. grid view vs. list view.
 + You can set up a scraper (or use one of the included ones) in order to collect metadata about each file in a folder. This includes: icon images (could be multiple), fanart images, description, genre, producer, etc. There are built in scrapers for <http://thetvdb.com/>, <http://themoviedb.org/>, and <http://gamefaqs.com/>.

---------------

# Developer Information

The user interface for AWEMC is based on Qt (<http://www.qt-project.org/>).

## User Data

### Folder Organization

The folder organization the end user sees in the application does actually exist. It is under the `folders` folder in the root of the project. Each folder has an JSON file in it called `config.json` which specifies a few details such as:

 + Default media player for items in the folder (can be changed by sub folders)
 + Metadata for the folder (icons, description, etc.)
 + Default layout for the folder (the last layout view used)
 + Default sorting criteria (the last criteria used)
 + List of sub folders
 + List of items (which links to another JSON file)

An example of `config.json` for a movie folder would be:

```
{
	"metadata": {
		"name": "Movies",
		"location": "."

		"description": "Find movies by category.",

		"fanart": "fanart.png",
		"icons": {
			"front": "front.png",
			"default": "front"
		}
	},

	"folder": true,

	"player": "VLC",

	"layout": "AWEGridLayout",
	"sort": "name",

	"files": [
		{"file": "All Movies/config.json"},
		{"file": "Genre/config.json"},
		{"file": "Producer/config.json"},
		{"file": "Release Year/config.json"},
		{"file": "Up.json"},
		{"file": "Aladdin.json"},
		{"file": "Mulan.json"},
		{"file": "The Little Mermaid.json"}
	]
}
```

An example of a media file, `Up.json`:

```
{
	"metadata": {
		"name": "Up",
		"location": "../../../Users/Alex/Movies/Up.m4v"

		"description": "After a lifetime of dreaming of traveling the world, 78-year-old homebody Carl flies away on an unbelievable adventure with Russell, an 8-year-old Wilderness Explorer, unexpectedly in tow. Together, the unlikely pair embarks on a thrilling odyssey full of jungle beasts and rough terrain.",

		"Director(s)": "Pete Doctor, Bob Peterson",
		"Writer(s)": "Bob Peterson",
		"Cast": "Edward Asner, Christopher Plummer, Jordan Nagai, Bob Peterson",
		"Release Year": "2009",

		"fanart": "Up.png",
		"icons": {
			"front": "Up_front.png",
			"back": "Up_back.png",
			"left": "Up_left.png",
			"right": "Up_right.png",
			"top": "Up_top.png",
			"bottom": "Up_bottom.png",
			"default": "front"
		}
	},

	"folder": false,

	"player": "QuickTime"
}
```

Important things to note about AWEMC's folder organization JSON files:

 + Everything uses relative paths. This is so that, if a user wants to use the same setup on multiple computers, he can use a network to link to the root folder without worrying about absolute paths ruining everything. While this makes the program more flexible, it does make the json files pretty ugly (lots of `..`s used to link to files/folders). This also makes it so the same file/folder can be linked to by multiple folders (like a movie under both `Genre/Comedy` and `Release Year/2001`).
 + Sub folders and files are considered the same (link to the sub folder's `config.json` file vs. `file_name.json`).
 + Each file must have the `metadata` tag, along with the sub-tags `name`, `description`, `fanart`, `location`, and `icons`. `icons` must have the sub-tags `front` and `default`, but the others are optional. If there are more icons supplied, the user will be able to change which one is shown (which is stored in the `default` tag). This `metadata` universality is why folders and files are considered the same thing: all the data you need to display an item can be found whether it is a file or a folder.
 + In addition to the `metadata` tag, the `folder` tag is also necessary to indicate if this is a folder or a media file.
 + It is not actually necessary to have real folders for each folder in the user interface. The default implementation does have physical folders, but the same thing could be achieved by using `folder_name.json` files or the like instead of `folder/config.json`. It is good practice to make the folders.
 + The `player` tag overrules all other precedents for playing that file. See "External Media Players" below for more information.
 + The `sort` tag indicates which `metadata` tag should be used for sorting. Usually this is `name` or `Release Year` or the like. `icons` and `location` are excluded from the user interface, so they should not be values for `sort`. Some `metadata` tags, like `Producer(s)`, are not included for every item. Items that do not specify that tag are given the minimum value (empty string).
 + Although things like `Release Year` can be represented with numbers, they should still be strings for consistency among all  `metadata` tags.
 + The player variable should designate either an internal player by name (which always begins with `Default`) or by the `name` tag of an external player (see below).

### External Media Players

External media players are launched through the command line. The configuration for external media players comes from mor JSON files, stored in the `ExternalPlayers` directory in the root directory of AWEMC. Take `VLC.json` on an OS X machine, for example:

```
{
	"name": "VLC",
	"location": "/Applications/VLC.app/Contents/MacOS/VLC",
	"arguments": " -vvv {1}",
	"filetypes": ["avi", "iso", "mpg", "mpeg", "mp3"]
}
```

A few things to note about external player JSONs:

 + Unlike media files and folders, the `location` of media players should be an absolute path to the executable.
 + Note that on OS X, the `location` is inside of the `*.app` folder (it is always `*.app/Contents/MacOS/something`).
 + The command executed is just the location followed by a space followed by the arguments. Thus if the executable is in the PATH variable you do not need to supply an actual location.
 + Another tag not listed here is `DVD`. It is a `bool` to determine if the player should be used to play discs in the CD/DVD/BD drive.

The `{1}` in the `arguments` string is one of a few strings related to the file name:

 + `{0}` – the `location` value (e.g. `/Applications/VLC.app/Contents/MacOS/VLC`)
 + `{1}` – the absolute file path (e.g. `/files/video.avi`)
 + `{2}` – just the path, including trailing `/` or `\` (e.g. `/files/`)
 + `{3}` – just the file name (e.g. `video.avi`)
 + `{4}` – the file name with no extension (e.g. `video`)
 + `{5}` – the extension, including preceding `.` (e.g. `.avi`)

The `filetypes` array indicates which types of files should be opened with this player by default. The order of precedence for which player to use is:

 + `player` in the individual media file JSON
 + `player` in the folder containing the media file
 + The external player with that extension listed in `filetypes`
 + `player` in the folder of the folder containing the media file (and upward through the path)
 + Any internal player that is defined to play that file type
 + The `Default Program` player (which uses the operating system's default program)

## Included Media Players

 + `Default Program` – opens the file in the default program as specified by the operating system. On Windows, it executes `file_name`, on OS X `open file_name`, and on Linux `xdg-open file_name`. Note that this is actually an external media player, but it still has the `Default` prefix since it comes with AWEMC.
 + `Default Video Player` – the default internal video player for most video formats.
 + `Default Audio Player` – the default internal audio player for most audio formats.
 + `Default DVD Player` – the default internal player for discs (in the CD/DVD/BD drive).
 + `Default Web Browser` – the default web browser. On Windows, this is Internet Explorer, on OS X Safari and on Linux Firefox (so you should install it or create your own external media player for the desired file types).

Note that one quick way to change the default video player is to make your own external player also called `DefaultVideoPlayer`. So if you would rather have VLC play all of your files, just rename the above `VLC.json` to `DefaultVideoPlayer.json`. Any file that specifically asks for the default video player will thus get VLC. 

## Documentation

There are 8 classes that you should understand:

 + `AWEItem` – an item displayed in an `AWEFolder`. This could be an `AWEMediaFile`, `AWEMediaService`, or `AWEFolder`.
 + `AWEFolder` – a folder that contains `AWEItem`s.
 + `AWEMediaFile` – a file that can be launched by a specified `AWEMediaPlayer`.
 + `AWEMediaPlayer` - represents an external or internal media player, like a video player, audio player, DVD player, etc.
 + `AWEInternalMediaPlayer` – an `AWEMediaPlayer` that does not open a separate application (i.e. an extension of AWEMC)
 + `AWEExternalMediaPlayer` – an `AWEMediaPlayer` that does open a separate application, e.g. VLC.
 + `AWEMediaService` – an interface for an external media player that manages its own files (like, say, iTunes or Netflix).
 + `AWEScraper` – scrapes metadata for `AWEMediaFile`s (where that metadata comes from depends on the scraper).

As you can probably see, all classes built into AWEMC should be prefixed by "AWE".

More detailed documentation can be found under the `Documentation` folder in this repository. Documentation is generated with Doxygen, so comment your header files appropriately.