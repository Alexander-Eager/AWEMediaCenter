Developer Information
=====================

AWEMC is programmed using C++ and relies on [Qt][], [cURL][], and (eventually) [SFML][]. [JsonCpp][] is included in the source code.

There are 7 central concepts you should understand:

 + [Media items](items/README.md) are organized in a folder structure using JSON files to hold metadata and such.
 + [Media players](player/README.md) play media files.
 + [Media services](items/README.md) are standalone applications, like a web browser, Netflix, or iTunes.
 + [Metadata scrapers](scraper/README.md) get relevant information and images for a media item.
 + [Media types](type_README.md) describe the default metadata values for a collection of items, like Movies or TV Shows.
 + [Folder generators](type_README.md) make a folder structure with organization based on things like Genre for a specific media type. They also use metadata scrapers to collect information about media items to be placed in the folder structure.
 + Skins describe the way the UI looks and give default images to files.

## Namespaces

There are a few namespaces you should know about:

 + `std` - Well, this one should be obvious.
 + `Json` - This is the namespace for [JsonCpp][].
 + `AWE` - All backend classes fall under this namespace.
 + `UI` - All user interface classes (i.e. windows and widgets) fall under this.
 + `TCOM` - My own little colored command line library included with the code for debugging (it will be removed later).

[Qt]: <http://www.qt-project.org/>
[cURL]: <http://curl.haxx.se/>
[SFML]: <http://www.sfml-dev.org/>
[JsonCpp]: <http://jsoncpp.sourceforge.net/>
