#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

// for holding data
#include <QString>

// the superclass
#include "MediaItem.h"

// for playback
#include "player/MediaPlayerHandler.h"

namespace AWE
{
	// internal data
	class MediaFilePrivate;

	/**
	 * \brief Represents a media file.
	 *
	 * Holds the default player and all relevant metadata.
	 **/
	class MediaFile : public MediaItem
	{
		public:
			/**
			 * \brief Construct using the JSON file.
			 *
			 * \param file The path to the file.
			 **/
			MediaFile(QString file);

			/**
			 * \brief Construct from the given config file.
			 *
			 * \param file The config file.
			 **/
			MediaFile(ConfigFile* file);

			/** \brief Deconstructor. **/
			virtual ~MediaFile();

			/**
			 * \brief Get the absolute path to the media file.
			 *
			 * \returns The absolute path to of the media file.
			 **/
			virtual QString getMediaFile() const;

			/**
			 * \brief Get the default media player for this item.
			 *
			 * \returns The default media player for this item.
			 **/
			virtual MediaPlayerHandler* getDefaultPlayer();

			/**
			 * \brief Play this item with the default player.
			 *
			 * \returns `true` if playback was successful,
			 *			`false` if it was not.
			 **/
			virtual bool play();

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const;

		private:
			MediaFilePrivate* d;
	};
}

#endif // MEDIA_FILE_H