AWEMC's Settings
================

All configuration options for AWEMC are stored in JSON files. The JSON library used by AWEMC is [JsonDataTree][]

## Important Classes

There are 3 important classes related to AWEMC's settings:

 - `GlobalSettings`: Acts like a database for media player handlers, media service handlers, metadata scraper handlers, and skins.
 - `ConfigFile`: Represents a JSON configuration file. A `ConfigFile` object will automatically write out to file if the data in the config file was changed.
 - `MetadataHolder`: Represents anything that has metadata, which in AWEMC is pretty much everything.

### Metadata

Currently, "metadata" in AWEMC means the following:

 - Name: the name of the item.
 - Type: the type of item the metadata represents, e.g. `"Movie"`.
 - Description: a few sentences or a paragraph describing the item.
 - Location: what exactly this means depends on the item. For [media files][items], it represents the path to the file on disk. Folders, similarly, link to the folder on disk. Things like [media players][player], [media services][service], and [metadata scrapers][scraper], that are based on plugins, link to the plugin on disk. For [skins][skin]... well, it doesn't mean anything.
 - Icon images: a list of images that can represent an item, with one marked as default. Icon images can be "owned" by a specific item, in which case the image file is deleted if the icon is removed.
 - Fanart images: a list of images that can be used as a backdrop for an item, with one marked as default. Fanart images can be "owned" by a specific item, in which case the image file is deleted if the fanart is removed.
 - Details: a list of key-value pairs of details, e.g. "Release Date". Every detail has a name and a value. The name must always be a string, while the value can be a boolean, string, number, or array. When displayed, booleans become "Yes" or "No", and arrays become a comma-separated list of their contained values. Details are ordered.

[JsonDataTree]: <https://github.com/Alexander-Eager/JsonDataTree>
[items]: <../items/README.md>
[player]: <../player/README.md>
[scraper]: <../scraper/README.md>
[service]: <../service/README.md>
[skin]: <../skin/README.md>