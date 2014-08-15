#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

// library macro
#include "macros/BackendLibraryMacros.h"

// superclass
#include <QObject>

// internal data
#include "items/MediaFile.h"
#include <QString>

namespace AWE {
	// forward declarations
	class MediaFile;
	
	/**
	 * \brief Represents an abstract media player's functions.
	 *
	 * \todo Make plugin interface.
     */
    class AWEMC_BACKEND_LIBRARY MediaPlayer : public QObject {
		Q_OBJECT

		public:
			/**
			 * \brief Deconstructor.
             */
			virtual ~MediaPlayer() { }

			/**
			 * \brief Get the name of the player.
			 *
			 * \returns The name of the player.
             */
			virtual QString getName() const = 0;

			/**
			 * \brief Determine if the given media file
             *        can be played by this player.
			 *
			 * \param file The file to determine playability for.
			 *
			 * \returns `true` if this player can play `file`,
			 *			`false` otherwise.
             */
			virtual bool canPlay(MediaFile* file) const = 0;

			/**
			 * \brief Determine if the player is being used.
			 *
			 * \returns `true` if the player is being used,
			 *			`false` otherwise.
             */
			virtual bool isPlaying() const = 0;

			/**
			 * \brief Determines if the player is playing
             *		  a particular file.
			 *
			 * If this returns `true` for any file,
			 * `isPlaying()` must also return `true`.
			 *
			 * \param file The file to check for.
			 *
			 * \returns `true` if the player is being used
			 *			to play `file`, `false` otherwise.
             */
			virtual bool isPlaying(MediaFile* file) const = 0;

			/**
			 * \brief Determine if this player can be used at all.
			 *
			 * \returns `true` if this player is valid, `false`
			 *			otherwise.
             */
			virtual bool isValid() const = 0;

		public slots:
			/**
			 * \brief Play the given file.
			 *
			 * For players that have a queue (i.e., that add
			 * an item to a list to be played through), this
			 * should add `file` to the queue and return `true`,
			 * but should NOT `emit startedPlaying(file)` until
			 * the file actually starts playing. Similarly,
			 * `isPlaying(file)` should return `false` until the
			 * file actually starts playing.
			 *
			 * \param file The media file to play.
			 *
			 * \returns `true` if `file` played successfully,
			 *			`false` otherwise.
             */
			virtual bool play(MediaFile* file) = 0;

			/**
			 * \brief Close the media player.
			 *
			 * \returns `true` if the player is now closed,
			 *			`false` otherwise.
             */
			virtual bool close() = 0;

			/**
			 * \brief Close a specific file.
			 *
			 * This is used mostly for queued players,
			 * to remove a particular file from the queue,
			 * but it is also used for regular, single-item
			 * players to close the current item.
			 *
			 * \param file The file to close.
			 *
			 * \returns `true` if the player is playing `file`
			 *			and it was closed successfully,
			 *			`false` otherwise.
             */
			virtual bool close(MediaFile* file) = 0;

		signals:
			/**
			 * \brief Sent when the player has been closed.
			 *
			 * This should be sent whenever `close()` is called
			 * successfully, and whenever the file stops playing.
			 *
			 * For queued players, or any player that plays multiple
			 * items, this should NOT be sent until all items stop
			 * playing, as doing so will cause the player handler
			 * to unload the player.
			 *
			 * Basically, this indicates that `isPlaying()` has
			 * changed from `true` to `false`.
             */
			void closed();

			/**
			 * \brief Sent when the player has been closed.
			 *
			 * This should be sent whenever `close()` is called
			 * successfully, and whenever the file stops playing.
			 *
			 * \param file The file that was closed.
             */
			void closed(MediaFile* file);

			/**
			 * \brief Sent when the player has opened a file.
			 *
			 * This should be sent whenever `play()` is called
			 * successfully, and whenever the file starts playing.
			 *
			 * For queued players, or any player that plays multiple
			 * items, this should only be sent for the first item
			 * that starts playing. In other words, this indicates
			 * that `isPlaying()` has changed from `false` to `true`.
             */
			void startedPlaying();

			/**
			 * \brief Sent when the player has opened a file.
			 *
			 * This should be sent whenever `play()` is called
			 * successfully, and whenever the file starts playing.
			 *
			 * \param file The file that has started playing.
             */
			void startedPlaying(MediaFile* file);
	};
}

#endif // MEDIA_PLAYER_H
