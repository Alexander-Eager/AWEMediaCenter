#ifndef AWE_MEDIA_ITEM_H
#define AWE_MEDIA_ITEM_H

// for holding data
#include <QString>
#include <QPixmap>
#include <QList>

// for holding settings data
#include "settings/ConfigFile.h"

// superclass that holds data
#include "settings/MetadataHolder.h"

namespace AWE
{
	// internal data
	class MediaItemPrivate;

	/**
	 * \brief Represents a media file, folder, or service.
	 *
	 * By subclassing `MetadataHolder`, all `MediaItem`
	 * subclasses have metadata that they can access and
	 * modify. In reality, `MediaItem`s are not much
	 * more than `MetadataHolder`s that also have a
	 * item type.
	 **/
	class MediaItem : public MetadataHolder
	{
		Q_OBJECT

		Q_ENUMS(ItemType)

		Q_PROPERTY(ItemType itemType
			READ getItemType
			STORED false
			CONSTANT
			FINAL)
		Q_PROPERTY(bool isFolder
			READ isFolder
			STORED false
			CONSTANT
			FINAL)
		Q_PROPERTY(bool isFile
			READ isFile
			STORED false
			CONSTANT
			FINAL)
		Q_PROPERTY(bool isService
			READ isService
			STORED false
			CONSTANT
			FINAL)

		public:
			/** \brief The type of item. **/
			enum ItemType { FOLDER, FILE, SERVICE };

			/** 
			 * \brief Create from the given JSON file.
			 *
			 * \param file The JSON file path.
			 **/
			MediaItem(QString file);

			/**
			 * \brief Create from the given config file.
			 *
			 * \param file The config file.
			 **/
			MediaItem(ConfigFile* file);

			/** 
			 * \brief Destroys this object.
			 **/
			virtual ~MediaItem();

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const = 0;

			/**
			 * \brief Determine if this is a folder.
			 *
			 * \returns `true` if this is a folder,
			 *			`false` otherwise.
			 **/
			virtual bool isFolder() const;

			/**
			 * \brief Determine if this is a file.
			 *
			 * \returns `true` if this is a file,
			 *			`false` otherwise.
			 **/
			virtual bool isFile() const;

			/**
			 * \brief Determine if this is a service.
			 *
			 * \returns `true` if this is a service,
			 *			`false` otherwise.
			 **/
			virtual bool isService() const;

			/**
			 * \brief Make a media item from the given
			 *			file, or retrieve it if it already
			 *			exists.
			 *
			 * This is used to create the item, or retrieve
			 * it if it already exists.
			 *
			 * \param file The path to the file.
			 *
			 * \returns A pointer to the newly created item,
			 *			or `nullptr` if the file is not correct.
			 **/
			static MediaItem* makeItem(QString file);

			/**
			 * \brief Cleanup all items.
			 **/
			static void deleteAllItems();

		private:
			MediaItemPrivate* d;
	};
}

#endif