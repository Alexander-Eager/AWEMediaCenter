#ifndef AWE_FOLDER_H
#define AWE_FOLDER_H

// global settings
#include "settings/AWEGlobalSettings.h"

// the super class
#include "AWEMediaItem.h"

// for holding data
#include <vector>

/**
 * \brief A folder that contains `AWEMediaItem`s.
 **/
class AWEFolder : public AWEMediaItem
{
	public:
		/**
		 * \brief Construct from the folder's settings
		 *			and from the global settings.
		 *
		 * \param folder The configuration file for this folder.
		 * \param settings The global settings.
		 **/
		AWEFolder(const QDir& folder, AWEGlobalSettings* settings);

		/** \brief Deconstructor. **/
		virtual ~AWEFolder();

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
		virtual std::vector<AWEMediaItem*>& getItems();

	private:
		/** \brief List of contained items. **/
		std::vector<AWEMediaItem*> myItems;
};

#endif