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
			virtual const QString& getName() const = 0;
	};
}

#endif