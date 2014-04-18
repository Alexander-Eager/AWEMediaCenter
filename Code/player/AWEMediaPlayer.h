#ifndef AWE_MEDIA_PLAYER_H
#define AWE_MEDIA_PLAYER_H

#include <string>

// forward declarations
class AWEMediaFile;

/**
 * \brief Represents an abstract media player's functions.
 *
 * \todo Make plugin interface.
 **/
class AWEMediaPlayer
{
	public:
		/**
		 * \brief Play the given file.
		 *
		 * \param file The media file to play.
		 *
		 * \returns `true` if `file` played successfully,
		 *			`false` otherwise.
		 **/
		virtual int play(AWEMediaFile* file) = 0;

		/**
		 * \brief Get the name of the player.
		 *
		 * \returns The name of the player.
		 **/
		virtual const std::string& getName() const = 0;
};

#endif