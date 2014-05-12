#ifndef AWE_MEDIA_PLAYER_H
#define AWE_MEDIA_PLAYER_H

#include <QString>

namespace AWE
{
	// forward declarations
	class MediaFile;
	
	/**
	 * \brief Represents an abstract media player's functions.
	 *
	 * \todo Make plugin interface.
	 **/
	class MediaPlayer
	{
		public:
			/**
			 * \brief Deconstructor.
			 **/
			virtual ~MediaPlayer() { }

			/**
			 * \brief Play the given file.
			 *
			 * \param file The media file to play.
			 *
			 * \returns `true` if `file` played successfully,
			 *			`false` otherwise.
			 **/
			virtual int play(MediaFile* file) = 0;

			/**
			 * \brief Get the name of the player.
			 *
			 * \returns The name of the player.
			 **/
			virtual QString getName() const = 0;

			/**
			 * \brief Determine if the given media file
			 *			can be played by this player.
			 *
			 * \param file The file to determine playability for.
			 *
			 * \returns `true` if this player can play `file`,
			 *			`false` otherwise.
			 **/
			virtual bool canPlay(MediaFile* file) = 0;
	};
}

#endif