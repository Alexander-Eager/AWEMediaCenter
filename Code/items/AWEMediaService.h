#ifndef AWE_MEDIA_SERVICE_H
#define AWE_MEDIA_SERVICE_H

// superclass
#include "AWEMediaItem.h"

namespace AWE
{
	/**
	 * \brief A media service, which is basically
	 *			an application with its own media
	 *			browser.
	 **/
	class MediaService : public MediaItem
	{
		public:
			/**
			 * \brief Construct from thie given JSON file.
			 *
			 * \param file The JSON file for this service.
			 **/
			MediaService(const QDir& file);

			/**
			 * \brief Open the media service.
			 *
			 * \returns The exit code of the application.
			 **/
			virtual int open() = 0;

			/**
			 * \brief Get the type of this item.
			 *
			 * \returns SERVICE_TYPE
			 **/
			virtual ItemType getItemType() const;
	};
}

#endif