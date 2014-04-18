// header file
#include "AWEFolder.h"

// file reading
#include "libs/generic_file_reader/file_reader.h"
#include <string>
#include <sstream>
#include <iostream>

AWEFolder::AWEFolder(const QDir& folder,
		AWEGlobalSettings* settings) :
	AWEMediaItem(folder)
{
	// get all of the children
	QDir root(folder);
	settings->addFolder(root.absolutePath().toStdString(), this);
	root.cdUp();
	std::string r = root.absolutePath().toStdString();
	for (unsigned int i = 0; i < myData["items"].size(); ++ i)
	{
		std::string str = r + "/" + myData["items"][i].asString();
		QDir dir(QDir::cleanPath(str.c_str()));
		AWEMediaItem* toAdd = settings->getMediaItemByJSONFile(dir);
		if (toAdd != NULL)
		{
			myItems.push_back(toAdd);
		}
	}
}

AWEFolder::~AWEFolder()
{
	// nothing
}

ItemType AWEFolder::getItemType() const
{
	return FOLDER_TYPE;
}

std::vector<AWEMediaItem*>& AWEFolder::getItems()
{
	return myItems;
}