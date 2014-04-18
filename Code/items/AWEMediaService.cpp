// header file
#include "AWEMediaService.h"

using namespace AWE;

MediaService::MediaService(const QDir& file) :
	MediaItem(file)
	{ }

ItemType MediaService::getItemType() const
{
	return SERVICE_TYPE;
}