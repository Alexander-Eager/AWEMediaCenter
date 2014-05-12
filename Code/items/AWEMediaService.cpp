// header file
#include "AWEMediaService.h"

using namespace AWE;

MediaService::MediaService(QDir file) :
	MediaItem(file)
	{ }

ItemType MediaService::getItemType() const
{
	return SERVICE_TYPE;
}