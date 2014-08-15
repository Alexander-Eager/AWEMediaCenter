// header file
#include "Folder.h"

// for settings
#include "settings/AWEMC.h"

// for holding data
#include <QList>
#include <QString>

namespace AWE {
	class FolderPrivate
	{
		public:
			QList<MediaItem*> items;
	};
}

using namespace AWE;
using namespace JSON;

Folder::Folder(QString file)
	:	MediaItem(file),
		d(new FolderPrivate)
{
	// make the items array if necessary
	if (!getConfigFile()->getMember({"items"}).isArray())
	{
		getConfigFile()->addMember({"items"}, JsonValue::Array);
	}
	// get all of the items
	int i = 0;
	JsonArray arr = getConfigFile()->getMember({"items"}).toArray();
	while (i < arr.count())
	{
		MediaItem* temp = MediaItem::makeItem(getConfigFile()
			->getPathToConfigFile().absoluteFilePath(arr[i].toString()));
		if (temp)
		{
			// its a valid item, so add it
			d->items << temp;
			++ i;
		}
		else
		{
			// not a valid item, so remove it
			arr.removeAt(i);
			getConfigFile()->removeMember({"items", i});
		}
	}
}

Folder::Folder(ConfigFile* file)
	:	MediaItem(file),
		d(new FolderPrivate)
{
	// make the items array if necessary
	if (!getConfigFile()->getMember({"items"}).isArray())
	{
		getConfigFile()->addMember({"items"}, JsonValue::Array);
	}
	// get all of the items
	int i = 0;
	JsonArray arr = getConfigFile()->getMember({"items"}).toArray();
	while (i < arr.count())
	{
		MediaItem* temp = MediaItem::makeItem(getConfigFile()
			->getPathToConfigFile().absoluteFilePath(arr[i].toString()));
		if (temp)
		{
			// its a valid item, so add it
			d->items << temp;
			++ i;
		}
		else
		{
			// not a valid item, so remove it
			arr.removeAt(i);
			getConfigFile()->removeMember({"items", i});
		}
	}
}

Folder::~Folder()
{
	delete d;
}

MediaItem::ItemType Folder::getItemType() const
{
	return FOLDER;
}

QList<MediaItem*> Folder::getItems()
{
	return d->items;
}

void Folder::addItem(MediaItem* item)
{
	if (item && !d->items.contains(item))
	{
		d->items << item;
		emit itemAdded(item);
	}
}
