// header file
#include "items/AWEMediaFile.h"

// for global settings
#include "settings/AWEMC.h"

using namespace AWE;

MediaFile::MediaFile(QDir file) :
	MediaItem(file),
	myMediaFile(file)
{
	myMediaFile.cdUp();
	myMediaFile = myMediaFile.absoluteFilePath(getStringMember("metadata.location"));
	myDefaultPlayer = AWEMC::settings()->getPlayerByName(getStringMember("player"));
}

MediaFile::~MediaFile() { }

ItemType MediaFile::getItemType() const
{
	return FILE_TYPE;
}

QDir MediaFile::getMediaFile() const
{
	return myMediaFile;
}

MediaPlayer* MediaFile::getDefaultPlayer()
{
	return myDefaultPlayer;
}

int MediaFile::play()
{
	return myDefaultPlayer->play(this);
}