// header file
#include "AWEFolder.h"

// for settings
#include "AWEMC.h"

using namespace AWE;

Folder::Folder(QDir folder) :
	MediaItem(folder)
{
	// add the initial item
	AWEMC::settings()->addItem(this);

	// get all of the children
	QDir root(folder);
	root.cdUp();
	for (uint i = 0; i < getData()["items"].size(); ++ i)
	{
		QString str = root.absoluteFilePath(getData()["items"][i].asCString());
		QDir dir(QDir::cleanPath(str));
		MediaItem* toAdd = AWEMC::settings()->getMediaItemByJSONFile(dir);
		if (toAdd != nullptr)
		{
			myItems.append(toAdd);
		}
	}
}

Folder::~Folder()
{
	// nothing
}

ItemType Folder::getItemType() const
{
	return FOLDER_TYPE;
}

QList<MediaItem*> Folder::getItems()
{
	return myItems;
}

void Folder::addItem(MediaItem* item)
{
	myItems.append(item);
}