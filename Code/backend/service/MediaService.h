#ifndef MEDIA_SERVICE_H
#define MEDIA_SERVICE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QObject>

// for data
#include <QString>

namespace AWE
{
	/**
	 * \brief Represents a media service.
	 *
	 * A media service is basically an application that does
	 * NOT launch files from AWEMC. An example would be
	 * Netflix, or iTunes.
	 **/
	class AWEMC_BACKEND_LIBRARY MediaService : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * \brief Destroy this object.
			 **/
			virtual ~MediaService() { }

			/**
			 * \brief Determine if this service is valid.
			 *
			 * \returns `true` if the service is valid,
			 *			`false` otherwise.
			 **/
			virtual bool isValid() const = 0;

			/**
			 * \brief Get the name of the service.
			 *
			 * \returns The name of the service.
			 **/
			virtual QString getName() const = 0;

		public slots:
			/**
			 * \brief Open the service.
			 *
			 * \returns `true` if the service was closed
			 *			successfully, `false` otherwise.
			 **/
			virtual bool open() = 0;

			/**
			 * \brief Close the service.
			 *
			 * \returns `true` if the service was opened
			 *			successfully, `false` otherwise.
			 **/
			virtual bool close() = 0;

		signals:
			/**
			 * \brief Sent when the service is opened.
			 **/
			void opened();

			/**
			 * \brief Sent when the service is closed.
			 **/
			void closed();
	};
}

#endif // MEDIA_SERVICE_H