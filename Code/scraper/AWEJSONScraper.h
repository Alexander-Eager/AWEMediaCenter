#ifndef AWE_JSON_SCRAPER_H
#define AWE_JSON_SCRAPER_H

// the superclass
#include "AWEMetadataScraper.h"

// for global settings and data
#include "settings/AWEGlobalSettings.h"

// for reading/writing JSON files for the scraper and media file
#include "libs/json/json.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

// for holding data
#include <QString>
#include <QHash>
#include <QSet>

// for media items
#include "items/AWEMediaItem.h"
#include "items/AWEFolder.h"

namespace AWE
{
	/**
	 * \brief A metadata scraper based on JSON files.
	 *
	 * \todo Change `myType` to be the mystical know-all configuration object.
	 *
	 * One way of defining a scraper is through a JSON file interpreted by an
	 * instantiation of this class. To read more about the format of such a JSON file,
	 * read [this document](README.md).
	 *
	 * For information on media types, read [this document](../type/README.md).
	 **/
	class JSONScraper : public MetadataScraper
	{
		public:
			/** 
			 * \brief Construct a new JSON-based scraper from the given name.
			 *
			 * \param[in] name The name of the scraper.
			 * \param[in] type The media type for this scraper.
			 **/
			JSONScraper(QString name, QString type);

			/**
			 * \brief Prepares the scraper by reading the scraper and type files.
			 *
			 * This helps with memory management.
			 *
			 * \param[in] settings The [global settings of AWEMC](../settings/README.md).
			 *
			 * \returns `true` if the scraper was able to prepare itself,
			 *			`false` if an error occured and scraping should be
			 *			aborted. Generally, a `false` result here means that
			 *			the JSON file was incorrectly written.
			 **/
			virtual bool prepare(GlobalSettings* settings);

			/**
			 * \brief Retrieves metadata for a media file.
			 *
			 * To construct your JSON file, you should use 
			 * [jsoncpp](http://jsoncpp.sourceforge.net).
			 *
			 * `askUser` tells your scraper if the user wants to be
			 * given a list of choices for certain things. You should 
			 * NOT ask the user for everything if `askUser` is true;
			 * only basic things like, "Which icon do you want to use?"
			 *
			 * `import` specifies if the files you get should be
			 * copied into AWEMC's folders. Do NOT copy the media file.
			 *
			 * \todo boolean flags
			 *
			 * \param[inout] file The media file to get metadata for.
			 * \param[in] askUser `true` if the user wants to be given choices,
			 *				`false` otherwise.
			 * \param[in] import `true` if the user wants to import metadata files,
			 *				`false` otherwise.
			 * \param[in] inheritMetadata `true` if designated metadata items should
			 *								be inherited from the containing folder,
			 *								`false` otherwise.
			 *
			 * \returns `true` if the scraper was able to get the metadata,
			 *			`false` if it was not.
			 **/
			virtual bool scrapeDataForFile(MediaItem* file,
				bool askUser, bool import, bool inheritMetadata);

			/**
			 * \brief Create a media item (or multiple if applicable) from a
			 *			given file or folder.
			 *
			 * To construct your JSON file, you should use 
			 * [JsonCpp](http://jsoncpp.sourceforge.net).
			 *
			 * `askUser` tells your scraper if the user wants to be
			 * given a list of choices for certain things. You should 
			 * NOT ask the user for everything if `askUser` is true;
			 * only basic things like, "Which icon do you want to use?"
			 *
			 * `import` specifies if the files you get should be
			 * copied into AWEMC's folders. Do NOT copy the media file.
			 *
			 * `inheritMetadata` determines if data that could be inherited from 
			 * the folder should be.
			 *
			 * \todo boolean flags
			 *
			 * \param[out] placeInMe The `Folder` to put the created items in.
			 * \param[in] file The file or folder to get media items for.
			 * \param[in] globalSettings The global settings of AWEMC.
			 * \param[in] askUser `true` if the user wants to be given choices,
			 *				`false` otherwise.
			 * \param[in] import `true` if the user wants to import metadata files,
			 *				`false` otherwise.
			 * \param[in] inheritMetadata `true` if designated metadata items should
			 *								be inherited from the containing folder,
			 *								`false` otherwise.
			 *
			 * \returns A list of media items for the given file. The list is empty if
			 *			the file does not match.
			 **/
			virtual QList<MediaItem*> scrapeDataForFile(Folder* placeInMe,
				GlobalSettings* globalSettings, QDir file,
				bool askUser, bool import, bool inheritMetadata);

			/**
			 * \brief Destroys any used-up dynamic memory.
			 *
			 * This helps with memory management.
			 **/
			virtual void deactivate();

			/**
			 * \brief Determines if this is scraper can be used.
			 *
			 * \returns `true` if this scraper can be used successfully,
			 *			`false` otherwise.
			 **/
			virtual bool isValid();

			/**
			 * \brief Gets the name of the scraper.
			 *
			 * \returns The name of the scraper.
			 **/
			virtual QString getName();

			/**
			 * \brief Gets the media type for this scraper.
			 *
			 * \returns The media type name for the scraper.
			 **/
			virtual QString getType();

		private:
			/** \brief Can this be used effectively? **/
			bool myValidity;

			/** \brief Name of the scraper. **/
			QString myName;

			/** \brief The type of the scraper. **/
			QString myType;

			/** \brief The data determining how to scrape. **/
			Json::Value myScraper;

			/** \brief The global settings. **/
			Json::Value myDefaultProperties;

			/** \brief The current file. **/
			MediaItem* myCurrentFile;

			/** \brief The folder contianing myCurrentFile. **/
			Folder* myCurrentFolder;

			/** \brief The global settings of AWEMC. **/
			GlobalSettings* myGlobalSettings;

			/** \brief Maps file onto file contents (for speed boost). **/
			QHash<QString, QString> myMetadataFiles;

			/** \brief Maps `myCurrentFile` props onto `myCurrentFolder` props. **/
			QHash<QString, QString> myInheritedProperties;

			/** \brief Set of file properties. **/
			QSet<QString> myFileProperties;

			/**
			 * \brief Execute a specific procedure from a `"procedures"` array.
			 *
			 * \param[in] procedure The procedure to execute.
			 * \param[in] backrefs The backreferences to use on the `"look in file"`
			 *				and `"for"` tags.
			 * \param[in] askUser `true` if the user wants semi-automatic scraping,
			 *						`false` if completely automatic.
			 * \param[in] import `true` if the user wants to import files,
			 *						`false` if the user wants links.
			 * \param[in] inheritMetadata `true` if designated metadata items should
			 *								be inherited from the containing folder,
			 *								`false` otherwise.
			 *
			 * \returns `true` if the procedure ran without issue, `false` otherwise.
			 **/
			bool executeProcedure(Json::Value& procedure, QRegularExpressionMatch backrefs,
				bool askUser, bool import, bool inheritMetadata);

			/**
			 * \brief Helper function that sets properties and executes sub-procedures.
			 *
			 * \param[in] procedure The procedure describing the properties and
			 *				sub-procedures.
			 * \param[in] backrefs The backreferences to use on the properties tags.
			 * \param[in] askUser `true` if the user wants semi-automatic scraping,
			 *						`false` if completely automatic.
			 * \param[in] import `true` if the user wants to import files,
			 *						`false` if the user wants links.
			 * \param[in] inheritMetadata `true` if designated metadata items should
			 *								be inherited from the containing folder,
			 *								`false` otherwise.
			 *
			 * \returns `true` if the procedure ran without issue, `false` otherwise.
			 **/
			bool useMatchForProcedure(Json::Value& procedure, QRegularExpressionMatch backrefs,
				bool askUser, bool import, bool inheritMetadata);

			/**
			 * \brief Helper function that imports the files in the given `Json::Value`.
			 *
			 * This is used for the `"force copy"` and `"copy"` tags.
			 *
			 * \param[in] props The properties that contain files to import.
			 **/
			void importFiles(Json::Value& props);

			/**
			 * \brief Replace the backreferences in `pseudo_reg` with the references from
			 *			`backrefs`.
			 *
			 * `pseudo_reg` should be formatted according to 
			 * [this function's](http://www.cplusplus.com/reference/regex/match_replace/)
			 * `fmt` parameter.
			 *
			 * \param[out] pseudo_reg The `QString` with the references to replace.
			 * \param[in] backrefs The backreferences to use.
			 *
			 * \returns The highest backref requested.
			 **/
			int replaceBackrefs(QString& pseudo_reg, QRegularExpressionMatch backrefs);

			/**
			 * \brief Get the contents of a file, either from the already opened files
			 *			or a new file.
			 *
			 * \param[in] file The file to get the contents for.
			 *
			 * \returns The contents of `file`.
			 **/
			QString& getFileContents(QString file);

			/**
			 * \brief Does a test run of the procedures to decide if this scraper is valid.
			 *
			 * \todo This entire function (which at the moment just returns `true`)
			 *
			 * \returns `true` if this scraper is safe to use, `false` otherwise.
			 **/
			bool checkValidity();

			/**
			 * \brief Does a test run of a procedure to decide if it is valid.
			 *
			 * \todo This entire function (which at the moment just returns `true`)
			 *
			 * \param[in] procedure The procedure to check.
			 * \param[in] capCount The number of backrefs passed to the procedure.
			 *
			 * \returns `true` if `procedure` is safe to use, `false` otherwise.
			 **/
			bool checkProcedureValidity(Json::Value& procedure, int capCount);
	};
}

#endif