// header file
#include "MediaPlayerHandler.h"

// the class that this handles
#include "MediaPlayer.h"

// for loading the plugin and creating the player
#include "MediaPlayerFactory.h"
#include <QPluginLoader>

// for debug
#include <QDebug>

namespace AWE
{
	class MediaPlayerHandlerPrivate
	{
		public:
			MediaPlayerHandler* p;

			QPluginLoader plugin;
			MediaPlayer* player;
			bool open;
			bool valid;

			bool tryToLoad();
			void unload();
	};
}

using namespace AWE;
using namespace JSON;

MediaPlayerHandler::MediaPlayerHandler(QString file)
	:	MetadataHolder(file),
		d(new MediaPlayerHandlerPrivate)
{
	d->p = this;
	d->player = nullptr;
	d->plugin.setFileName(getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation()));
	d->open = false;

	// determine validity
	d->valid = true;
	if (!d->tryToLoad())
	{
		qWarning() << "MediaPlayerHandler: Invalid player" << getName();
		d->valid = false;
	}
	else
	{
		d->unload();
	}
}

MediaPlayerHandler::~MediaPlayerHandler()
{
	d->unload();
	delete d;
}

bool MediaPlayerHandler::canPlay(MediaFile* file) const
{
	if (!d->valid)
	{
		return false;
	}
	// load if necessary
	bool shouldClose = !d->open;
	if (shouldClose)
	{
		if (!d->tryToLoad())
		{
			return false;
		}
	}

	// check to see if it can play
	bool ans = d->player->canPlay(file);

	// unload if necessary
	if (shouldClose)
	{
		d->unload();
	}

	// return the player's ans
	return ans;
}

bool MediaPlayerHandler::isPlaying() const
{
	return d->open && d->player->isPlaying();
}

bool MediaPlayerHandler::isPlaying(MediaFile* file) const
{
	return d->open && d->player->isPlaying(file);
}

bool MediaPlayerHandler::isValid() const
{
	return d->valid;
}

bool MediaPlayerHandler::play(MediaFile* file)
{
	if (!d->open)
	{
		if (!d->tryToLoad())
		{
			return false;
		}
		// connect close/open signals to respective slots
		connect(d->player, static_cast<void (MediaPlayer::*)()>
							(&MediaPlayer::closed),
				this,	[this] ()
						{
							d->unload();
							emit closed();
						}, Qt::QueuedConnection); // queued since it deletes

		connect(d->player, static_cast<void (MediaPlayer::*)(MediaFile*)>
							(&MediaPlayer::closed),
				this,	[this] (MediaFile* file)
						{
							emit closed(file);
						} );

		connect(d->player, static_cast<void (MediaPlayer::*)()>
							(&MediaPlayer::startedPlaying),
				this,	[this] ()
						{
							emit startedPlaying();
						});

		connect(d->player, static_cast<void (MediaPlayer::*)(MediaFile*)>
							(&MediaPlayer::startedPlaying),
				this,	[this] (MediaFile* file)
						{
							emit startedPlaying(file);
						} );
	}
	d->open = true;

	return d->player->play(file);
}

bool MediaPlayerHandler::close()
{
	if (!d->open)
	{
		return false;
	}

	return d->player->close();
}

bool MediaPlayerHandler::close(MediaFile* file)
{
	if (!d->open)
	{
		return false;
	}

	return d->player->close(file);
}

bool MediaPlayerHandlerPrivate::tryToLoad()
{
	if (open)
	{
		return true;
	}
	// if it isn't valid, there is no point
	if (!p->isValid())
	{
		return false;
	}
	// try to load it
	if (!plugin.load())
	{
		return false;
	}
	// get the factory
	QObject* inst = plugin.instance();
	if (!inst)
	{
		plugin.unload();
		return false;
	}
	MediaPlayerFactory* factory 
		= qobject_cast<MediaPlayerFactory*>(inst);
	if (!factory)
	{
		plugin.unload();
		return false;
	}
	// get the player
	player = factory->create(p->getConfigFile());
	if (!player)
	{
		plugin.unload();
		return false;
	}
	if (!player->isValid())
	{
		delete player;
		player = nullptr;
		plugin.unload();
		return false;
	}
	open = true;
	return true;
}

void MediaPlayerHandlerPrivate::unload()
{
	if (!open)
	{
		return;
	}
	delete player;
	player = nullptr;
	plugin.unload();
	open = false;
}