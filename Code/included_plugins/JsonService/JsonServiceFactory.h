#ifndef JSON_SERVICE_FACTORY_H
#define JSON_SERVICE_FACTORY_H

// interface that this implements
#include "service/MediaServiceFactory.h"

// superclass
#include <QObject>

// for plugin macros
#include <QtPlugin>

/**
 * \brief Creates JSON media services.
 **/
class JsonServiceFactory : public QObject, public AWE::MediaServiceFactory
{
	Q_OBJECT
	Q_INTERFACES(AWE::MediaServiceFactory)
	Q_PLUGIN_METADATA(IID "com.awe.MediaServiceFactory")

	public:
		/**
		 * \brief Creates a JSON media service with the
		 *			given settings.
		 *
		 * \param config The configuration file for
		 *					the service.
		 *
		 * \returns A new instance of the desired service,
		 *			or `nullptr` if the service could not
		 *			be created.
		 **/
		AWE::MediaService* create(AWE::ConfigFile* config);
};

#endif // JSON_SERVICE_FACTORY_H