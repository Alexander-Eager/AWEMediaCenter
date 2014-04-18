#ifndef AWE_JSON_SCRAPER_H
#define AWE_JSON_SCRAPER_H

// the superclass
#include "AWEMetadataScraper.h"

// for global settings and data
#include "settings/AWEGlobalSettings.h"

// for reading/writing JSON files for the scraper and media file
#include "libs/json/json.h"
#include <regex>

// for holding data
#include <string>

/** \brief Defines a list of sub expressions **/
typedef std::smatch BackrefList;

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
class AWEJSONScraper : public AWEMetadataScraper
{
	public:
		/** 
		 * \brief Construct a new JSON-based scraper from the given name.
		 *
		 * \param[in] name The name of the scraper.
		 * \param[in] type The media type for this scraper.
		 **/
		AWEJSONScraper(const std::string& name, const std::string& type);

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
		virtual bool prepare(AWEGlobalSettings* settings);

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
		 * \todo `import` and `askUser`
		 *
		 * \param[inout] file The media file to get metadata for.
		 * \param[in] askUser `true` if the user wants to be given choices,
		 *				`false` otherwise.
		 * \param[in] import `true` if the user wants to import metadata files,
		 *				`false` otherwise.
		 *
		 * \returns `true` if the scraper was able to get the metadata,
		 *			`false` if it was not.
		 **/
		virtual bool scrapeDataForFile(AWEMediaFile* file,
			bool askUser, bool import);

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
		virtual const std::string& getName();

		/**
		 * \brief Gets the media type for this scraper.
		 *
		 * \returns The media type name for the scraper.
		 **/
		virtual const std::string& getType();

	private:
		/** \brief Can this be used effectively? **/
		bool myValidity;

		/** \brief Name of the scraper. **/
		std::string myName;

		/** \brief The type of the scraper. **/
		std::string myType;

		/** \brief The data determining how to scrape. **/
		Json::Value myScraper;

		/** \brief The data determining what properties are available. **/
		Json::Value myDefaultProperties;

		/** \brief The current file. **/
		AWEMediaFile* myCurrentFile;

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
		 *
		 * \returns `true` if the procedure ran without issue, `false` otherwise.
		 **/
		bool executeProcedure(Json::Value& procedure, BackrefList& backrefs,
			bool askUser, bool import);

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
		 *
		 * \returns `true` if the procedure ran without issue, `false` otherwise.
		 **/
		bool useMatchForProcedure(Json::Value& procedure, BackrefList& backrefs,
			bool askUser, bool import);

		/**
		 * \brief Get the backreferences resulting from searching through `search`
		 *			for the regex `reg`.
		 *
		 * \param[in] search The `std::string` to look in.
		 * \param[in] reg A `std::string` representing the 
		 *				[ECMAScript](http://www.cplusplus.com/reference/regex/ECMAScript/)
		 *				to use as the regex.
		 * \param[out] backrefs The backreferences resulting from the search.
		 *
		 * \returns `true` if a match was found, `false` otherwise.
		 **/
		bool getBackrefs(const std::string& search, const std::string& reg,
			BackrefList& backrefs);

		/**
		 * \brief Replace the backreferences in `pseudo_reg` with the references from
		 *			`backrefs`.
		 *
		 * `pseudo_reg` should be formatted according to 
		 * [this function's](http://www.cplusplus.com/reference/regex/match_replace/)
		 * `fmt` parameter.
		 *
		 * \param[out] pseudo_reg The `std::string` with the references to replace.
		 * \param[in] backrefs The backreferences to use.
		 *
		 * \returns `true` if `pseudo_reg` was formatted correctly, `false` otherwise.
		 **/
		bool replaceBackrefs(std::string& pseudo_reg, const BackrefList& backrefs);

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
		 * \param procedure The procedure to check.
		 *
		 * \returns `true` if `procedure` is safe to use, `false` otherwise.
		 **/
		bool checkProcedureValidity(Json::Value& procedure);
};

#endif