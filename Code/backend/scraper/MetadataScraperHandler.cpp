// header file
#include "MetadataScraperHandler.h"

// class to act in place of
#include "MetadataScraper.h"

// factory class
#include "MetadataScraperFactory.h"
#include <QObject>

// plugin class
#include <QPluginLoader>

namespace AWE
{
	class MetadataScraperHandlerPrivate
	{
		public:
			QPluginLoader plugin;
			MetadataScraper* scraper;
			bool prepared;
	};
}

using namespace AWE;
using namespace JSON;

MetadataScraperHandler::MetadataScraperHandler(QString file)
	:	MetadataHolder(file),
		d(new MetadataScraperHandlerPrivate)
{
	d->scraper = nullptr;
	d->plugin.setFileName(getConfigFile()->getPathToConfigFile()
		.absoluteFilePath(getLocation()));
	d->prepared = false;
}

MetadataScraperHandler::~MetadataScraperHandler()
{
	deactivate();
	delete d;
}

bool MetadataScraperHandler::prepare()
{
	// try to load it
	if (!d->plugin.load())
	{
		return false;
	}
	// get the factory
	QObject* inst = d->plugin.instance();
	if (!inst)
	{
		d->plugin.unload();
		return false;
	}
	MetadataScraperFactory* factory 
		= qobject_cast<MetadataScraperFactory*>(inst);
	if (!factory)
	{
		d->plugin.unload();
		return false;
	}
	// get the scraper
	d->scraper = factory->create(getConfigFile());
	if (!d->scraper)
	{
		d->plugin.unload();
		return false;
	}
	if (!d->scraper->isValid())
	{
		delete d->scraper;
		d->scraper = nullptr;
		d->plugin.unload();
		return false;
	}
	d->prepared = true;
	return true;
}

bool MetadataScraperHandler::addMetadata(MetadataHolder* item, int flags)
{
	if (!isValid())
	{
		return false;
	}
	return d->scraper->addMetadata(item, flags);
}

QList<MediaItem*> MetadataScraperHandler::makeMediaItems(Folder* placeInMe,
	QString file, int flags)
{
	if (!isValid())
	{
		return QList<MediaItem*>();
	}
	return d->scraper->makeMediaItems(placeInMe, file, flags);
}

void MetadataScraperHandler::deactivate()
{
	if (!isValid())
	{
		return;
	}
	delete d->scraper;
	d->scraper = nullptr;
	d->plugin.unload();
	d->prepared = false;
}

bool MetadataScraperHandler::isValid() const
{
	return d->prepared;
}

bool MetadataScraperHandler::canBeUsedFor(MetadataHolder* item) const
{
	return getType() == item->getType();
}