#ifndef MEDIA_FILE_H
#define MEDIA_FILE_H

// library macros and forward declarations
#include "macros/BackendLibraryMacros.h"

// superclass
#include "MediaItem.h"

namespace AWE {
	// internal data
	class MediaFilePrivate;

	/**
	 * \brief Represents a media file.
	 *
	 * Holds the default player and all relevant metadata.
     */
    class AWEMC_BACKEND_LIBRARY MediaFile : public MediaItem {
		public:
			/**
			 * \brief Construct using the JSON file.
			 *
			 * \param file The path to the file.
             */
			MediaFile(QString file);

			/**
			 * \brief Construct from the given config file.
			 *
			 * \param file The config file.
             */
			MediaFile(ConfigFile* file);

            /**
             * \brief Deconstructor.
             */
			virtual ~MediaFile();

			/**
			 * \brief Get the absolute path to the media file.
			 *
			 * \returns The absolute path to of the media file.
             */
            auto getMediaFile() const -> QString;

			/**
			 * \brief Get the default media player for this item.
			 *
			 * \returns The default media player for this item.
             */
            auto getDefaultPlayer() -> MediaPlayerHandler*;

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
             */
            virtual auto getItemType() const -> ItemType;

        public slots:
            /**
             * \brief Play this item with the default player.
             *
             * \returns `true` if playback was successful,
             *			`false` if it was not.
             */
            bool play();

		private:
			MediaFilePrivate* d;
	};
}

#endif // MEDIA_FILE_H
