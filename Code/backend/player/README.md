Media Players
=============

Media players play [media files][], using a plugin.

Media players hold metadata, so check out [the settings README][settings] for more information on the `"metadata"` tag. The "location" defined in said metadata is the plugin's location.

## Plugin Interfaces

Every media player plugin must implement the following interfaces:

 - `MediaPlayerFactory`: constructs media players based on the JSON configuration file that they are being created from.
 - `MediaPlayer`: takes `MediaFile` objects and either enqueues them for future playback or plays them immediately. This interface is currently incomplete, as it provides no way to paint directly to the main window.

[media files]: <../items/README.md>
[settings]: <../settings/README.md>