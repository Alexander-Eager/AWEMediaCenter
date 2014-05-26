#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// JSON data
#include <JsonDataTree/Json.h>

namespace UI
{
	/**
	 * \brief An interface defining anything that
	 *			can be configured with a JSON value
	 *			from a skin.
	 *
	 * This requires two functions:
	 *	- `useConfig()`, which sets all relevant
	 *		painting/UI information to use the given data.
	 *	- `useDefaultConfig()`, which tells the object to
	 *		use the default configuration (which usually
	 *		comes from the current skin).
	 **/
	class AWEMC_BACKEND_LIBRARY Configurable
	{
		public:
			/**
			 * \brief Configure this object to use the
			 *			given data.
			 *
			 * If `data` is missing important members,
			 * the object is free to use whatever reasonable
			 * defaults it sees fit.
			 *
			 * \param data The data to use.
			 **/
			virtual void useConfig(JSON::JsonValue data) = 0;

			/**
			 * \brief Tell this object to use the default
			 *			configuration.
			 *
			 * Usually, this comes from the currently set skin.
			 **/
			virtual void useDefaultConfig() = 0;
	};
}

#endif // CONFIGURABLE_H