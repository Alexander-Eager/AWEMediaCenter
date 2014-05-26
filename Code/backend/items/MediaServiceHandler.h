#ifndef MEDIA_SERVICE_HANDLER_H
#define MEDIA_SERVICE_HANDLER_H

// superclass
#include "MediaItem.h"

namespace AWE
{
	// internal data class
	class MediaServiceHandlerPrivate;

	/**
	 * \brief Handles a `MediaService` object.
	 *
	 * This loads and unloads the plugin to
	 * save memory space.
	 **/
	class MediaServiceHandler : public MediaItem
	{
		Q_OBJECT
		
		public:
			/**
			 * \brief Construct from the given JSON file.
			 *
			 * \param file The JSON file for this service.
			 **/
			MediaServiceHandler(QString file);

			/**
			 * \brief Construct from the given JSON file.
			 *
			 * \param file The JSON file for this service.
			 **/
			MediaServiceHandler(ConfigFile* file);

			virtual ~MediaServiceHandler();

			/**
			 * \brief Determine if this service is valid.
			 *
			 * \returns `true` if the service is valid,
			 *			`false` otherwise.
			 **/
			virtual bool isValid() const;

			/**
			 * \brief Get the type of this item.
			 *
			 * \returns SERVICE
			 **/
			virtual ItemType getItemType() const;

		public slots:
			/**
			 * \brief Open the media service.
			 *
			 * \returns `true` if the launch was successful,
			 *			`false` otherwise.
			 **/
			virtual bool open();

			/**
			 * \brief Close the media service.
			 *
			 * \returns `true` if the application closed
			 *			without error, `false` otherwise.
			 **/
			virtual bool close();

		signals:
			/**
			 * \brief Sent when the service is opened.
			 **/
			void opened();

			/**
			 * \brief Sent when the service is closed.
			 **/
			void closed();

		private slots:
			/**
			 * \brief Respond to the service opening.
			 **/
			void respondToOpened();
			
			/**
			 * \brief Respond to the service closing.
			 **/
			void respondToClosed();

		private:
			friend class MediaServiceHandlerPrivate;
			MediaServiceHandlerPrivate* d;
	};
}

#endif // MEDIA_SERVICE_HANDLER_H