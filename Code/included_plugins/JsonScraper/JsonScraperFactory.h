#ifndef JSON_SCRAPER_FACTORY_H
#define JSON_SCRAPER_FACTORY_H

// interface that this implements
#include "scraper/MetadataScraperFactory.h"

// superclass
#include <QObject>

// for plugin macros
#include <QtPlugin>

/**
 * \brief Factory class that makes `JsonScraper`s.
 */
class JsonScraperFactory : public QObject, public AWE::MetadataScraperFactory
{
	Q_OBJECT
	Q_INTERFACES(AWE::MetadataScraperFactory)
	Q_PLUGIN_METADATA(IID "com.awe.MetadataScraperFactory")

	public:
		/**
		 * \brief Creates a JSON scraper with the
		 *			given settings.
		 *
		 * \param config The configuration file for
		 *					the scraper.
		 *
		 * \returns A new instance of the desired scraper,
		 *			or `nullptr` if the scraper could not
		 *			be created.
         */
		AWE::MetadataScraper* create(AWE::ConfigFile* config);
};

#endif // JSON_SCRAPER_FACTORY_H
