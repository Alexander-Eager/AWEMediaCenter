#ifndef JSON_PLAYER_H
#define JSON_PLAYER_H

// interface this implements
#include "player/MediaPlayer.h"

// configuration file
#include "settings/ConfigFile.h"

// internal data class
class JsonPlayerPrivate;

/**
 * \brief A media player for AWEMC that runs external programs
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
 *				// {0} refers to the full path to the media file 
 *				"command": "some command",
 *				// list of file names that this can play, using
 *				// standard bash syntax for wildcards
 *				"can play": ["*.ext1", "*.ext2", ...]
 *				// determines if the terminal itself should be shown
 *				// this is optional; assumed to be false if missing
 *				"show console": true or false
 *			}
 *		}
 *
 * `<plugin location>` is one of these:
 *	- On OS X, it is `"libs/libJsonPlayer.dylib"`.
 *	- On Linux, it is `"libs/libJsonPlayer.so"`.
 *	- On Windows, it is `"libs/JsonPlayer.dll"`.
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
 *		have the command be `"/Applications/VLC.app -vvv \"{0}\""`. You must do
 *		one of the following:
 *		- `"/Applications/VLC.app/Contents/MacOS/VLC -vvv \"{0}\""`
 *		- `"open /Applications/VLC.app --args -vvv \"{0}\""`
 *		- `"open \"{0}\"" -a /Applications/VLC.app"`
 *	- You should almost always enclose the `{0}` with quotes.
 *
 * \todo Implement `"show console"`.
 **/
class JsonPlayer : public AWE::MediaPlayer
{
	public:
		/**
		 * \brief Make a JSON player from the given configuration file.
		 *
		 * \param file The configuration file for the player.
		 **/
		JsonPlayer(AWE::ConfigFile* file);

		/**
		 * \brief Deconstructor.
		 **/
		virtual ~JsonPlayer();

		/**
		 * \brief Get the name of the player.
		 *
		 * \returns The name of the player.
		 **/
		virtual QString getName() const;

		/**
		 * \brief Determine if the given media file
		 *			can be played by this player.
		 *
		 * This is determined by the `"can play"` tag.
		 *
		 * \param file The file to determine playability for.
		 *
		 * \returns `true` if this player can play `file`,
		 *			`false` otherwise.
		 **/
		virtual bool canPlay(AWE::MediaFile* file) const;

		/**
		 * \brief Determine if the player is being used.
		 *
		 * \returns `true` if the player is being used,
		 *			`false` otherwise.
		 **/
		virtual bool isPlaying() const;

		/**
		 * \brief Determines if the player is playing
		 *			a particular file.
		 *
		 * \param file The file to check for.
		 *
		 * \returns `true` if the player is being used
		 *			to play `file`, `false` otherwise.
		 **/
		virtual bool isPlaying(AWE::MediaFile* file) const;

		/**
		 * \brief Determine if this player can be used at all.
		 *
		 * \returns `true` if this player is valid, `false`
		 *			otherwise.
		 **/
		virtual bool isValid() const;

	public slots:
		/**
		 * \brief Play the given file.
		 *
		 * \param file The media file to play.
		 *
		 * \returns `true` if `file` played successfully,
		 *			`false` otherwise.
		 **/
		virtual bool play(AWE::MediaFile* file);

		/**
		 * \brief Close the media player.
		 *
		 * \returns `true` if the player is now closed,
		 *			`false` otherwise.
		 **/
		virtual bool close();

		/**
		 * \brief Close a specific file.
		 *
		 * Since JSON players only allow one instance of the
		 * program at a time, this just calls `close()`
		 * if the application is currently playing `file`.
		 *
		 * \param file The file to close.
		 *
		 * \returns `true` if the player is playing `file`
		 *			and it was closed successfully,
		 *			`false` otherwise.
		 **/
		virtual bool close(AWE::MediaFile* file);

	private:
		JsonPlayerPrivate* d;
};

#endif // JSON_PLAYER_H