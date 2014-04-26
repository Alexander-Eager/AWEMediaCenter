#ifndef AWE_MEDIA_FILE_H
#define AWE_MEDIA_FILE_H

// for holding data
#include <QDir>

// for holding settings data
#include "libs/json/json.h"

// the superclass
#include "items/AWEMediaItem.h"

// for playback
#include "player/AWEMediaPlayer.h"

// settings
#include "settings/AWEGlobalSettings.h"

namespace AWE
{
	/**
	 * \brief Represents a media file.
	 *
	 * Holds the default player and all relevant metadata.
	 **/
	class MediaFile : public MediaItem
	{
		public:
			/**
			 * \brief Construct using the JSON file
			 *			and global settings.
			 *
			 * \param file The path to the file.
			 * \param settings The settings of AWEMC.
			 **/
			MediaFile(const QDir& file,
							GlobalSettings* settings);

			/** \brief Deconstructor. **/
			virtual ~MediaFile();

			/**
			 * \brief Get the absolute path to the media file.
			 *
			 * \returns The absolute path to of the media file.
			 **/
			virtual const QDir& getMediaFile() const;

			/**
			 * \brief Get the default media player for this item.
			 *
			 * \returns The default media player for this item.
			 **/
			virtual MediaPlayer* getDefaultPlayer();

			/**
			 * \brief Play this item with the default player.
			 *
			 * \returns `true` if playback was successful,
			 *			`false` if it was not.
			 **/
			virtual int play();

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const;

		private:
			/** \brief The path to the media file. **/
			QDir myMediaFile;

			/** \brief The default media player **/
			MediaPlayer* myDefaultPlayer;
	};
}

#endif