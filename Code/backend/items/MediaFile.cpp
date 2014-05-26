// header file
#include "items/MediaFile.h"

// for global settings
#include "settings/AWEMC.h"

namespace AWE
{
	class MediaFilePrivate
	{
		public:
			MediaPlayerHandler* defaultPlayer;
			QString mediaFile;
	};
}

using namespace AWE;
using namespace JSON;

MediaFile::MediaFile(QString file)
	:	MediaItem(file),
		d(new MediaFilePrivate)
{
	// get the media file path (absolute)
	d->mediaFile = getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation());

	// get the default player
	if (!getConfigFile()->getMember({"player"}).isString())
	{
		getConfigFile()->addMember({"player"}, JsonValue::String);
	}
	d->defaultPlayer = AWEMC::settings()->getPlayerHandler(
		getConfigFile()->getMember({"player"}).toString());
}

MediaFile::MediaFile(ConfigFile* file)
	:	MediaItem(file),
		d(new MediaFilePrivate)
{
	d->mediaFile = getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation());
	d->defaultPlayer = AWEMC::settings()->getPlayerHandler(
		getConfigFile()->getMember({"player"}).toString());
}

MediaFile::~MediaFile()
{
	delete d;
}

MediaFile::ItemType MediaFile::getItemType() const
{
	return FILE;
}

QString MediaFile::getMediaFile() const
{
	return d->mediaFile;
}

MediaPlayerHandler* MediaFile::getDefaultPlayer()
{
	return d->defaultPlayer;
}

bool MediaFile::play()
{
	return getDefaultPlayer()->play(this);
}