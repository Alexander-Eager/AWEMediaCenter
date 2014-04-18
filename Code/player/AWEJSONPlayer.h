#ifndef AWE_JSON_PLAYER_H
#define AWE_JSON_PLAYER_H

// superclass
#include "AWEMediaPlayer.h"

// global settings
#include "settings/AWEGlobalSettings.h"

/**
 * \brief Represents an external media player
 *			designed in a JSON file.
 **/
class AWEJSONPlayer : public AWEMediaPlayer
{
	public:
		/**
		 * \brief Construct a media player from
		 *			the given JSON object.
		 *
		 * \param player The JSON object representing
		 *					this player.
		 **/
		AWEJSONPlayer(Json::Value& player);

		/**
		 * \brief Play the given file.
		 *
		 * \param file The media file to play.
		 *
		 * \returns `true` if `file` played successfully,
		 *			`false` otherwise.
		 **/
		virtual int play(AWEMediaFile* file);

		/**
		 * \brief Get the name of the player.
		 *
		 * \returns The name of the player.
		 **/
		virtual const std::string& getName() const;

	private:
		/** \brief The name of the player. **/
		std::string myName;
		/** \brief The program to be run. **/
		std::string myProgram;
		/** \brief The arguments to be passed. **/
		std::string myArguments;
};

#endif