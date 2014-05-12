#ifndef AWE_MEDIA_ITEM_H
#define AWE_MEDIA_ITEM_H

// for holding data
#include <QString>
#include <QDir>
#include <QPixmap>
#include <QList>

// for holding settings data
#include "libs/json/json.h"

// superclass that holds data
#include "settings/ConfigFile.h"

namespace AWE
{
	/** \brief The type of item. **/
	enum ItemType { FOLDER_TYPE, FILE_TYPE, SERVICE_TYPE };

	/**
	 * \brief Represents a media file, folder, or service.
	 *
	 * Holds all relevant metadata for the item.
	 **/
	class MediaItem : public ConfigFile
	{
		Q_OBJECT

		public:
			/** 
			 * \brief Create from the given JSON file.
			 *
			 * \param file The JSON file path.
			 **/
			MediaItem(QString file);

			/** 
			 * \brief Destroy this object and write to file if necessary.
			 **/
			virtual ~MediaItem();

			/**
			 * \brief Get the name of the media item.
			 *
			 * \returns The name of this media item.
			 **/
			virtual QString getName() const;

			/**
			 * \brief Get the media type of the item, e.g. Movie.
			 *
			 * \returns The media type of this item.
			 **/
			virtual QString getType() const;

			/**
			 * \brief Get the description of the item.
			 *
			 * \returns The description of this item.
			 **/
			virtual QString getDescription() const;

			/**
			 * \brief Get the location for this item.
			 *
			 * For `MediaFile`s, this is the path to
			 * the actual file.
			 *
			 * For system `Folder`s this is the path
			 * to the folder on disk.
			 *
			 * For `Folder`s with a media type, this
			 * is the location of the folder that
			 * contains the sub-type files (see
			 * [the type README](../type/README.md)).
			 *
			 * For `MediaService`s, this is either the
			 * path to the program (for JSON services)
			 * or the path to the plugin.
			 *
			 * \returns The location for this item.
			 **/
			virtual QString getLocation() const;

			/**
			 * \brief Get the number of icons.
			 *
			 * \returns The number of icons.
			 **/
			virtual int numIcons() const;

			/**
			 * \brief Get the `i`th icon.
			 *
			 * \returns The `i`th icon.
			 **/
			virtual QPixmap getIcon(int i) const;

			/**
			 * \brief Get the default icon for this item, as an image.
			 *
			 * \returns The default icon image.
			 **/
			virtual QPixmap getDefaultIcon() const;

			/**
			 * \brief Get the default icon image's index.
			 *
			 * \returns The default icon image's index.
			 **/
			virtual int getDefaultIconIndex() const;

			/**
			 * \brief Get the number of icons.
			 *
			 * \returns The number of icons.
			 **/
			virtual int numFanarts() const;

			/**
			 * \brief Get the `i`th fanart.
			 *
			 * \returns The `i`th fanart.
			 **/
			virtual QPixmap getFanart(int i) const;

			/**
			 * \brief Get the default fanart for this item, as an image.
			 *
			 * \returns The default fanart image.
			 **/
			virtual QPixmap getDefaultFanart() const;

			/**
			 * \brief Get the default fanart image's index.
			 *
			 * \returns The default fanart image's index.
			 **/
			virtual int getDefaultFanartIndex() const;

			/**
			 * \brief Get the number of icons.
			 *
			 * \returns The number of icons.
			 **/
			virtual int numDetails() const;

			/**
			 * \brief Get the name of the `i`th detail.
			 *
			 * \param i The position of the detail name to get.
			 *
			 * \returns The name of the `i`th detail.
			 **/
			virtual QString getDetailName(int i) const;

			/**
			 * \brief Get the value of the `i`th detail.
			 *
			 * If there is no such detail, this function returns
			 * a null `Json::Value`.
			 *
			 * \param i The position of the detail value to get.
			 *
			 * \returns The value of the `i`th detail.
			 **/
			virtual const Json::Value& getDetailValue(int i) const;

			/**
			 * \brief Get the value of the `i`th detail as
			 *			a formatted string.
			 *
			 * If there is no such detail, this function returns
			 * a null `QString`.
			 *
			 * \param i The position of the detail value to get.
			 *
			 * \returns The value of the `i`th detail as a formatted
			 *			string.
			 **/
			virtual QString getDetailValueAsString(int i) const;

			/**
			 * \brief Determine if this item has the given detail.
			 *
			 * \param detail The name of the detail to look for.
			 *
			 * \returns `true` if this item has that detail,
			 *			`false` otherwise.
			 **/
			virtual bool hasDetail(QString detail) const;

			/**
			 * \brief Get the value for the detail with the
			 *			given name.
			 *
			 * If there is no such detail, this function returns
			 * a null `Json::Value`.
			 *
			 * \param name The name of the detail.
			 *
			 * \returns The corresponding value.
			 **/
			virtual const Json::Value& getDetailValue(QString name) const;

			/**
			 * \breif Get the value for the detail with the
			 *			given name as a string.
			 *
			 * If there is no such detail, this function returns
			 * a null `QString`.
			 *
			 * \param name The name of the detail.
			 *
			 * \returns The corresponding value, in a formatted string.
			 **/
			virtual QString getDetailValueAsString(QString name) const;

			/**
			 * \brief Determine the basic type (folder, file, service)
			 *
			 * \returns The basic type of this item.
			 **/
			virtual ItemType getItemType() const = 0;

			/**
			 * \brief Determine if this item has been edited.
			 *
			 * \returns `true` if this item has been edited,
			 *			`false` otherwise.
			 **/
			virtual bool hasBeenEdited() const;

		public slots:
			/** 
			 * \brief Mark this item as edited, so that it
			 *			is written to file upon deletion.
			 **/
			virtual void markAsEdited();

			/**
			 * \brief Refresh this item's information to
			 *			match the backend changes.
			 *
			 * This should only be called when you have altered
			 * the backend information via `getMember()`.
			 *
			 * NOTE: This does NOT mark the item as edited.
			 **/
			virtual void refresh();

			/**
			 * \brief Set the name of the media item.
			 *
			 * \param name The new name for the item.
			 **/
			virtual void setName(QString name);

			/**
			 * \brief Set the media type of the item.
			 *
			 * \param type The new media type.
			 **/
			virtual void setType(QString type);

			/**
			 * \brief Set the description of the item.
			 *
			 * \param description The new description.
			 **/
			virtual void setDescription(QString description);

			/**
			 * \brief Set the location of the item.
			 *
			 * \param location The new location.
			 **/
			virtual void setLocation(QString location);

			/**
			 * \brief Change the default icon image to the
			 *			`i`th icon.
			 *
			 * \param i The index of the new default icon.
			 *
			 * \returns `true` if `i` was a valid index,
			 *			`false` otherwise.
			 **/
			virtual bool setDefaultIconIndex(int i);

			/**
			 * \brief Add an icon for this item, but do not
			 *			import the image.
			 *
			 * `file` could be stored locally or it could
			 * be online. If stored locally, you should pass
			 * the absolute path to the image file.
			 *
			 * \param file The new icon file.
			 *
			 * \returns `true` if `file` is valid, and thus
			 *			the icon was added, `false` if not.
			 **/
			virtual bool addIcon(QString file);

			/**
			 * \brief Add and import the given icon.
			 *
			 * `file` could be stored locally or it could
			 * be online. If stored locally, you should pass
			 * the absolute path to the image file.
			 *
			 * \param file The new icon file.
			 *
			 * \returns `true` if `file` is valid, and thus
			 *			the icon was added, `false` if not.
			 **/
			virtual bool importIcon(QString file);

			/**
			 * \brief Add an icon for this item.
			 *
			 * Since this takes a `QPixmap`, the item
			 * is imported.
			 *
			 * \param icon The new icon.
			 *
			 * \returns `true` if `icon` is valid and was added,
			 *			`false` if not.
			 **/
			virtual bool addIcon(QPixmap icon);

			/**
			 * \brief Add and import the given icon.
			 *
			 * Exactly the same as `addIcon(icon)`.
			 *
			 * \param icon The new icon.
			 *
			 * \returns `true` if `icon` is valid and was added,
			 *			`false` if not.
			 **/
			virtual bool importIcon(QPixmap icon);

			/**
			 * \brief Remove the `i`th icon.
			 *
			 * \param i The index of the icon to remove.
			 *
			 * \returns `true` if `i` is a valid index,
			 *			and thus an icon was removed,
			 *			`false` otherwise.
			 **/
			virtual bool removeIcon(int i);

			/**
			 * \brief Change the default fanart image to the
			 *			`i`th fanart.
			 *
			 * \param i The index of the new default fanart.
			 *
			 * \returns `true` if `i` was a valid index,
			 *			`false` otherwise.
			 **/
			virtual bool setDefaultFanartIndex(int i);

			/**
			 * \brief Add an fanart for this item, but do not
			 *			import the image.
			 *
			 * `file` could be stored locally or it could
			 * be online. If stored locally, you should pass
			 * the absolute path to the image file. If it is
			 * from the internet, it is also imported.
			 *
			 * \param file The new fanart file.
			 *
			 * \returns `true` if `file` is valid, and thus
			 *			the fanart was added, `false` if not.
			 **/
			virtual bool addFanart(QString file);

			/**
			 * \brief Add and import the given fanart.
			 *
			 * `file` could be stored locally or it could
			 * be online. If stored locally, you should pass
			 * the absolute path to the image file.
			 *
			 * \param file The new fanart file.
			 *
			 * \returns `true` if `file` is valid, and thus
			 *			the fanart was added, `false` if not.
			 **/
			virtual bool importFanart(QString file);

			/**
			 * \brief Add an fanart for this item.
			 *
			 * Since this takes a `QPixmap`, the item
			 * is imported.
			 *
			 * \param fanart The new fanart.
			 *
			 * \returns `true` if `fanart` is valid and was added,
			 *			`false` if not.
			 **/
			virtual bool addFanart(QPixmap fanart);

			/**
			 * \brief Add and import the given fanart.
			 *
			 * Exactly the same as `addIcon(fanart)`.
			 *
			 * \param fanart The new fanart.
			 *
			 * \returns `true` if `fanart` is valid and was added,
			 *			`false` if not.
			 **/
			virtual bool importFanart(QPixmap fanart);

			/**
			 * \brief Remove the `i`th fanart.
			 *
			 * \param i The index of the fanart to remove.
			 *
			 * \returns `true` if `i` is a valid index,
			 *			and thus a fanart was removed,
			 *			`false` otherwise.
			 **/
			virtual bool removeFanart(int i);

			/**
			 * \brief Add a new detail with name `name` and
			 *			value `value`.
			 *
			 * If `name` is already a detail, then the
			 * corresponding value is set to `value`.
			 *
			 * When a detail is "set", what actually happens
			 * depends on the type of the detail:
			 *	- Array: appends the new value to the array
			 *	- Object: does nothing, because objects are
			 *				not supported.
			 *	- Everything else: replaces the old value
			 *
			 * \param name The name of the detail.
			 * \param value The value of the detail.
			 *
			 * \returns `true` if this item was changed,
			 *			`false` otherwise.
			 **/
			virtual bool addDetail(QString name, QString value);

			/**
			 * \brief Add a new detail with the name `name` and
			 *			value `value`.
			 *
			 * This function will accept `int`, `bool`, `std::string`,
			 * `char*`, and a whole host of other things.
			 *
			 * If `name` is already a detail, then the
			 * corresponding value is set to `value`.
			 *
			 * When a detail is "set", what actually happens
			 * depends on the type of the detail:
			 *	- Array: appends the new value to the array
			 *	- Object: does nothing, because objects are
			 *				not supported.
			 *	- Everything else: replaces the old value
			 *
			 * \param name The name of the detail.
			 * \param value The value of the detail.
			 *
			 * \returns `true` if this item was changed,
			 *			`false` otherwise.
			 **/
			virtual bool addDetail(QString name, const Json::Value& value);

			/**
			 * \brief Remove the `i`th detail.
			 *
			 * \param i The index of the detail to remove.
			 *
			 * \returns `true` if this item was changed,
			 *			`false` if not.
			 **/
			virtual bool removeDetail(int i);

			/**
			 * \brief Remove the detail with the given name.
			 *
			 * \param name The name of the detail to remove.
			 *
			 * \returns `true` if this item was changed,
			 *			`false` if not.
			 **/
			virtual bool removeDetail(QString name);

		signals:
			/**
			 * \brief Sent when the name is changed.
			 *
			 * \param name The new name.
			 **/
			void nameChanged(QString name);

			/**
			 * \brief Sent when the media type is changed.
			 *
			 * \param type The new media type.
			 **/
			void typeChanged(QString type);

			/**
			 * \brief Sent when the description is changed.
			 *
			 * \param description The new description.
			 **/
			void descriptionChanged(QString description);

			/**
			 * \brief Sent when the location is changed.
			 *
			 * \param location The new location.
			 **/
			void locationChanged(QString location);

			/**
			 * \brief Sent when an icon is added.
			 *
			 * \param icon The added icon.
			 **/
			void iconAdded(QPixmap icon);

			/**
			 * \brief Sent when an icon is removed.
			 *
			 * \param index The index of the removed icon.
			 **/
			void iconRemoved(int index);

			/**
			 * \brief Sent when the default icon is changed.
			 *
			 * \param index The new default icon index.
			 **/
			void defaultIconChanged(int index);

			/**
			 * \brief Sent when a fanart image is added.
			 *
			 * \param fanart The added fanart image.
			 **/
			void fanartAdded(QPixmap fanart);

			/**
			 * \brief Sent when a fanart image is removed.
			 *
			 * \param index The index of the removed fanart.
			 **/
			void fanartRemoved(int index);

			/**
			 * \brief Sent when the default fanart is changed.
			 *
			 * \param index The new default fanart index.
			 **/
			void defaultFanartChanged(int index);

			/**
			 * \brief Sent when a detail is added.
			 *
			 * \param name The name of the detail.
			 * \param value The value for the detail.
			 **/
			void detailAdded(QString name);

			/**
			 * \brief Sent when the value of a detail is changed.
			 *
			 * \param index The index of the detail.
			 **/
			void detailChanged(int index);

			/**
			 * \brief Sent when a detail is removed.
			 *
			 * \param index The index of the removed detail.
			 **/
			void detailRemoved(int index);

			/**
			 * \brief Sent when the item is refreshed.
			 **/
			void refreshed();

		private:
			/** 
			 * \brief Helper function that makes details into strings. 
			 *
			 * This is the way it is converted:
			 *	- null becomes `""`
			 *	- strings stay what they are
			 *	- `int`s become the string representation
			 *	- `bool`s become `"Yes"` or `"No"`
			 *	- arrays become a comma separated list of the strings
			 *		for their members
			 *	- objects become `""` (they are not supported)
			 *
			 * \param val The value to make a string for.
			 **/
			QString stringFor(const Json::Value& val) const;

			/** \brief The JSON file for this item. **/
			QDir myConfigFile;

			/** \brief The data for this item. **/
			Json::Value myData;

			/** \brief Determines if this should be written to file or not. **/
			bool myHasBeenEdited;

			/** \brief The name of this item. **/
			QString myName;

			/** \brief The media type of this item. **/
			QString myType;

			/** \brief The description of this item. **/
			QString myDescription;

			/** \brief The location of this item. **/
			QString myLocation;

			/** \brief The icon images for this item. **/
			QList<QPixmap> myIconImages;

			/** \brief The default icon index. **/
			int myDefaultIconIndex;

			/** \brief The fanart images for this item. **/
			QList<QPixmap> myFanartImages;

			/** \brief The default fanart index. **/
			int myDefaultFanartIndex;

			/** \brief The detail names for this item. **/
			QList<QString> myDetailNames;
	};
}

#endif