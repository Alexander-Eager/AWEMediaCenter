// header file
#include "items/AWEMediaFile.h"

// for reading files
#include <sstream>
#include "libs/generic_file_reader/file_reader.h"

AWEMediaFile::AWEMediaFile(const QDir& file,
							AWEGlobalSettings* settings) :
	AWEMediaItem(file),
	myMediaFile(file)
{
	myMediaFile.cdUp();
	myMediaFile = myMediaFile.absolutePath() 
		+ "/" + getMember("metadata.location").asCString();
	myDefaultPlayer = settings->getPlayerByName(getMember("player").asString());
}

AWEMediaFile::~AWEMediaFile() { }

ItemType AWEMediaFile::getItemType() const
{
	return FILE_TYPE;
}

const QDir& AWEMediaFile::getMediaFile() const
{
	return myMediaFile;
}

AWEMediaPlayer* AWEMediaFile::getDefaultPlayer()
{
	return myDefaultPlayer;
}

int AWEMediaFile::play()
{
	return myDefaultPlayer->play(this);
}