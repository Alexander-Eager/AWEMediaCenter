// header file
#include "items/AWEMediaFile.h"

// for reading files
#include <sstream>
#include "libs/generic_file_reader/file_reader.h"

using namespace AWE;

MediaFile::MediaFile(const QDir& file,
							GlobalSettings* settings) :
	MediaItem(file),
	myMediaFile(file)
{
	myMediaFile.cdUp();
	myMediaFile = myMediaFile.absolutePath() 
		+ "/" + getMember("metadata.location").asCString();
	myDefaultPlayer = settings->getPlayerByName(getMember("player").asString());
}

MediaFile::~MediaFile() { }

ItemType MediaFile::getItemType() const
{
	return FILE_TYPE;
}

const QDir& MediaFile::getMediaFile() const
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