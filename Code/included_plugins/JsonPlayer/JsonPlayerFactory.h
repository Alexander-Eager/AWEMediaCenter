#ifndef JSON_PLAYER_FACTORY_H
#define JSON_PLAYER_FACTORY_H

// interface that this implements
#include "player/MediaPlayerFactory.h"

// superclass
#include <QObject>

// for plugin macros
#include <QtPlugin>

/**
 * \brief Creates JSON media players.
 **/
class JsonPlayerFactory : public QObject, public AWE::MediaPlayerFactory
{
	Q_OBJECT
	Q_INTERFACES(AWE::MediaPlayerFactory)
	Q_PLUGIN_METADATA(IID "com.awe.MediaPlayerFactory")

	public:
		/**
		 * \brief Creates a JSON media player with the
		 *			given settings.
		 *
		 * \param config The configuration file for
		 *					the player.
		 *
		 * \returns A new instance of the desired player,
		 *			or `nullptr` if the player could not
		 *			be created.
		 **/
		AWE::MediaPlayer* create(AWE::ConfigFile* config);
};

#endif // JSON_PLAYER_FACTORY_H