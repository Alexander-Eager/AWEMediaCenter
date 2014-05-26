#ifndef MEDIA_SERVICE_FACTORY_H
#define MEDIA_SERVICE_FACTORY_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the class that this makes
#include "MediaService.h"

namespace AWE
{
	/**
	 * \brief Interface for making media services.
	 *
	 * This is the main interface that must be
	 * implemented in every service plugin, to
	 * create the desired service(s).
	 **/
	class AWEMC_BACKEND_LIBRARY MediaServiceFactory
	{
		public:
			virtual ~MediaServiceFactory() { }

			/**
			 * \brief Create a media service with the
			 *			given settings.
			 *
			 * \param config The configuration file for
			 *					the service.
			 *
			 * \returns A new instance of the desired service,
			 *			or `nullptr` if the service could not
			 *			be created.
			 **/
			virtual MediaService* create(ConfigFile* config) = 0;
	};
}

// this makes it available to QPluginLoader
Q_DECLARE_INTERFACE(AWE::MediaServiceFactory, "com.awe.MediaServiceFactory")

#endif // MEDIA_SERVICE_FACTORY_H