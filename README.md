AWE Media Center
==============

Media center for OS X, Linux, and Windows based on generalized file launchers.

# Features

The idea behind AWE Media Center is simple: using players, built in or otherwise, to launch media.  That sounds simple, but many media centers make the issue much more complicated than they need to.

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
		},
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
		},
	}

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
 + The `player` tag overrules the containing folder's `player` tag. If it is not supplied, the containing folder's `player` is used.
 + The `sort` tag indicates which `metadata` tag should be used for sorting. Usually this is `name` or `Release Year` or the like. `icons` and `location` are excluded from the user interface, so they should not be values for `sort`. Some `metadata` tags, like `Producer(s)`, are not included for every item. Items that do not specify that tag are given the minimum value (empty string).
 + Although things like `Release Year` can be represented with numbers, they should still be strings for consistency among all  `metadata` tags.

### External Media Players

TODO

## Documentation

There are 8 classes that you should understand:

 + `AWEItem` – an item displayed in a `AWEFolder`. This could be an `AWEMediaFile`, `AWEMediaService`, or `AWEFolder`.
 + `AWEFolder` – a folder that contains `AWEItem`s.
 + `AWEMediaFile` – a file that can be launched by a specified `AWEMediaPlayer`.
 + `AWEMediaPlayer` - represents an external or internal media player, like a video player, audio player, DVD player, etc.
 + `AWEInternalMediaPlayer` – an `AWEMediaPlayer` that does not open a separate application (i.e. an extension of AWEMC)
 + `AWEExternalMediaPlayer` – an `AWEMediaPlayer` that does open a separate application, e.g. VLC.
 + `AWEMediaService` – an interface for an external media player that manages its own files (like, say, iTunes or Netflix).
 + `AWEScraper` – scrapes metadata for `AWEMediaFile`s (where that metadata comes from depends on the scraper).

As you can probably see, all classes built into AWEMC should be prefixed by "AWE".

More detailed documentation can be found under the `Documentation` folder in this repository.