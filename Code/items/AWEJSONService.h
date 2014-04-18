#ifndef AWE_JSON_SERVICE_H
#define AWE_JSON_SERVICE_H

// super class
#include "AWEMediaService.h"

// for holding data
#include <string>

/**
 * \brief An external media service (aka application)
 *			described by a JSON file.
 **/
class AWEJSONService : public AWEMediaService
{
	public:
		/**
		 * \brief Construct an AWEMediaService from
		 *			its JSON file.
		 *
		 * \param file The JSON file.
		 **/
		AWEJSONService(const QDir& file);

		/**
		 * \brief Open the application.
		 *
		 * \returns The exit code of the application.
		 **/
		virtual int open();

	private:
		/** \brief The command to run. **/
		std::string myCommand;
};

#endif