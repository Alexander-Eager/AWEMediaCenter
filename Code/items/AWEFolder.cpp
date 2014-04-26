// header file
#include "AWEFolder.h"

// file reading
#include "libs/generic_file_reader/file_reader.h"
#include <QTextStream>
#include <QString>

using namespace AWE;

Folder::Folder(const QDir& folder,
		GlobalSettings* settings) :
	MediaItem(folder)
{
	// add the initial item
	settings->addItem(this);

	// get all of the children
	QDir root(folder);
	root.cdUp();
	QString r = root.absolutePath();
	for (uint i = 0; i < myData["items"].size(); ++ i)
	{
		QString str = r + "/" + myData["items"][i].asCString();
		QDir dir(QDir::cleanPath(str));
		MediaItem* toAdd = settings->getMediaItemByJSONFile(dir);
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