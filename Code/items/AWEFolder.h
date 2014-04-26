#ifndef AWE_FOLDER_H
#define AWE_FOLDER_H

// global settings
#include "settings/AWEGlobalSettings.h"

// the super class
#include "AWEMediaItem.h"

// for holding data
#include <QList>

namespace AWE
{
	/**
	 * \brief A folder that contains `MediaItem`s.
	 **/
	class Folder : public MediaItem
	{
		public:
			/**
			 * \brief Construct from the folder's settings
			 *			and from the global settings.
			 *
			 * \param folder The configuration file for this folder.
			 * \param settings The global settings.
			 **/
			Folder(const QDir& folder, GlobalSettings* settings);

			/** \brief Deconstructor. **/
			virtual ~Folder();

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const;

			/**
			 * \brief Get a list of all of the items this folder contains.
			 *
			 * \returns All of the items this folder contains.
			 **/
			virtual QList<MediaItem*> getItems();

			/**
			 * \brief Add an item.
			 *
			 * \param item The item to add to this `Folder`.
			 **/
			virtual void addItem(MediaItem* item);

		private:
			/** \brief List of contained items. **/
			QList<MediaItem*> myItems;
	};
}

#endif