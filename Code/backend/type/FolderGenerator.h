#ifndef AWE_MEDIA_TYPE_H
#define AWE_MEDIA_TYPE_H

// for holding data
#include <QStringList>
#include <vector>
#include <string>
#include "libs/json/json.h"
#include <QDir>

namespace AWE
{
	// forward declarations
	class MetadataScraper;
	class Folder;
	class MediaItem;
	class GlobalSettings;

	/**
	 * \brief Defines a folder generator for a hierarchical
	 *			media type.
	 **/
	class FolderGenerator
	{
		public:
			/**
			 * \brief Construct from the given JSON file.
			 *
			 * \param[in] file The JSON file representing this generator.
			 **/
			FolderGenerator(QDir file);

			/**
			 * \brief Get the surface type of the generator.
			 *
			 * \returns The surface type of the generator.
			 **/
			QString getType() const;

			/**
			 * \brief Get the default metadata values.
			 *
			 * \returns The default metadata values.
			 **/
			Json::Value& getDefaultMetadata();

			/**
			 * \brief Get the generators for all contained types.
			 *
			 * \returns A list of all sub generators.
			 **/
			QList<FolderGenerator*> getSubGenerators();

			/**
			 * \brief Create a folder structure for holding this type tree.
			 *
			 * \param[out] root The folder to place the new folder structure in.
			 * \param[in] dir The directory to check for media files.
			 * \param[in] scrapersToUse Maps type names onto metadata scrapers to use.
			 * \param[in] askUser Decide if the user should be asked to help scraping.
			 * \param[in] importFiles Decide if optional file imports should occur.
			 * \param[in] inheritMetadata `true` if this generator is being called
			 *								by another, `false` otherwise.
			 *
			 * \returns `true` if all metadata was successfully obtained,
			 *			`false` otherwise.
			 **/
			bool createFolderStructure(Folder* root, QDir dir, 
				QHash<QString, MetadataScraper*>& scrapersToUse,
				bool askUser, bool importFiles, bool inheritMetadata);

			/**
			 * \brief Create the detail folders for this type.
			 *
			 * A detail folder is only created if that detail has more than one value
			 * in the item list.
			 *
			 * \param[in] itemsGenerated The items to make detail folders for.
			 * \param[out] placeInMe The folder to put all of the type folders in.
			 **/
			void makeDetailFolders(QList<MediaItem*> itemsGenerated, Folder* placeInMe);

		private:
			/** \brief The config file. **/
			QDir myJSONFile;
			/** \brief The data from the config file. **/
			Json::Value myMetadata;
			/** \brief The file filters to use when searching. **/
			QStringList myFileFilters;
			/** \brief List of all contained generators. **/
			QList<FolderGenerator*> mySubGenerators;
			/** \brief Determines if this generates folders. **/
			bool myItemsAreFolders;

			/**
			 * \brief Construct from a JSON value.
			 *
			 * \param data The JSON value for the type.
			 **/
			FolderGenerator(Json::Value& data);
	};
}

#endif