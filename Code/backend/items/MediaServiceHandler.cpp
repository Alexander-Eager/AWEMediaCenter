// header file
#include "MediaServiceHandler.h"

// class that this handles
#include "service/MediaService.h"

// for making the service
#include "service/MediaServiceFactory.h"
#include <QPluginLoader>

// for debug
#include <QDebug>

namespace AWE
{
	class MediaServiceHandlerPrivate
	{
		public:
			MediaServiceHandler* p;

			MediaService* service;
			QPluginLoader plugin;
			bool open;
			bool valid;

			bool tryToLoad();
			void unload();
	};
}

using namespace AWE;
using namespace JSON;

MediaServiceHandler::MediaServiceHandler(QString file)
	:	MediaItem(file),
		d(new MediaServiceHandlerPrivate)
{
	d->p = this;
	d->plugin.setFileName(getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation()));
	d->open = false;
	d->service = nullptr;

	// determine validity
	d->valid = true;
	if (!d->tryToLoad())
	{
		d->valid = false;
	}
	else
	{
		d->unload();
	}
}

MediaServiceHandler::MediaServiceHandler(ConfigFile* file)
	:	MediaItem(file),
		d(new MediaServiceHandlerPrivate)
{
	d->plugin.setFileName(getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation()));
	d->open = false;
	d->service = nullptr;

	// determine validity
	d->valid = true;
	if (!d->tryToLoad())
	{
		qWarning() << "MediaServiceHandler: Invalid service" << getName();
		d->valid = false;
	}
	else
	{
		d->unload();
	}
}

MediaServiceHandler::~MediaServiceHandler()
{
	d->unload();
	delete d;
}

bool MediaServiceHandler::isValid() const
{
	return d->valid;
}

bool MediaServiceHandler::open()
{
	if (d->open)
	{
		return true;
	}

	if (!d->tryToLoad())
	{
		return false;
	}

	connect(d->service, &MediaService::opened,
			this,	[this] ()
					{
						emit opened();
					});

	connect(d->service, &MediaService::closed,
			this,	[this] ()
					{
						d->unload();
						emit closed();
					}, Qt::QueuedConnection); // queued since it deletes

	return d->service->open();
}

bool MediaServiceHandler::close()
{
	if (!d->open)
	{
		return false;
	}

	return d->service->close();
}

MediaItem::ItemType MediaServiceHandler::getItemType() const
{
	return SERVICE;
}

bool MediaServiceHandlerPrivate::tryToLoad()
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
	MediaServiceFactory* factory 
		= qobject_cast<MediaServiceFactory*>(inst);
	if (!factory)
	{
		plugin.unload();
		return false;
	}
	// get the service
	service = factory->create(p->getConfigFile());
	if (!service)
	{
		plugin.unload();
		return false;
	}
	if (!service->isValid())
	{
		delete service;
		service = nullptr;
		plugin.unload();
		return false;
	}
	open = true;
	return true;
}

void MediaServiceHandlerPrivate::unload()
{
	if (!open)
	{
		return;
	}
	delete service;
	service = nullptr;
	plugin.unload();
	open = false;
}
