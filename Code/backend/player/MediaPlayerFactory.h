#ifndef MEDIA_PLAYER_FACTORY_H
#define MEDIA_PLAYER_FACTORY_H

// library macros
#include "macros/BackendLibraryMacros.h"

// the class this creates
#include "MediaPlayer.h"

namespace AWE {
	/**
	 * \brief A factory class that creates media players.
	 *
	 * This must be implemented for every plugin that
	 * provides media players.
     */
    class AWEMC_BACKEND_LIBRARY MediaPlayerFactory {
		public:
			virtual ~MediaPlayerFactory() { }

			/**
			 * \brief Create a media player with the
             *		  given settings.
			 *
			 * \param config The configuration file for
             *				 the player.
			 *
			 * \returns A new instance of the desired player,
			 *			or `nullptr` if the player could not
			 *			be created.
             */
			virtual MediaPlayer* create(ConfigFile* config) = 0;
	};
}

// this makes it available to QPluginLoader
Q_DECLARE_INTERFACE(AWE::MediaPlayerFactory, "com.awe.MediaPlayerFactory")

#endif // MEDIA_PLAYER_FACTORY_H
