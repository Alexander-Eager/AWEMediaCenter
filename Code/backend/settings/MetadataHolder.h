#ifndef METADATA_HOLDER_H
#define METADATA_HOLDER_H

// for the library
#include "macros/BackendLibraryMacros.h"

// for holding data
#include <QString>
#include <QPixmap>
#include "ConfigFile.h"

// for holding settings data
#include <JsonDataTree/Json.h>

namespace AWE
{
	// internal data
	class MetadataHolderPrivate;

	/**
	 * \brief Represents anything that has metadata.
	 *
	 * In AWEMC, this includes files, folders, services,
	 * scrapers, and even media types.
	 *
	 * "Metadata," in the context of AWEMC, includes
	 * icon images, fanart images, details, and a few
	 * standalone infos like name and description. In the
	 * future, this could be expanded to include any number
	 * of things, which makes this class extremely useful.
	 **/
	class AWEMC_BACKEND_LIBRARY MetadataHolder : public QObject
	{
		Q_OBJECT

		Q_PROPERTY(QString name
			READ getName
			WRITE setName
			NOTIFY nameChanged)
		Q_PROPERTY(QString type
			READ getType
			WRITE setType
			NOTIFY typeChanged)
		Q_PROPERTY(QString description
			READ getDescription
			WRITE setDescription
			NOTIFY descriptionChanged)
		Q_PROPERTY(QString location
			READ getLocation
			WRITE setLocation
			NOTIFY locationChanged)
		Q_PROPERTY(int numIcons
			READ numIcons
			STORED false)
		Q_PROPERTY(int numFanarts
			READ numFanarts
			STORED false)
		Q_PROPERTY(int numDetails
			READ numDetails
			STORED false)

		public:
			/** 
			 * \brief Create from the given JSON file.
			 *
			 * \param file The JSON file path.
			 **/
			MetadataHolder(QString file);

			/**
			 * \brief Create from the given config file.
			 *
			 * `file` is transferred over to this metadata
			 * holder's ownership; deleting `file` will
			 * cause issues. The newly created
			 * `MetadataHolder` object will delete the file
			 * itself.
			 *
			 * \param file The configuration file.
			 **/
			MetadataHolder(ConfigFile* file);

			/** 
			 * \brief Destroy this object.
			 **/
			virtual ~MetadataHolder();

			/**
			 * \brief Get the name of the item.
			 *
			 * \returns The name of this item.
			 **/
			virtual QString getName() const;

			/**
			 * \brief Get the media type of the item, e.g. `"Movie"`.
			 *
			 * What this means to the object depends on the subclass.
			 * For files, folders, and services, this is an indication
			 * of default metadata values and other such things. For
			 * folder generators, this represents the type of item
			 * the folder generator works on, and similarly scrapers
			 * also take the type of the item they work on. Media players
			 * have a more generic type name based on what they generally
			 * play. For example, VLC would likely say `"Video"`
			 * or `"Multimedia"`, while an NES emulator would say `"Video Games"`
			 * or maybe more specifically `"NES"`.
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
			 * For `MetadataScraper`s, `MediaPlayer`s,
			 * and `MediaService`s, this is the
			 * path to the plugin that creates the
			 * object.
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
			 * \param i The icon to get.
			 *
			 * \returns The `i`th icon.
			 **/
			virtual QPixmap getIcon(int i) const;

			/**
			 * \brief Get the `i`th icon file.
			 *
			 * \param i The icon file to get.
			 *
			 * \returns The `i`th icon file.
			 **/
			virtual QString getIconFile(int i) const;

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
			 * \param i The fanart to get.
			 *
			 * \returns The `i`th fanart.
			 **/
			virtual QPixmap getFanart(int i) const;

			/**
			 * \brief Get the `i`th fanart file.
			 *
			 * \param i The fanart file to get.
			 *
			 * \returns The `i`th fanart file.
			 **/
			virtual QString getFanartFile(int i) const;

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
			virtual JSON::JsonValue getDetailValue(int i) const;

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
			virtual JSON::JsonValue getDetailValue(QString name) const;

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

		public slots:
			/**
			 * \brief Set the name of the item.
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
			 * \brief Add a new detail with the name `name` and
			 *			value `value`.
			 *
			 * This function will accept `int`, `bool`, `QString`,
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
			 **/
			virtual void addDetail(QString name, JSON::JsonValue value);

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
			 * \brief Sent when the value of a detail is changed.
			 *
			 * \param name The name of the changed detail.
			 **/
			void detailChanged(QString name);

			/**
			 * \brief Sent when a detail is removed.
			 *
			 * \param index The index of the removed detail.
			 **/
			void detailRemoved(int index);

			/**
			 * \brief Sent when a detail is removed.
			 *
			 * \param name The name of the removed detail.
			 **/
			void detailRemoved(QString name);

		protected:
			/**
			 * \brief Get the configuration file.
			 *
			 * \returns the configuration file.
			 **/
			virtual ConfigFile* getConfigFile();

		private:
			/** \brief Internal data. **/
			MetadataHolderPrivate* d;
	};
}

#endif // METADATA_HOLDER_H