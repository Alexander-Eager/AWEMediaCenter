#ifndef AWE_JSON_SERVICE_H
#define AWE_JSON_SERVICE_H

// super class
#include "AWEMediaService.h"

// for holding data
#include <QString>

namespace AWE
{
	/**
	 * \brief An external media service (aka application)
	 *			described by a JSON file.
	 **/
	class JSONService : public MediaService
	{
		public:
			/**
			 * \brief Construct an MediaService from
			 *			its JSON file.
			 *
			 * \param file The JSON file.
			 **/
			JSONService(const QDir& file);

			/**
			 * \brief Open the application.
			 *
			 * \returns The exit code of the application.
			 **/
			virtual int open();

		private:
			/** \brief The command to run. **/
			QString myCommand;
	};
}

#endif