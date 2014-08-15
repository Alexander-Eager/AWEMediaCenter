#ifndef BACKENDFORWARDS_H
#define BACKENDFORWARDS_H

// JSON library forwards
#include <JsonDataTree/JsonForwards.h>

// Qt forwards
#include "QtForwards.h"

// backend forwards
namespace AWE {
    // items
    class Folder;
    class MediaFile;
    class MediaItem;
    class MediaServiceHandler;
    // player
    class MediaPlayer;
    class MediaPlayerFactory;
    class MediaPlayerHandler;
    // scraper
    class MetadataScraper;
    class MetadataScraperFactory;
    class MetadataScraperHandler;
    // service
    class MediaService;
    class MediaServiceFactory;
    // settings
    class AWEMC;
    class ConfigFile;
    class GlobalSettings;
    class MetadataHolder;
}

namespace UI {
    // skin
    class ColoredFont;
    class Skin;
    // ui
    class Configurable;
    class MainWindow;
    // contents
    class WindowContents;
    class FolderBrowser;
    // pane
    class FolderPane;
    class ImagePane;
    class InfoPane;
    class Pane;
    class TextPane;
    // widgets
    class TransparentScrollArea;
    // collection
    class ItemCollectionWidget;
    class ItemGridWidget;
    class ItemListWidget;
    // items
    class ImageItemWidget;
    class ItemWidget;
    class MediaItemWidget;
    class TextItemWidget;
}

#endif // BACKENDFORWARDS_H
