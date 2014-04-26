#ifndef AWE_MEDIA_ITEM_H
#define AWE_MEDIA_ITEM_H

// for holding data
#include <QString>
#include <QDir>

// for holding settings data
#include "libs/json/json.h"

/** \brief The type of item. **/
enum ItemType { FOLDER_TYPE, FILE_TYPE, SERVICE_TYPE };

namespace AWE
{
	/**
	 * \brief Represents a media file, folder, or service.
	 *
	 * Holds all relevant metadata for the item.
	 **/
	class MediaItem
	{
		public:
			/** \brief Create from the given JSON file.
			 *
			 * \param file The JSON file path.
			 **/
			MediaItem(const QDir& file);

			/** \brief Deconstructor. **/
			virtual ~MediaItem();

			/**
			 * \brief Get the data for this item.
			 *
			 * \returns The data for this item.
			 **/
			virtual Json::Value& getData();

			/**
			 * \brief Get the data for this item.
			 *
			 * \returns The data for this item.
			 **/
			virtual const Json::Value& getData() const;

			/**
			 * \brief Get a member of unspecified type by name.
			 *
			 * \param str A formatted string representing the path
			 *				to the member variable in the JSON file.
			 *
			 * \returns The value associated with the key `str`.
			 **/
			virtual const Json::Value& getMember(const QString& str) const;

			/**
			 * \brief Get a member of unspecified type by name.
			 *
			 * \param str A formatted string representing the path
			 *				to the member variable in the JSON file.
			 *
			 * \returns The value associated with the key `str`.
			 **/
			virtual Json::Value& getMember(const QString& str);

			/**
			 * \brief Get a member of `bool` type by name.
			 *
			 * \param str A formatted string representing the path
			 *				to the member variable in the JSON file.
			 *
			 * \returns The value associated with the key `str`.
			 **/
			virtual bool getBoolMember(const QString& str) const;

			/**
			 * \brief Get a member of `QString` type by name.
			 *
			 * \param str A formatted string representing the path
			 *				to the member variable in the JSON file.
			 *
			 * \returns The value associated with the key `str`.
			 **/
			virtual QString getStringMember(const QString& str) const;

			/**
			 * \brief Get a member of `int` type by name.
			 *
			 * \param str A formatted string representing the path
			 *				to the member variable in the JSON file.
			 *
			 * \returns The value associated with the key `str`.
			 **/
			virtual int getIntMember(const QString& str) const;

			/**
			 * \brief Get the name of the media item.
			 *
			 * Equivalent to `getStringMember("metadata.name")`
			 *
			 * \returns The name of this media item.
			 **/
			virtual QString getName() const;

			/**
			 * \brief Get the absolute path to the JSON settings file.
			 *
			 * \returns The path to the JSON settings file.
			 **/
			virtual const QDir& getJSONFile() const;

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const = 0;

		protected:
			/** \brief The JSON file for this item. **/
			QDir myJSONFile;

			/** \brief The data for this item. **/
			Json::Value myData;
	};
}

#endif