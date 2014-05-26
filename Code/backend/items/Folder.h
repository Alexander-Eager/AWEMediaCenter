#ifndef FOLDER_H
#define FOLDER_H

// the super class
#include "MediaItem.h"

// for holding data
#include <QList>
#include <QString>

namespace AWE
{
	// internal data class
	class FolderPrivate;

	/**
	 * \brief A folder that contains `MediaItem`s.
	 **/
	class Folder : public MediaItem
	{
		Q_OBJECT
		
		public:
			/**
			 * \brief Construct from the folder's settings.
			 *
			 * \param file The configuration file for this folder.
			 **/
			Folder(QString file);

			/**
			 * \brief Construct from the folder's settings.
			 *
			 * \param file The configuration file for this folder.
			 **/
			Folder(ConfigFile* file);

			/** 
			 * \brief Destroy this object. 
			 **/
			virtual ~Folder();

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns `FOLDER`
			 **/
			virtual ItemType getItemType() const;

			/**
			 * \brief Get a list of all of the items this folder contains.
			 *
			 * \returns All of the items this folder contains.
			 **/
			virtual QList<MediaItem*> getItems();

		public slots:
			/**
			 * \brief Add an item.
			 *
			 * \param item The item to add to this `Folder`.
			 **/
			virtual void addItem(MediaItem* item);

		signals:
			/**
			 * \brief Sent when an item is added to this folder.
			 *
			 * \param item The added item.
			 **/
			void itemAdded(MediaItem* item);

		private:
			FolderPrivate* d;
	};
}

#endif // FOLDER_H