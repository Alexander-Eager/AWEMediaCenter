#ifndef MEDIA_SERVICE_HANDLER_H
#define MEDIA_SERVICE_HANDLER_H

// library macros and forward declarations
#include "macros/BackendLibraryMacros.h"

// superclass
#include "MediaItem.h"

namespace AWE {
	// internal data class
	class MediaServiceHandlerPrivate;

	/**
	 * \brief Handles a `MediaService` object.
	 *
	 * This loads and unloads the plugin to
	 * save memory space.
     */
    class AWEMC_BACKEND_LIBRARY MediaServiceHandler : public MediaItem {
		Q_OBJECT
		
		public:
			/**
			 * \brief Construct from the given JSON file.
			 *
			 * \param file The JSON file for this service.
             */
			MediaServiceHandler(QString file);

			/**
			 * \brief Construct from the given JSON file.
			 *
			 * \param file The JSON file for this service.
             */
			MediaServiceHandler(ConfigFile* file);

			virtual ~MediaServiceHandler();

			/**
			 * \brief Determine if this service is valid.
			 *
			 * \returns `true` if the service is valid,
			 *			`false` otherwise.
             */
            auto isValid() const -> bool;

			/**
			 * \brief Get the type of this item.
			 *
			 * \returns SERVICE
             */
            auto getItemType() const -> ItemType;

		public slots:
			/**
			 * \brief Open the media service.
			 *
			 * \returns `true` if the launch was successful,
			 *			`false` otherwise.
             */
            bool open();

			/**
			 * \brief Close the media service.
			 *
			 * \returns `true` if the application closed
			 *			without error, `false` otherwise.
             */
            bool close();

		signals:
			/**
			 * \brief Sent when the service is opened.
             */
            void opened();

			/**
			 * \brief Sent when the service is closed.
             */
            void closed();

		private:
			friend class MediaServiceHandlerPrivate;
			MediaServiceHandlerPrivate* d;
	};
}

#endif // MEDIA_SERVICE_HANDLER_H
