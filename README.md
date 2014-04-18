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

AWEMC is programmed using java and relies on [Qt](http://www.qt-project.org/), [cURL](http://curl.haxx.se/), and (eventually) [SDL](http://libsdl.org/). [JsonCpp](http://jsoncpp.sourceforge.net) is included in the source code.

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