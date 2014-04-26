// header file
#include "AWEMediaType.h"

// for scraping for data
#include "scraper/AWEMetadataScraper.h"

// for adding to the folder structure
#include "items/AWEFolder.h"
#include "items/AWEMediaFile.h"

// for general settings
#include "settings/AWEGlobalSettings.h"

// for editing files
#include "libs/generic_file_reader/file_reader.h"

// for temporary data storage
#include <deque>

using namespace std;
using namespace AWE;
using namespace Json;

FolderGenerator::FolderGenerator(const QDir& file) :
	myJSONFile(file)
{
	// read in the file
	myJSONFile = file;
	Reader reader;
	Value data;
	stringstream ss;
	copyFile(file.absolutePath().toStdString(), ss);
	reader.parse(ss.str(), data, false);

	// get the metadata defaults
	myMetadata = data["metadata"];

	// set the folder/file flag
	myItemsAreFolders = (data["type"].asString() == "folder");

	// get file filters
	for (uint i = 0; i < data["matching files"].size(); ++ i)
	{
		myFileFilters << data["matching files"][i];
	}

	// get all of the sub generators
	for (uint i = 0; i < data["contains"].size(); ++ i)
	{
		mySubGenerators.push_back(
			new FolderGenerator(data["contains"][i], myFileFilters));
	}
}

FolderGenerator::FolderGenerator(Value& data) :
	myMetadata(data["metadata"])
{
	// get all of the sub generators
	for (uint i = 0; i < data["contains"].size(); ++ i)
	{
		mySubGenerators.push_back(
			new FolderGenerator(data["contains"][i]));
	}
}

string FolderGenerator::getType() const
{
	return myMetadata["type"];
}

Value& FolderGenerator::getDefaultMetadata()
{
	return myMetadata;
}

vector<FolderGenerator*>& FolderGenerator::getSubGenerators()
{
	return mySubGenerators;
}

// TODO
bool FolderGenerator::createFolderStructure(Folder* root, const QDir& dir,
	vector<MetadataScraper*>& scrapersToUse, GlobalSettings* settings,
	bool askUser, bool importFiles, bool inheritMetadata)
{
	bool ans = true;

	// set filters to the stuff we care about
	QDir searchDir = dir;
	QDir rootDir = root->getJSONFile();
	rootDir.cdUp();
	searchDir.setNameFilters(myFileFilters);
	if (myFilesAreFolders)
	{
		searchDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	}
	else
	{
		searchDir.setFilter(QDir::Files);
	}
	// get them
	for (uint i = 0; i < searchDir.count(); ++ i)
	{
		AWEMediaFile* file =
			new AWEMediaFile(QDir(rootDir.absoluteFilePath(searchDir[i]) + ".json"),
								settings);
		
	}
}