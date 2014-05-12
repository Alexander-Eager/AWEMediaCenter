#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

// super class
#include <QObject>

// for holding data
#include "json.h"
#include <QDir>
#include <QString>

// for retrieving data
#include "JsonPath.h"

namespace AWE
{
	/**
	 * \brief Holds the information for a configuration
	 *			file in an abstract way.
	 *
	 * The configuration files used by AWEMC are all
	 * JSON files.
	 *
	 * All data is stored in `Json::Value` objects from the
	 * [JsonCpp library](http://jsoncpp.sourceforge.net).
	 **/
	class ConfigFile : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * \brief Create a wrapper for JSON data not in
			 *			a file.
			 **/
			ConfigFile();

			/**
			 * \brief Open the given config file.
			 *
			 * \param[in] file The file to open. If
			 *			the file does not exist,
			 *			the config data will be
			 *			initialized to an empty map.
			 **/
			ConfigFile(QString file);

			/**
			 * \brief Depathoys this object.
			 **/
			virtual ~ConfigFile();

			/**
			 * \brief Check to see if the config file is
			 *			valid.
			 *
			 * This returns `false` if and only if the file
			 * exists but is not properly formatted. If the
			 * file does not exist, this returns `true`; the
			 * class will create the file.
			 *
			 * \returns `true` if the config file is valid,
			 *			`false` otherwise.
			 **/
			virtual bool isValid() const;

			/**
			 * \brief Get this file's name, without
			 *			the path.
			 *
			 * \returns The config file name.
			 **/
			virtual QString getConfigFileName() const;

			/**
			 * \brief Get the path to this config file,
			 *			excluding the file name.
			 *
			 * \returns The path to the config file.
			 **/
			virtual QDir getPathToConfigFile() const;

			/**
			 * \brief Determine if this config file has
			 *			been altered since it was read.
			 *
			 * \returns `true` if this config file has
			 *			been altered since it was read,
			 *			`false` otherwise.
			 **/
			bool hasBeenEdited() const;

			/**
			 * \brief Mark this config file as edited,
			 * 			so that the data is written to
			 *			file upon deletion.
			 **/
			void markAsEdited();

			/**
			 * \brief Write the data to file.
			 **/
			void writeToFile();

			/**
			 * \brief Get the data held in this config
			 *			file.
			 *
			 * \returns The data held in this config file.
			 **/
			virtual const Json::Value& getData() const;

			/**
			 * \brief Set the data held in this config
			 *			file.
			 *
			 * \param[in] data The new data to hold.
			 **/
			virtual void setData(const Json::Value& data);

			/**
			 * \brief Get a data member.
			 *
			 * `path` is a list of values to follow to reach
			 * the desired data member. So if I have:
			 * 
			 *	 	{
			 *	 		"a": {
			 *	 			"b": [
			 *	 				"Hello World"
			 *	  			]			
			 *	 		}
			 *	 	}
			 *
			 * The list to use to get to `"Hello World"` is
			 * `{ "a", "b", 0 }`.
			 *
			 * \param[in] path The path to the data member to retrieve.
			 *
			 * \returns The desired data member, or a null `Json::Value` if
			 *			the member does not exist.
			 **/
			virtual const Json::Value& getMember(JsonPath path) const;

			/**
			 * \brief Set a data member to a new value.
			 *
			 * \see getMember(JsonPath)
			 *
			 * \param[in] path The path to the data member.
			 * \param[in] value The new value for the data member.
			 *
			 * \returns `true` if the data member exists,
			 *			`false` if an error occurred.
			 **/
			virtual bool setMember(JsonPath path, const Json::Value& value);

			/**
			 * \brief Append a value to a array member.
			 *
			 * The member must be an array type. If it is not,
			 * the function will not do anything.
			 *
			 * \see getMember(JsonPath)
			 *
			 * \param[in] path The path to the data member.
			 * \param[in] value The value to append to the data member.
			 *
			 * \returns `true` if the data member exists and is an array,
			 *			`false` if an error occurred.
			 **/
			virtual bool appendValueToMember(JsonPath path, const Json::Value& value);

			/**
			 * \brief Append a key-value pair to an object member.
			 *
			 * The member must be an object type. If it is not,
			 * the function will not do anything.
			 *
			 * \see getMember(JsonPath)
			 *
			 * \param[in] path The path to the data member.
			 * \param[in] key The key to append to the data member.
			 * \param[in] value The value to assign to `key`.
			 *
			 * \returns `true` if the data member exists and is an object,
			 *			`false` if an error occurred.
			 **/
			 virtual bool appendValueToMember(JsonPath path, QString key,
												const Json::Value& value);

		signals:
			/**
			 * \brief Sent when any data member is changed.
			 **/
			void dataChanged();

		private:
			/** \brief The name of the config file. **/
			QString myConfigFileName;

			/** \brief The path to the config file. **/
			QDir myPathToConfigFile;

			/** \brief The data map. **/
			Json::Value myData;

			/** \brief Flag determining if the data has been edited. **/
			bool myEditedFlag;

			/** \brief Flag determining if the file was valid. **/
			bool myValidity;
	};
}

#endif