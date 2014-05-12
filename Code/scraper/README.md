Metadata Scraping
==============

Explanation of the way in which AWEMC scrapes metadata for media files.

# The MetadataScraper interface

There are three steps to all metadata scraping:

1. Creating the scraper object: this happens at launch.
2. Preparing the scraper: this allocates memory to be used by the scraper and sets settings.
3. Scraping for data: the data is scraped using whatever method your class defines.
4. Deactivating the scraper: the objects allocated in step 2 are now deleted.

## How to: Create Internal Metadata Scrapers using Plugins

Essentially, you need to implement the `MetadataScraper` interface, which is designed to be used as a plugin. Read the [how-to for Qt plugins](http://qt-project.org/doc/qt-4.8/plugins-howto.html) to learn more. You'll need to use [JsonCpp][] to write the settings file out.

In addition to creating the plugin, you must make a JSON settings file. The only required entries in this file are:

	"name": <name of the scraper as it should appear to the user>,
	"plugin": <the plugin library file>

You can include other settings in this file if you like; it should automatically be configurable in the main settings pane.

## How To: Create External Metadata Scrapers using JSON Files

Before reading this how-to, here is some information you should know:

 + The general format of a JSON document (see <http://www.json.org/> for more details).
 + The kinds of metadata that AWEMC accepts (see [Media Types][] for details).
 + The way metadata is stored in a media file's JSON preference file (see [Media Items][] for details).
 + Qt regular expressions (see [QRegExp][] for more details).

Note that, although comments are not officially supported by the JSON file format, they are supported by AWEMC's JSON reader, [JsonCpp][]. Standard `// comment` lines work.

### Introduction to the idea behind JSON-based scrapers

The central theory behind these so-called *external scrapers* is that all metadata scrapers do
basically the same thing: retrieve data from formatted files. Sometimes these are XML files
(e.g. .nfo files from XBMC) and sometimes they are web pages (e.g. <http://www.themoviedb.org/>).
JSON-based scrapers in AWEMC make no distinction between documents hosted on the internet and locally;
they are all just text files that the scraper must read to get information about the media. Thus all you
have to do to get a piece of information from a file is:

1. Get the file to read from.
2. Look for a specific section of text in that file.
3. Take parts of that section of text and assign those values to metadata properties.

The implentation if these so-called *procedures* is based on regular expressions and backreferences. The type of regex used is [QRegExp][], while the format of the string where backreferences are placed is defined by the `fmt` parameter for the C++ Standard Library's [backref replacement function](http://www.cplusplus.com/reference/regex/match_replace/).

### A template for a scraper

Here is a template for a scraper:

	{
		// The user picks the scraper based on this name
		"name": <name of your scraper>,

		// This scraper is available to scrape metadata for this type of media item
		"type": <the type of media files>,

		// If a single file can have multiple items in it, set this to true.
		// The procedures below will be repeated for every file name match if true,
		// so make sure your filename regex is strict
		"multiple items per file": <true or false>

		// This helps you get information to use, like the name of the media item
		"filename": <regex to get backreferences from the media file path>,

		// If this type is hierarchical, the metadata should be inherited from the parent folder
		"inherited metadata": {
			<this type's property>: <parent type's property>
		}

		// List of procedures to run using the backreferences from "filename"
		"procedures": [
			{
				// Should this be repeated for every match or just one?
				"repeat": <true or false>,

				// Should the user be prompted to choose which match (or matches) to use?
				// Empty string means that the user should not be prompted
				"ask user": <string to prompt user with>,

				// The file to look in; backrefs are replaced
				"look in file": <formatted string with backrefs>,

				// The regex to search for in the above file; backrefs are replaced
				"for": <formatted regex with backrefs>,

				// Set a bunch of properties to backreferences from "for"
				"set properties": {
					<prop>: <value with backrefs>,
					<prop>: <value with backrefs>,
					// More properties...
				}

				// Run a list of sub-procedures using the backreferences from "for"
				"procedures": [...]
			},
			// More procedures...
		]

		// For properties that contain file paths or are arrays of file paths, sometimes 
		// you want to import the files.
		// This should always be defined to import every file (except the media file);
		// The user can select settings at the launching of the scraper to decide if
		// this should use links to the files or copy the files.
		// you don't get to choose the new names or the location; AWEMC does that for you
		"copy": [
			<prop with file-path value>,
			<prop with file-path value>,
			// More properties...	
		]

		// These are for files that should always be imported, e.g. internet files
		"force copy": [
			<prop with file-path value>
			// More properties...
		]
	}

Those of you who have read the [Media Types explanation][Media Types] know that
some metadata properties are actually objects that contain other metadata properties.
In order to access a property held inside of an object, you must use the `.` operator,
much like you would in C++. So to set the "default" property of the "icons" object, 
I would use:


	"icons.default": <value>


### Example scrapers

There are plenty of example scrapers for you to look at in the `scrapers/json` directory
in AWEMC's root folder. Specifically, `themoviedb.json` and `thetvdb.json` are included
with AWEMC and well commented, so if you need a place to start read up on those.

### Testing your scraper

If you use the debug build of AWEMC you can see if your scraper JSON is valid in the command
line output. You will also be able to see each individual property being set. You should test
your scraper thoroughly in this way before recommending it to others.

[Media Types]: <../type/README.md>
[JsonCpp]: <http://jsoncpp.sourceforge.net/>
[Media Items]: <../items/README.md>
[QRegExp]: <http://qt-project.org/doc/qt-5/qregexp.html>