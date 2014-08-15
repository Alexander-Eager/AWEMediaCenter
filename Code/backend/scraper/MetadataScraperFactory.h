#ifndef METADATA_SCRAPER_FACTORY_H
#define METADATA_SCRAPER_FACTORY_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the instance type to create
#include "MetadataScraper.h"

// for the creation of the type
#include "settings/ConfigFile.h"
#include <QString>

namespace AWE {
	/**
	 * \brief Interface describing a factory that
	 *			creates metadata scrapers.
	 *
	 * This is used for plugin-based scrapers. In
	 * general, only a specific metadata scraper is
	 * created. For example, a plugin could be created
	 * that scrapes movie metadata from an XBMC
	 * installation. It is also possible, however, that
	 * a factory can be made that makes multiple different
	 * scrapers. To use the XBMC example, a single plugin
	 * could be created that contains scrapers for movies,
	 * TV shows, and music from XBMC, and the correct
	 * scraper can be returned depending on the arguments.
	 * This is how AWEMC's JSON scrapers work: a plugin
	 * for JSON scrapers is provided, and the `create()`
	 * function returns the desired scraper.
     */
    class AWEMC_BACKEND_LIBRARY MetadataScraperFactory {
		public:
			virtual ~MetadataScraperFactory() { }
			
			/**
			 * \brief Create a metadata scraper with the
             *		  given settings.
			 *
			 * \param config The configuration file for
             *				 the scraper.
			 *
			 * \returns A new instance of the desired scraper,
			 *			or `nullptr` if the scraper could not
			 *			be created.
             */
			virtual MetadataScraper* create(ConfigFile* config) = 0;
	};
}

// this makes it available to QPluginLoader
Q_DECLARE_INTERFACE(AWE::MetadataScraperFactory, "com.awe.MetadataScraperFactory")

#endif // METADATA_SCRAPER_FACTORY_H
