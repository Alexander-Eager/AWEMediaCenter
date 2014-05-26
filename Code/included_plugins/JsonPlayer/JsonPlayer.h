#ifndef AWE_JSON_PLAYER_H
#define AWE_JSON_PLAYER_H

// superclass
#include "AWEMediaPlayer.h"

// global settings
#include "settings/AWEGlobalSettings.h"

// data
#include <QString>
#include <QStringList>

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
			virtual QString getName() const;

			/**
			 * \brief Determine if the given media file
			 *			can be played by this player.
			 *
			 * For JSON based players, this is determined
			 * using the file extension and the `"filetypes"` tag.
			 *
			 * \param file The file to determine playability for.
			 *
			 * \returns `true` if this player can play `file`,
			 *			`false` otherwise.
			 **/
			virtual bool canPlay(MediaFile* file);

		private:
			/** \brief The name of the player. **/
			QString myName;
			/** \brief The program to be run. **/
			QString myProgram;
			/** \brief The arguments to be passed. **/
			QString myArguments;
			/** \brief The possible file types that can be played. **/
			QStringList myFileTypes;
	};
}

#endif