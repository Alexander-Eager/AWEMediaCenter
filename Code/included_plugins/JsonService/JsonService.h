#ifndef JSON_SERVICE_H
#define JSON_SERVICE_H

// superclass
#include "service/MediaService.h"

// configuration file
#include "settings/ConfigFile.h"

// internal data class
class JsonServicePrivate;

/**
 * \brief A media service class that runs external programs
 *			based on a JSON configuration file.
 *
 * The general format of the file should be as follows:
 *
 *		{
 *			"metadata": {
 *				"location": <plugin location>,
 *				// other metadata for your player goes here
 *			},
 *			"config": {
 *				// terminal command to run
 *				"command": "some command",
 *				// determines if the terminal itself should be shown
 *				// this is optional; assumed to be false if missing
 *				"show console": true or false
 *			}
 *		}
 *
 * `<plugin location>` is one of these:
 *	- On OS X, it is `"libs/libJsonService.dylib"`.
 *	- On Linux, it is `"libs/libJsonService.so"`.
 *	- On Windows, it is `"libs/JsonService.dll"`.
 *	- On other platforms, it depends on the file names for
 *		dynamic libraries. Look it up online. It will always
 *		be `"libs/<library name>"`.
 *
 * A few tips and tricks:
 *	- The "Default Program" player included with AWEMC makes
 *		use of this plugin. It uses `open` on OS X, `xdg-open`
 *		on Linux, and nothing on Windows (typing in the file
 *		automatically selects the default program).
 *	- On OS X, applications are really folders, so you cannot
 *		have the command be `"/Applications/VLC.app"`. You must do
 *		one of the following:
 *		- `"/Applications/iTunes.app/Contents/MacOS/iTunes"`
 *		- `"open /Applications/iTunes.app""`
 *
 * \todo Implement `"show console"`.
 **/
class JsonService : public AWE::MediaService
{
	public:
		/**
		 * \brief Construct a JSON service from its configuration
		 *			file.
		 *
		 * \param file The configuration file to use.
		 **/
		JsonService(AWE::ConfigFile* file);

		/**
		 * \brief Destroys this object.
		 **/
		virtual ~JsonService();

		/**
		 * \brief Determine if this service is valid.
		 *
		 * \returns `true` if the service is valid,
		 *			`false` otherwise.
		 **/
		virtual bool isValid() const;

		/**
		 * \brief Get the name of the service.
		 *
		 * \returns The name of the service.
		 **/
		virtual QString getName() const;

	public slots:
		/**
		 * \brief Open the service.
		 *
		 * \returns `true` if the service was opened
		 *			successfully, `false` otherwise.
		 **/
		virtual bool open();

		/**
		 * \brief Close the service.
		 *
		 * \returns `true` if the service was closed
		 *			successfully, `false` otherwise.
		 **/
		virtual bool close();

	private:
		JsonServicePrivate* d;
};

#endif // JSON_SERVICE_H