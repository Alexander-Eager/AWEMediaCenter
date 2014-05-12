#ifndef JSON_PATH_H
#define JSON_PATH_H

// superclass
#include <QObject>

// for holding data
#include <QString>
#include <QStringList>
#include <QList>
#include "libs/json/json.h"

// for initialization
#include <initializer_list>

namespace AWE
{
	/**
	 * \brief Describes a key in a JSON object
	 *			or array.
	 *
	 * Essentially, this is a `union` that can
	 * be either a `QString` or a `uint`.
	 **/
	class JsonKey : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make an integer key, i.e.
			 *			an index in an array.
			 *
			 * When constructing a `JsonKey` from
			 * a numeric value, it cannot be used
			 * as a key in an object; it can only
			 * be used in an array.
			 *
			 * \param key The key to hold.
			 **/
			JsonKey(uint key);

			/**
			 * \brief Make an integer key, i.e.
			 *			an index in an array.
			 *
			 * When constructing a `JsonKey` from
			 * a numeric value, it cannot be used
			 * as a key in an object; it can only
			 * be used in an array.
			 *
			 * \param key The key to hold.
			 **/
			JsonKey(int key);

			/**
			 * \brief Make a string key, i.e.
			 *			a key for an object.
			 *
			 * When constructing a `JsonKey` from
			 * a string value, it can always be used
			 * as a key in an object. If the key
			 * is the string representation of a number,
			 * it can also be used in an array.
			 *
			 * \param key The key to hold.
			 **/
			JsonKey(QString key);

			/**
			 * \brief Make a string key, i.e.
			 *			a key for an object.
			 *
			 * When constructing a `JsonKey` from
			 * a string value, it can always be used
			 * as a key in an object. If the key
			 * is the string representation of a number,
			 * it can also be used in an array.
			 *
			 * \param key The key to hold.
			 **/
			JsonKey(const char* key);

			/**
			 * \brief Make a string key, i.e.
			 *			a key for an object.
			 *
			 * When constructing a `JsonKey` from
			 * a string value, it can always be used
			 * as a key in an object. If the key
			 * is the string representation of a number,
			 * it can also be used in an array.
			 *
			 * \param key The key to hold.
			 **/
			explicit JsonKey(const std::string& key);

			/**
			 * \brief Make a copy of `other`.
			 *
			 * \param other The key to copy.
			 **/
			JsonKey(const JsonKey& other);

			/**
			 * \brief Assign the contens of `other` to this.
			 *
			 * \param other The key to copy.
			 **/
			JsonKey& operator= (const JsonKey& other);

			/**
			 * \brief Destroy this object.
			 **/
			~JsonKey();

			/**
			 * \brief Determine if this can be used
			 *			as a key for an object.
			 *
			 * This only returns `true` if `isString()`
			 * returns `true`.
			 *
			 * \returns `true` if this can be used
			 * 			to access a member of an object,
			 *			`false` otherwise.
			 **/
			bool isObjectKey() const;

			/**
			 * \brief Convert this key to an object key.
			 *
			 * If `!isObjectKey()`, this returns `""`.
			 *
			 * \returns A string that can be used
			 *			to access a member of an object.
			 **/
			std::string toObjectKey() const;

			/**
			 * \brief Determine if this can be used
			 *			as an index for an array.
			 *
			 * This returns `true` if `isInteger()`
			 * returns `true` or the string this holds
			 * represents an integer.
			 *
			 * \returns `true` if this can be used
			 *			as an array index,
			 *			`false` otherwise.
			 **/
			bool isArrayIndex() const;

			/**
			 * \brief Convert this key to an array index.
			 *
			 * If `!isArrayIndex()`, this returns `(uint) -1`.
			 *
			 * \returns A `uint` that can be used
			 *			to access a member of an array.
			 **/
			uint toArrayIndex() const;

			/**
			 * \brief Determine if this holds
			 *			a string.
			 *
			 * If this returns `true`, `isObjectKey()`
			 * will also return `true`, but `isArrayIndex()`
			 * could be either `true` or `false` depending
			 * on the string.
			 *
			 * This returns the opposite of `isInteger()`.
			 *
			 * \returns `true` if the key held is in
			 *			a string format,
			 *			`false` otherwise.
			 **/
			bool isString() const;

			/**
			 * \brief Convert to a string.
			 *
			 * If `!isString()`, this returns `QString()`.
			 *
			 * \returns This key as a `QString`.
			 **/
			QString toString() const;

			/**
			 * \brief Determine if this holds
			 *			an integer.
			 *
			 * If this returns `true`, `isArrayIndex()`
			 * will also return `true`, and `isObjectKey()`
			 * returns `false`.
			 *
			 * This returns the opposite of `isString()`.
			 *
			 * \returns `true` if the key held is in
			 *			an integer format,
			 *			`false` otherwise.
			 **/
			bool isInteger() const;

			/**
			 * \brief Convert to a `uint`.
			 *
			 * If `!isInteger()`, this returns `(uint) -1`.
			 *
			 * \returns This key as a `uint`.
			 **/
			uint toInteger() const;

		private:
			/** 
			 * \brief `true` indicates this is a string,
			 *			`false` it is an integer.
			 **/
			bool myIsString;

			/**
			 * \brief `true` indicates that this can
			 *			be used as an array index.
			 **/
			bool myIsIndex;

			/** \brief For integer keys. **/
			uint myInteger;
			/** \brief For string keys. **/
			QString myString;
	};

	/**
	 * \brief Describes a path to a data member
	 *			of a JSON file.
	 *
	 * There are 3 ways to make a `JsonPath`:
	 *	- Initializer list: pass a list
	 *		of `QString`s and `uint`s to the
	 *		constructor, e.g.
	 *		`JsonPath path({"Hello", "World", 1})`.
	 *	- String: pass a `'.'`-separated list
	 *		of keys, e.g. `"Hello.World.1"`.
	 *	- String list: pass a `QStringList` filled
	 *		with the keys.
	 **/
	class JsonPath : public QObject
	{
		Q_OBJECT

		public:
			/**
			 * \brief Make from an initializer list.
			 *
			 * \param keys The list of keys representing
			 *			the path.
			 **/
			JsonPath(std::initializer_list<JsonKey> keys);

			/**
			 * \brief Make from a `'.'`-separated list of
			 *			keys.
			 *
			 * \param keys The string representing the path.
			 **/
			JsonPath(QString keys);

			/**
			 * \brief Make from a `'.'`-separated list of
			 *			keys.
			 *
			 * \param keys The string representing the path.
			 **/
			JsonPath(const char keys[]);

			/**
			 * \brief Make from a list of strings.
			 *
			 * \param keys The list of string keys.
			 **/
			JsonPath(QStringList keys);

			/**
			 * \brief Make a copy of `other`.
			 *
			 * \param other The path to copy.
			 **/
			JsonPath(const JsonPath& other);

			/**
			 * \brief Get the member of `data` at the
			 *			end of this path.
			 *
			 * If the path does not exist in `data`,
			 * this function returns `Json::null`.
			 *
			 * \param data The JSON data to get a member
			 *			for.
			 *
			 * \returns The member at the end of this path
			 *			in `data`.
			 **/
			const Json::Value& followConst(const Json::Value& data) const;

			/**
			 * \brief Get the member of `data` at the
			 *			end of this path.
			 *
			 * If the path does not exist in `data`,
			 * this function returns `Json::null`.
			 *
			 * \param data The JSON data to get a member
			 *			for.
			 *
			 * \returns The member at the end of this path
			 *			in `data`.
			 **/
			Json::Value& follow(Json::Value& data) const;

			/**
			 * \brief Create this path in `data` and return
			 *			the end of it.
			 *
			 * \param data The JSON data to create the member
			 *			in.
			 *
			 * \returns The member at the end of this path
			 *			in `data`.
			 **/
			Json::Value& create(Json::Value& data) const;

		private:
			/** \brief Static member for nonexistant results. **/
			static Json::Value null;

			/** \brief The list of keys representing the path. **/
			QList<JsonKey> myPath;
	};
}

#endif