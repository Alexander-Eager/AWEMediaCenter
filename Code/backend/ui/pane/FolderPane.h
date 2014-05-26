#ifndef FOLDER_PANE_H
#define FOLDER_PANE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// superclass
#include "Pane.h"

// Q_OBJECT
#include <QObject>

// the Folder class
#include "items/Folder.h"

// the MediaItem class
#include "items/MediaItem.h"

namespace UI
{
	// internal data class
	class FolderPanePrivate;

	/**
	 * \brief Allows the user to browse through
	 *			the items of a folder.
	 *
	 * This is a collection of UI items holding
	 * a list of `AWE::MediaItem`s and a back button.
	 *
	 * \todo Other layout options, possibly with icons.
	 **/
	class AWEMC_BACKEND_LIBRARY FolderPane : public Pane
	{
		Q_OBJECT

		public:
			/**
			 * \brief Construct with the given parent widget.
			 *
			 * \param[in] parent The parent widget.
			 **/
			FolderPane(QWidget* parent);

			/**
			 * \brief Destroys this object.
			 **/
			virtual ~FolderPane();

		public slots:
			/**
			 * \brief Change the folder to the given folder.
			 *
			 * Changes the list of items that the user can select.
			 *
			 * \param[in] folder The folder to change to.
			 **/
			virtual void setFolder(AWE::Folder* folder);

		signals:
			/**
			 * \brief Sent when an item is highlighted, but not
			 *			selected.
			 *
			 * \param[in] item The item that was highlighted.
			 **/
			void itemHighlighted(AWE::MediaItem* item);

			/**
			 * \brief Sent when the user has opened an item.
			 *
			 * \param[in] item The item that was chosen.
			 **/
			void itemSelected(AWE::MediaItem* item);

			/**
			 * \brief Sent when the user wants to go back one
			 *			folder.
			 **/
			void goUpOne();

		private:
			friend class FolderPanePrivate;
			FolderPanePrivate* d;
	};
}

#endif