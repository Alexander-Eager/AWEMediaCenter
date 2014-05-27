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
		connect(d->player, SIGNAL(closed()),
				this, SLOT(respondToClosed()));
		connect(d->player, SIGNAL(closed(MediaFile*)),
				this, SLOT(respondToClosed(MediaFile*)));
		connect(d->player, SIGNAL(startedPlaying()),
				this, SLOT(respondToPlaying()));
		connect(d->player, SIGNAL(startedPlaying(MediaFile*)),
				this, SLOT(respondToPlaying(MediaFile*)));
	}

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

void MediaPlayerHandler::respondToClosed()
{
	d->unload();
	emit closed();
}

void MediaPlayerHandler::respondToClosed(MediaFile* file)
{
	emit closed(file);
}

void MediaPlayerHandler::respondToPlaying()
{
	emit startedPlaying();
}

void MediaPlayerHandler::respondToPlaying(MediaFile* file)
{
	emit startedPlaying(file);
}

bool MediaPlayerHandlerPrivate::tryToLoad()
{
	// if it isn't valid, there is no point
	if (open)
	{
		return true;
	}
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