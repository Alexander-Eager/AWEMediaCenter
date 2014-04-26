#ifndef AWE_JSON_PLAYER_H
#define AWE_JSON_PLAYER_H

// superclass
#include "AWEMediaPlayer.h"

// global settings
#include "settings/AWEGlobalSettings.h"

namespace AWE
{
	/**
	 * \brief Represents an external media player
	 *			designed in a JSON file.
	 **/
	class JSONPlayer : public MediaPlayer
	{
		public:
			/**
			 * \brief Construct a media player from
			 *			the given JSON object.
			 *
			 * \param player The JSON object representing
			 *					this player.
			 **/
			JSONPlayer(Json::Value& player);

			/**
			 * \brief Play the given file.
			 *
			 * \param file The media file to play.
			 *
			 * \returns `true` if `file` played successfully,
			 *			`false` otherwise.
			 **/
			virtual int play(MediaFile* file);

			/**
			 * \brief Get the name of the player.
			 *
			 * \returns The name of the player.
			 **/
			virtual const QString& getName() const;

		private:
			/** \brief The name of the player. **/
			QString myName;
			/** \brief The program to be run. **/
			QString myProgram;
			/** \brief The arguments to be passed. **/
			QString myArguments;
	};
}

#endif