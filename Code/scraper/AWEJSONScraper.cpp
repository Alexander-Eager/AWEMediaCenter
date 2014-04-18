// class header
#include "AWEJSONScraper.h"

// for reading and writing
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>
#include <iostream>
#include <fstream>

// debug
#include "debug_macros/debug.h"

AWEJSONScraper::AWEJSONScraper(const std::string& name,
		const std::string& type) :
	myValidity(false),
	myName(name),
	myType(type),
	myCurrentFile(0)
	{ }

bool AWEJSONScraper::prepare(AWEGlobalSettings* settings)
{
	myScraper = settings->getScraperSettingsByName(myName);
	myDefaultProperties = settings->getTypeByName(myType);
	myValidity = checkValidity();
	return myValidity;
}

bool AWEJSONScraper::scrapeDataForFile(AWEMediaFile* file,
	bool askUser, bool import)
{
	// set ans to defaults
	myCurrentFile = file;
	std::string temp = myCurrentFile->getStringMember("metadata.location");
	myCurrentFile->getMember("metadata") = myDefaultProperties;
	myCurrentFile->getMember("metadata.location") = temp;

	// check validity
	if (!isValid())
	{
		DEBUG(std::cout << "Scraper \"" << getName() << "\" not valid" << std::endl;)
		return false;
	}

	// get the backrefs for the filename
	BackrefList backrefs;
	if (!getBackrefs(temp, myScraper["filename"].asString(), backrefs))
	{
		return false;
	}

	// run through the procedures, noting issues
	bool procsSucceeded = true;
	for (unsigned int i = 0; i < myScraper["procedures"].size(); ++ i)
	{
		procsSucceeded = procsSucceeded 
			&& executeProcedure(myScraper["procedures"][i], backrefs,
				askUser, import);
	}

	// reset the file variable
	myCurrentFile = 0;

	// return the success/failure
	return procsSucceeded;
}

bool AWEJSONScraper::executeProcedure(Json::Value& procedure, BackrefList& backrefs,
	bool askUser, bool import)
{
	// get the file to look in and what to look for
	std::string lookInFile = procedure["look in file"].asString();
	std::string lookFor = procedure["for"].asString();
	if (!replaceBackrefs(lookInFile, backrefs)
		|| !replaceBackrefs(lookFor, backrefs))
	{
		return false;
	}

	// get the contents of the file
	std::stringstream fileContents;
	copyFile(lookInFile, fileContents);

	BackrefList list;
	bool called = false;
	bool procsSucceeded = true;
	// repetitive (i.e. array-filling) procedure
	if (procedure["repeat"].asBool())
	{
		// for every match
		std::string s = fileContents.str();
		while (getBackrefs(s, lookFor, list))
		{
			// do the necessary stuff with this result
			procsSucceeded = procsSucceeded
					&& useMatchForProcedure(procedure, list, askUser, import);
			s = list.suffix().str();
			called = true;
		}
		if (!called)
		{
			return false;
		}
	}
	// not repetitive
	else
	{
		if (!getBackrefs(fileContents.str(), lookFor, list))
		{
			return false;
		}
		procsSucceeded = useMatchForProcedure(procedure, list, askUser, import);
	}

	// return success/failure
	return procsSucceeded;
}

bool AWEJSONScraper::useMatchForProcedure(Json::Value& procedure,
	BackrefList& backrefs, bool askUser, bool import)
{
	bool procsSucceeded = true;

	// apply to the properties in this procedure
	Json::Value::Members mems = procedure.getMemberNames();
	Json::Value::Members::iterator it = mems.begin();
	for (auto prop : mems)
	{
		if (prop != "look in file" && prop != "for" 
			&& prop != "repeat" && prop != "procedures"
			&& prop != "ask user")
		{
			// determine what type it is
			Json::Value valueToSet;
			if (procedure[prop].isString()) // string implies backrefs
			{
				// replace backrefs in the value
				std::string temp = procedure[prop].asString();
				if (!replaceBackrefs(temp, backrefs))
				{
					return false;
				}
				valueToSet = temp;
			}
			else
			{
				valueToSet = procedure[prop];
			}

			// parse the property name to delve down objects
			Json::Value* toSet = &(myCurrentFile->getMember(
									"metadata." + prop));

			// set the object in the appropriate way
			if (toSet->isArray())
			{
				// append to the array
				toSet->append(valueToSet);
			}
			else // something else
			{
				// replace the current value
				toSet->operator= (valueToSet);
			}
		}
		++ it;
	}

	// apply to the sub procedures
	for (unsigned int j = 0; j < procedure["procedures"].size(); ++ j)
	{
		procsSucceeded = procsSucceeded 
			&& executeProcedure(procedure["procedures"][j],
				backrefs, askUser, import);
	}

	return procsSucceeded;
}

void AWEJSONScraper::deactivate()
{
	myScraper = Json::Value::null;
	myDefaultProperties = Json::Value::null;
}

bool AWEJSONScraper::getBackrefs(const std::string& search, const std::string& reg,
	BackrefList& backrefs)
{
	// initialize the regex
	std::regex r(reg);

	// get the matches (only care about the first)
	return regex_search(search, backrefs, r);
}

bool AWEJSONScraper::replaceBackrefs(std::string& pseudo_reg, 
	const BackrefList& backrefs)
{
	pseudo_reg = backrefs.format(pseudo_reg);

	// always a success (AFAICT)
	return true;
}

bool AWEJSONScraper::isValid()
{
	return myValidity;
}

bool AWEJSONScraper::checkValidity()
{
	// if true, we assume its good
	if (myValidity)
	{
		return true;
	}
	// doesn't have the necessary tags
	if (!myScraper.isMember("filename") || !myScraper["filename"].isString()
		|| !myScraper.isMember("type") || !myScraper["type"].isString()
		|| !myScraper.isMember("procedures") || !myScraper["procedures"].isArray()
		|| !myScraper.isMember("force copy") || !myScraper["force copy"].isArray()
		|| !myScraper.isMember("copy") || !myScraper["copy"].isArray())
	{
		return false;
	}
	// check each procedure
	for (unsigned int i = 0; i < myScraper["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(myScraper["procedures"][i]))
		{
			// bad procedure
			return false;
		}
	}
	// all is well
	return true;
}

bool AWEJSONScraper::checkProcedureValidity(Json::Value& procedure)
{
	// doesn't have the necessary tags
	if (!procedure.isMember("repeat") || !procedure["repeat"].isBool()
		|| !procedure.isMember("ask user") || !procedure["ask user"].isBool()
		|| !procedure.isMember("look in file") || !procedure["look in file"].isString()
		|| !procedure.isMember("for") || !procedure["for"].isString()
		|| !procedure.isMember("procedures") || !procedure["procedures"].isArray())
	{
		return false;
	}
	// check each sub procedure
	for (unsigned int i = 0; i < procedure["procedures"].size(); ++ i)
	{
		if (!checkProcedureValidity(procedure["procedures"][i]))
		{
			// bad procedure
			return false;
		}
	}
	// all is well
	return true;
}

const std::string& AWEJSONScraper::getName()
{
	return myName;
}

const std::string& AWEJSONScraper::getType()
{
	return myType;
}