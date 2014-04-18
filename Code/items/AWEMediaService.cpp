// header file
#include "AWEMediaService.h"

AWEMediaService::AWEMediaService(const QDir& file) :
	AWEMediaItem(file)
	{ }

ItemType AWEMediaService::getItemType() const
{
	return SERVICE_TYPE;
}