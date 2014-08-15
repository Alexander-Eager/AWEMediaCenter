// header file
#include "MediaItem.h"

// subclasses to create
#include "Folder.h"
#include "MediaItem.h"
#include "MediaServiceHandler.h"

// for getting services
#include "settings/AWEMC.h"

// for holding data
#include <QString>
#include <QPixmap>
#include <QList>

// for holding settings data
#include "settings/ConfigFile.h"

namespace AWE
{
	// internal data class that is, at the moment, used
	// only for a static member
	class MediaItemPrivate
	{
		public:
			static QHash<QString, MediaItem*> items;
	};
}

using namespace AWE;

QHash<QString, MediaItem*> MediaItemPrivate::items
	= QHash<QString, MediaItem*>();

MediaItem::MediaItem(QString file)
	:	MetadataHolder(file)
{
	if (getConfigFile()->isValid())
	{
		QString f = getConfigFile()->getPathToConfigFile()
			.absoluteFilePath(getConfigFile()->getConfigFileName());
		MediaItemPrivate::items[f] = this;
	}
}

MediaItem::MediaItem(ConfigFile* file)
	:	MetadataHolder(file)
{
	if (file && file->isValid())
	{
		QString f = file->getPathToConfigFile().absoluteFilePath(
			file->getConfigFileName());
		MediaItemPrivate::items[f] = this;
	}
}

MediaItem::~MediaItem()
{
	// removing could cause problems, since this is likely
	// called by deleteAllItems, but if this isn't called
	// by deleteAllItems, there could be errors by leaving
	// hanging pointer, so set it to nullptr to avoid errors.
	QString f = getConfigFile()->getPathToConfigFile().absoluteFilePath(
		getConfigFile()->getConfigFileName());
	MediaItemPrivate::items[f] = nullptr;
}

bool MediaItem::isFolder() const
{
	return getItemType() == FOLDER;
}

bool MediaItem::isFile() const
{
	return getItemType() == FILE;
}

bool MediaItem::isService() const
{
	return getItemType() == SERVICE;
}

MediaItem* MediaItem::makeItem(QString file)
{
	// check to see if the item is already there
	if (MediaItemPrivate::items.contains(QDir::cleanPath(file)))
	{
		return MediaItemPrivate::items[QDir::cleanPath(file)];
	}
	// get the data and check for validity
	ConfigFile* conf = new ConfigFile(file);
	if (!conf->isValid())
	{
		delete conf;
		return nullptr;
	}
	// determine what type of item it is and make it
	QString itemType = conf->getMember({"type"}).toString();
	if (itemType == "file")
	{
		return new MediaFile(conf);
	}
	else if (itemType == "folder")
	{
		return new Folder(conf);
	}
	else if (itemType == "service")
	{
		QString name = conf->getMember({"name"}).toString();
		delete conf;
		return AWEMC::settings()->getServiceHandler(name);
	}
	// the type is unrecognized, so cleanup and let go
	delete conf;
	return nullptr;
}

void MediaItem::deleteAllItems()
{
	for (auto i : MediaItemPrivate::items)
	{
		delete i;
	}
}
