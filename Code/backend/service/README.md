Media Services
=============

Media services are standalone applications implemented in a plugin.

Media services hold metadata, so check out [the settings README][settings] for more information on the `"metadata"` tag. The "location" defined in said metadata is the plugin's location.

## Plugin Interfaces

Every media service plugin must implement the following interfaces:

 - `MediaServiceFactory`: constructs media services based on the JSON configuration file that they are being created from.
 - `MediaService`: opens an external program or provides window contents. At the moment, this interface is incomplete, as it does not include a way to paint in the main window.

[media files]: <../items/README.md>
[settings]: <../settings/README.md>