// header file
#include "FolderGenerator.h"

// for scraping for data
#include "scraper/AWEMetadataScraper.h"

// for adding to the folder structure
#include "items/AWEFolder.h"
#include "items/AWEMediaFile.h"

// for general settings
#include "AWEMC.h"

// for editing files
#include "libs/generic_file_reader/file_reader.h"

// for temporary data storage
#include <QQueue>
#include <QSet>

using namespace AWE;
using namespace Json;

FolderGenerator::FolderGenerator(QDir file) :
	myJSONFile(file)
{
	// read in the file
	myJSONFile = file;
	Reader reader;
	Value data;
	QString contents;
	QTextStream ss(&contents);
	copyFile(file.absolutePath(), ss);
	reader.parse(contents.toStdString(), data, false);

	// get the metadata defaults
	myMetadata = data["metadata"];

	// set the folder/file flag
	myItemsAreFolders = (data["type"].asString() == "folder");

	// get file filters
	for (uint i = 0; i < data["matching files"].size(); ++ i)
	{
		myFileFilters << data["matching files"][i].asCString();
	}

	// get all of the sub generators
	for (uint i = 0; i < data["contains"].size(); ++ i)
	{
		mySubGenerators.append(
			new FolderGenerator(data["contains"][i]));
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

QString FolderGenerator::getType() const
{
	return myMetadata["type"].asCString();
}

Value& FolderGenerator::getDefaultMetadata()
{
	return myMetadata;
}

QList<FolderGenerator*> FolderGenerator::getSubGenerators()
{
	return mySubGenerators;
}

bool FolderGenerator::createFolderStructure(Folder* root, QDir dir,
	QHash<QString, MetadataScraper*>& scrapersToUse,
	bool askUser, bool importFiles, bool inheritMetadata)
{
	// prepare the scrapers if this is the root item group
	if (!inheritMetadata)
	{
		for (auto scraper : scrapersToUse)
		{
			scraper->prepare(AWEMC::settings());
		}
	}

	bool ans = true;

	// get some important directories
	QDir searchDir = dir;
	QDir rootDir(root->getConfigFile().absolutePath());
	rootDir.cdUp();

	Folder* placeInMe = root;
	if (!inheritMetadata)
	{
		rootDir.mkdir("All Items");
		rootDir.cd("All Items");
		placeInMe = new Folder(rootDir.absoluteFilePath("config.json"));
		// TODO metadata (should be a settings file for auto-gen folders)
		placeInMe->getData()["metadata"]["name"] = "All Items";
		root->addItem(placeInMe);
		rootDir.cdUp();
	}

	// set the filters
	searchDir.setNameFilters(myFileFilters);
	if (myItemsAreFolders)
	{
		searchDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	}
	else
	{
		searchDir.setFilter(QDir::Files);
	}

	// get the items
	MetadataScraper* scraperForThisType = scrapersToUse[getType()];
	for (uint i = 0; i < searchDir.count(); ++ i)
	{
		// get the list of matching items for this file
		QDir currFile(searchDir.absoluteFilePath(searchDir[i]));
		QList<MediaItem*> result
			= scraperForThisType->scrapeDataForFile(placeInMe, AWEMC::settings(), currFile,
										askUser, importFiles, inheritMetadata);
		
		// if this file had no items, this function returns false
		if (result.count() == 0)
		{
			ans = false;
		}
		else if (myItemsAreFolders)
		{
			// for every folder, scrape for sub-types
			for (auto subGen : mySubGenerators)
			{
				for (int itemInd = 0; itemInd < result.count(); ++ itemInd)
				{
					QDir subDir(searchDir);
					subDir.cd(searchDir[i]);
					ans = ans && subGen->createFolderStructure((Folder*) result.takeAt(itemInd),
							subDir, scrapersToUse, askUser, importFiles, true);
				}
			}
		}
	}

	// if this is the root item group
	if (!inheritMetadata)
	{
		// deactivate the scrapers
		for (auto scraper : scrapersToUse)
		{
			scraper->deactivate();
		}

		// also, create the category folders using the type data
		makeDetailFolders(placeInMe->getItems(), root);
	}

	return ans;
}

// TODO what if the folders already exist? How do we deal with deletion of folders?
void FolderGenerator::makeDetailFolders(QList<MediaItem*> itemsGenerated, Folder* placeInMe)
{
	QDir rootDir(placeInMe->getConfigFile().absolutePath());
	rootDir.cdUp();
	Value::Members details = myMetadata["details"].getMemberNames();
	for (auto key : details)
	{
		// we don't want to do anything for _order
		if (key == "_order")
		{
			continue;
		}

		// create a map of detail value onto items that have that value
		QHash<QString, QList<MediaItem*> > possibleValues;
		for (int itemInd = 0; itemInd < itemsGenerated.count(); ++ itemInd)
		{
			QString currValue =
				itemsGenerated.takeAt(itemInd)
					->getMember(QString("metadata.details.") + key.c_str()).asCString();
			possibleValues[currValue] << itemsGenerated.takeAt(itemInd);
		}

		// if there is only one possible value, we don't make the folder
		if (possibleValues.count() <= 1)
		{
			continue;
		}

		// make the detail folder
		QString detailName = key.c_str();
		// TODO make the detail name clean for directory naming
		rootDir.mkdir(detailName);
		rootDir.cd(detailName);
		QDir detailFile = rootDir.absoluteFilePath("config.json");
		Folder* detailFolder = new Folder(detailFile);
		detailFolder->getMember("metadata.name") = detailName.data();

		// make the detail value folders
		auto iter = possibleValues.constBegin();
		while (iter != possibleValues.constEnd())
		{
			// create the value folder
			QString valueName = iter.key();
			// TODO clean the value name for directory naming
			rootDir.mkdir(valueName);
			rootDir.cd(valueName);
			QDir valueFile = rootDir.absoluteFilePath("config.json");
			Folder* valueFolder = new Folder(valueFile);

			// add the value folder to the detail folder
			detailFolder->addItem(valueFolder);

			// add the matching items to the value folder
			for (int itemInd = 0; itemInd < iter.value().count(); ++ itemInd)
			{
				valueFolder->addItem(iter.value()[itemInd]);
			}

			// move rootDir back out of the value folder
			rootDir.cdUp();

			// move onto the next value
			++ iter;
		}

		// move rootDir back out of the detail folder
		rootDir.cdUp();

		// add the detail folder to placeInMe
		placeInMe->addItem(detailFolder);
	}
}