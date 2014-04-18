// class header
#include "AWEJSONScraper.h"

// for reading and writing
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>
#include <iostream>
#include <fstream>

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace Json;
using namespace std;

JSONScraper::JSONScraper(const string& name,
		const string& type) :
	myValidity(false),
	myName(name),
	myType(type),
	myCurrentFile(0)
	{ }

bool JSONScraper::prepare(GlobalSettings* settings)
{
	myScraper = settings->getScraperSettingsByName(myName);
	myDefaultProperties = settings->getTypeByName(myType);
	myValidity = checkValidity();
	return myValidity;
}

bool JSONScraper::scrapeDataForFile(MediaFile* file,
	bool askUser, bool import)
{
	// set ans to defaults
	myCurrentFile = file;
	string temp = myCurrentFile->getStringMember("metadata.location");
	myCurrentFile->getMember("metadata") = myDefaultProperties;
	myCurrentFile->getMember("metadata.location") = temp;

	// check validity
	if (!isValid())
	{
		DEBUG(cout << "Scraper \"" << getName() << "\" not valid" << endl;)
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

bool JSONScraper::executeProcedure(Value& procedure, BackrefList& backrefs,
	bool askUser, bool import)
{
	// get the file to look in and what to look for
	string lookInFile = procedure["look in file"].asString();
	string lookFor = procedure["for"].asString();
	if (!replaceBackrefs(lookInFile, backrefs)
		|| !replaceBackrefs(lookFor, backrefs))
	{
		return false;
	}

	// get the contents of the file
	stringstream fileContents;
	copyFile(lookInFile, fileContents);

	BackrefList list;
	bool called = false;
	bool procsSucceeded = true;
	// repetitive (i.e. array-filling) procedure
	if (procedure["repeat"].asBool())
	{
		// for every match
		string s = fileContents.str();
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

bool JSONScraper::useMatchForProcedure(Value& procedure,
	BackrefList& backrefs, bool askUser, bool import)
{
	bool procsSucceeded = true;

	// apply to the properties in this procedure
	Value::Members mems = procedure.getMemberNames();
	Value::Members::iterator it = mems.begin();
	for (auto prop : mems)
	{
		if (prop != "look in file" && prop != "for" 
			&& prop != "repeat" && prop != "procedures"
			&& prop != "ask user")
		{
			// determine what type it is
			Value valueToSet;
			if (procedure[prop].isString()) // string implies backrefs
			{
				// replace backrefs in the value
				string temp = procedure[prop].asString();
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
			Value* toSet = &(myCurrentFile->getMember(
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

void JSONScraper::deactivate()
{
	myScraper = Value::null;
	myDefaultProperties = Value::null;
}

bool JSONScraper::getBackrefs(const string& search, const string& reg,
	BackrefList& backrefs)
{
	// initialize the regex
	regex r(reg);

	// get the matches (only care about the first)
	return regex_search(search, backrefs, r);
}

bool JSONScraper::replaceBackrefs(string& pseudo_reg, 
	const BackrefList& backrefs)
{
	pseudo_reg = backrefs.format(pseudo_reg);

	// always a success (AFAICT)
	return true;
}

bool JSONScraper::isValid()
{
	return myValidity;
}

bool JSONScraper::checkValidity()
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

bool JSONScraper::checkProcedureValidity(Value& procedure)
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

const string& JSONScraper::getName()
{
	return myName;
}

const string& JSONScraper::getType()
{
	return myType;
}