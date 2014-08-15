#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

// library macros
#include "macros/BackendLibraryMacros.h"

// super class
#include <QObject>

// for data
#include <JsonDataTree/Json.h>
#include <QDir>
#include <QString>

namespace AWE {
	// internal data
	class ConfigFilePrivate;

	/**
	 * \brief Holds the information for a configuration
     *		  file in an abstract way.
	 *
	 * The configuration files used by AWEMC are all
	 * JSON files.
	 *
	 * All data is stored in `JSON::JsonValue` objects from the
	 * JsonDataTree library.
	 *
	 * This class provides no copy constructor and should be used
	 * only in pointer form.
     */
    class AWEMC_BACKEND_LIBRARY ConfigFile : public QObject {
		Q_OBJECT

		Q_PROPERTY(QString configFileName
                   READ getConfigFileName
                   CONSTANT
                   FINAL)
		Q_PROPERTY(QDir pathToConfigFile
                   READ getPathToConfigFile
                   CONSTANT
                   FINAL)
		Q_PROPERTY(JSON::JsonValue data
                   READ getData
                   WRITE setData
                   NOTIFY dataChanged)
		Q_PROPERTY(bool edited
                   READ hasBeenEdited)
		Q_PROPERTY(bool valid
                   READ isValid
                   CONSTANT
                   FINAL)

		public:
			/**
			 * \brief Create a wrapper for JSON data not in
             *		  a file.
			 *
			 * This should be followed up by a call to `setData()`
			 * so that the object can be useful.
			 *
			 * No matter what function calls are made after the
			 * creation of this object, `isValid()` and
			 * `hasBeenEdited()` will always return `false`.
             */
			ConfigFile();

			/**
			 * \brief Open the given config file.
			 *
			 * \param[in] file The file to open. If
             *			  the file does not exist,
             *			  the config data will be
             *			  initialized to an empty map.
             */
			ConfigFile(QString file);

			/**
             * \brief Destroys this object.
             */
			virtual ~ConfigFile();

			/**
			 * \brief Check to see if the config file is
             *		  valid.
			 *
			 * This returns `false` if and only if the file
			 * exists but is not properly formatted. If the
			 * file does not exist, this returns `true`; the
			 * class will create the file.
			 *
			 * \returns `true` if the config file is valid,
			 *			`false` otherwise.
             */
			virtual bool isValid() const;

			/**
			 * \brief Get this file's name, without
             *		  the path.
			 *
			 * \returns The config file name.
             */
			virtual QString getConfigFileName() const;

			/**
			 * \brief Get the path to this config file,
             *		  excluding the file name.
			 *
			 * \returns The path to the config file.
             */
			virtual QDir getPathToConfigFile() const;

			/**
			 * \brief Determine if this config file has
             *		  been altered since it was read.
			 *
			 * \returns `true` if this config file has
			 *			been altered since it was read,
			 *			`false` otherwise.
             */
			virtual bool hasBeenEdited() const;

			/**
			 * \brief Mark this config file as edited,
             * 		  so that the data is written to
             *		  file upon deletion.
             */
			virtual void markAsEdited();

			/**
			 * \brief Write the data to file.
             */
			virtual void writeToFile();

			/**
			 * \brief Get the data held in this config
             *		  file.
			 *
			 * \returns The data held in this config file.
             */
			virtual JSON::JsonValue getData() const;

			/**
			 * \brief Set the data held in this config
             *		  file.
			 *
			 * \param[in] data The new data to hold.
             */
			virtual void setData(JSON::JsonValue data);

			/**
			 * \brief Determine if a data member exists.
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
			 * \param[in] path The path to the data member to look for.
			 *
			 * \returns `true` if the data member exists,
			 *			`false` otherwise.
             */
			virtual bool hasMember(JSON::JsonPath path) const;

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
             */
			virtual JSON::JsonValue getMember(JSON::JsonPath path) const;

			/**
			 * \brief Set a data member to a new value.
			 *
			 * \see getMember(JSON::JsonPath)
			 *
			 * \param[in] path The path to the data member.
			 * \param[in] value The new value for the data member.
			 *
			 * \returns `true` if the data member exists,
			 *			`false` if an error occurred.
             */
			virtual bool setMember(JSON::JsonPath path, JSON::JsonValue value);

			/**
			 * \brief Append a value to a array member.
			 *
			 * The member must be an array type. If it is not,
			 * the function will not do anything.
			 *
			 * \see getMember(JSON::JsonPath)
			 *
			 * \param[in] path The path to the data member.
			 * \param[in] value The value to append to the data member.
			 *
			 * \returns `true` if the data member exists and is an array,
			 *			`false` if an error occurred.
             */
			virtual bool appendValueToMember(JSON::JsonPath path,
												JSON::JsonValue value);

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
             */
			virtual bool appendValueToMember(JSON::JsonPath path, QString key,
												JSON::JsonValue value);

			/**
			 * \brief Remove a member from this file.
			 *
			 * This will only remove the last member of
			 * specified in the path.
			 *
			 * \param path The path to the member to remove.
			 *
			 * \returns `true` if the path is valid,
			 *			`false` otherwise.
             */
			virtual bool removeMember(JSON::JsonPath path);

			/**
			 * \brief Add a member to this file.
			 *
			 * This creates the path, and sets the value.
			 *
			 * Objects are favored to arrays if a key in `path` is
			 * ambiguous.
			 *
			 * If `path` already exists, the member is changed.
			 *
			 * \param path The path to the member to create.
			 * \param value The value to assign to this member.
			 *
			 * \returns `true` if the path is valid,
			 *			`false` otherwise.
             */
			virtual bool addMember(JSON::JsonPath path, JSON::JsonValue value);

		signals:
			/**
			 * \brief Sent when any data member is changed.
             */
			void dataChanged();

		private:
			// implicitly deleted copy constructor
			ConfigFile(const ConfigFile&) { }

            /** \brief Internal data *d-pointer*. */
			ConfigFilePrivate* d;
	};
}

#endif
