// header file
#include "AWEFolder.h"

// file reading
#include "libs/generic_file_reader/file_reader.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace AWE;
using namespace std;

Folder::Folder(const QDir& folder,
		GlobalSettings* settings) :
	MediaItem(folder)
{
	// get all of the children
	QDir root(folder);
	settings->addFolder(root.absolutePath().toStdString(), this);
	root.cdUp();
	string r = root.absolutePath().toStdString();
	for (unsigned int i = 0; i < myData["items"].size(); ++ i)
	{
		string str = r + "/" + myData["items"][i].asString();
		QDir dir(QDir::cleanPath(str.c_str()));
		MediaItem* toAdd = settings->getMediaItemByJSONFile(dir);
		if (toAdd != NULL)
		{
			myItems.push_back(toAdd);
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

vector<MediaItem*>& Folder::getItems()
{
	return myItems;
}