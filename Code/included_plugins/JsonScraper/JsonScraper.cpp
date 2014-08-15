// header file
#include "JsonScraper.h"

// settings
#include "settings/AWEMC.h"

// for reading files
#include "libs/generic_file_reader/file_reader.h"

// for regular expressions
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

// other important classes
#include <QVector>

// debug
#include <QDebug>

using namespace JSON;
using namespace AWE;

using Match = QRegularExpressionMatch;
using Regex = QRegularExpression;
using Matches = QVector<QRegularExpressionMatch>;

class JsonScraperPrivate
{
	public:
		// name of the scraper
		QString name;

		// type that this scrapes for
		QString type;

		// scraper validity
		bool valid;

		// The file name regex
		Regex fileName;

		// can there be multiple items per file?
		bool multipleItemsPerFile;

		// root procedure settings
		JsonArray rootProcedures;

		// the current item being edited
		MetadataHolder* currItem;

		// the current flags
		JsonScraper::ScraperSettings currConfig;

		// check the scraper's validity
		inline void checkValidity();
		inline int getHighestBackref(const QString& refString);

		// replace item's metadata with default metadata
		inline void makeDefault();

		// Execute a procedure
		inline bool executeProcedure(const JsonValue& proc, const Match& refs);

		// gets the matches for a given procedure
		inline Matches getMatches(const JsonValue& proc, const Match& refs);

		// replace backreferences
		inline void replaceBackrefs(QString& str, const Match& refs);

		// set values for a match
		inline void getProperties(const JsonValue& proc, const Match& refs);

		// for file contents and speed
		QHash<QString, QString> previouslyReadFiles;
		inline QString getFileContents(const QString& file);
};

JsonScraper::JsonScraper(ConfigFile* file)
	:	d(new JsonScraperPrivate)
{
	d->currItem = nullptr;
	if (!file || !file->isValid())
	{
		qWarning() << "JsonScraper: Configuration file badly formatted";
		d->valid = false;
		return;
	}
	d->valid = true;

	// get the name and type
	d->name = file->getMember({"metadata", "name"}).toString();
	d->type = file->getMember({"metadata", "type"}).toString();

	// get the file name regex
	if (!file->getMember({"metadata", "file name"}).isString())
	{
		qWarning() << "JsonScraper: Missing file name regex for"
			<< d->name;
		d->valid = false;
		return;
	}
	d->fileName = file->getMember({"metadata", "file name"}).toString();

	// get the root procedures array
	if (!file->getMember({"scraping procedure", "procedures"}).isArray())
	{
		qWarning() << "JsonScraper: Missing root procedures array for"
			<< d->name;
	}
	d->rootProcedures = file->getMember({"scraping procedure",
		"procedures"}).toArray();

	// item multiplicity
	d->multipleItemsPerFile = file->getMember({"scraping procedure",
		"repeat"}).toBoolean();

	// check the validity of the procedures
	d->checkValidity();
}

JsonScraper::~JsonScraper()
{
	delete d;
}

bool JsonScraper::addMetadata(MetadataHolder* item,
	JsonScraper::ScraperSettings config)
{
	currItem = item;
	d->makeDefault();
	Match fileNameMatch = fileName.match(item->getLocation());
	if (!fileNameMatch.isValid())
	{
		qWarning() << "JsonScraper: File name does not match for" << item->getName();
		currItem = nullptr;
		return false;
	}
	bool ans = true;
	const JsonArray procArray = rootProcedures;
	for (const auto& proc : procArray)
	{
		ans &&= d->executeProcedure(proc, fileNameMatch);
	}
	return ans;
}

// TODO makeMediaItems

bool JsonScraperPrivate::executeProcedure(const JsonValue& proc, const Match& refs)
{
	Matches newRefs = getMatches(proc, refs);
	bool ans = true;
	for (auto currRefs : newRefs)
	{
		getProperties(proc, currRefs);
		const JsonArray newProcs = proc["procedures"].toArray();
		for (auto newProc : newProcs)
		{
			ans &&= executeProcedure(newProc, currRefs);
		}
	}
}

void JsonScraperPrivate::checkValidity()
{
	// TODO
}

int JsonScraperPrivate::getHighestBackref(const QString& refString)
{
	// TODO
	return (int) (((uint) (-1)) >> 1);
}

void JsonScraperPrivate::makeDefault()
{
	// TODO
}

Matches JsonScraperPrivate::getMatches(const JsonValue& proc,
	const Match& refs)
{
	// get all of the repeat/ask user members
	const JsonObject obj = proc.toObject();
	bool multi = proc["repeat"].toBoolean();
	bool shouldAsk = currConfig & JsonScraper::AskUser;
	QString textPromptFormat = proc["ask user with text"].toString();
	QString imagePromptFormat = proc["ask user with image"].toString();

	// get the file's contents
	QString fileToRead = proc["look in file"].toString();
	replaceBackrefs(fileToRead, refs);
	QString textToLookIn = getFileContents(fileToRead);

	// get the "for" regex
	QString textToLookFor = proc["for"].toString();
	replaceBackrefs(textToLookFor, refs);
	Regex regex(textToLookFor);

	// get the answer
	Matches ans;
	if (shouldAsk && !textPromptFormat.isEmpty()
		&& !imagePromptFormat.isEmpty())
	{
		// ask user with both text and images
		// TODO
	}
	if (shouldAsk && !textPromptFormat.isEmpty())
	{
		// ask user with just text
		// TODO
	}
	if (shouldAsk && !imagePromptFormat.isEmpty())
	{
		// ask user with just images
		// TODO
	}
	if (multi)
	{
		// just get all of the matches
		QRegularExpressionMatchIterator iter = regex.globalMatch(textToLookIn);
		while (iter.hasNext())
		{
			ans << iter.next();
		}
		return ans;
	}
	else
	{
		// just get the first match
		Match m = regex.match(textToLookIn);
		ans << m;
		return ans;
	}
}

inline void replaceBackrefs(QString& str, const Match& refs)
{
	int i = 0;
	while (i < str.count() - 1)
	{
		if (str[i] == '$')
		{
			char c = str[i + 1];
			switch (c)
			{
				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
				case '8': case '9': // numbered backrefs
					str.replace(i, 2, refs.captured(c - '0'));
					i += 2;
					break;
				case '$':
					str.replace(i, 2, "$");
					i += 2;
					break;
				default:
					// this makes no sense, so leave it alone
					// this should never even happen with correct
					// validity checking
					qWarning() << "JsonScraper: Found invalid reference string"
						<< "while scraping";
					++ i;
					break;
			}
		}
		else
		{
			++ i;
		}
	}
}

inline void getProperties(const JsonValue& proc, const Match& refs)
{
	// name
	if (proc["set name"].isString())
	{
		QString newName = proc["set name"].toString();
		replaceBackrefs(newName, refs);
		currItem->setName(newName);
	}
	// description
	if (proc["set description"].isString())
	{
		QString newDescription = proc["set description"].toString();
		replaceBackrefs(newDescription, refs);
		currItem->setDescription(newDescription);
	}
	// details
	/*	Details are added according to these rules:
		- Strings have their backrefs replaced
		- If the value to be edited is a string, the string
			representation is used.
		- If the value to be edited is a boolean, these rules
			are used:
			- Strings like "yes", "no", "true", "false" are converted.
			- Numbers are converted to integers and then booleans.
			- Booleans are... well, you know.
			- Anything else is invalid, and no value is set.
		- If the value to be edited is a number, these rules
			are used:
			- Strings in numeric format are converted.
			- Numbers are... well, you know.
			- Booleans become 0 (false) or 1 (true)
			- Anything else is invlaid, and no value is set.
		- If the value to be edited is an array, the new value is appended.
		- If the value to be edited is an object or null, the value is replaced.
	*/
	if (proc["set details"].isObject())
	{
		const JsonObject obj = proc["set details"].toObject();
		for (auto detail : obj)
		{
			JsonValue detailValue = *detail;
			JsonValue::Type newType = detailValue.getType();
			if (newType == JsonValue::String)
			{
				QString temp = detailValue.toString();
				replaceBackrefs(temp, refs);
				detailValue = temp;
			}
			JsonValue::Type shouldType = currItem
				->getDetailValue(detail.key()).getType();
			switch (shouldType)
			{
				case JsonValue::String:
					switch (newType)
					{
						case JsonValue::String:
							currItem->addDetail(detail.key(), detailValue);
							break;
						case JsonValue::Number:
							currItem->addDetail(detail.key(), 
								QString::number(detailValue.toDouble()));
							break;
						case JsonValue::Boolean:
							if (detailValue.toBoolean())
							{
								currItem->addDetail(detail.key(),
									"Yes");
							}
							else
							{
								currItem->addDetail(detail.key(),
									"No");
							}
							break;
						case JsonValue::Array: case JsonValue::Object:
						case JsonValue::Null: default:
							// TODO multiple add with arrays?
							qWarning() << "JsonScraper: Found invalid detail value"
								<< "while scraping";
							break;
					}
					break;
				case JsonValue::Number:
					switch (newType)
					{
						case JsonValue::String:
							bool stringToNumberOk;
							double detailValueAsNumber = detailValue
								.toString().toDouble(&stringToNumberOk);
							if (stringToNumberOk)
							{
								currItem->addDetail(detail.key(), detailValueAsNumber);
							}
							else
							{
								qWarning() << "JsonScraper: Invalid string-to-number"
									<< "while scraping";
							}
							break;
						case JsonValue::Number:
							currItem->addDetail(detail.key(), detailValue);
							break;
						case JsonValue::Boolean:
							if (detailValue.toBoolean())
							{
								currItem->addDetail(detail.key(), 1);
							}
							else
							{
								currItem->addDetail(detail.key(), 0);
							}
							break;
						case JsonValue::Array: case JsonValue::Object:
						case JsonValue::Null: default:
							qWarning() << "JsonScraper: Invalid detail value"
								<< "while scraping";
							break;
					}
					break;
				case JsonValue::Boolean:
					switch (newType)
					{
						case JsonValue::String:
							QString boolString = detailValue.toString();
							if (!QString::compare(boolString, "yes",
								Qt::CaseInsensitive) || !QString::compare(
								boolString, "true", Qt::CaseInsensitive))
							{
								currItem->addDetail(detail.key(), true);
							}
							else if (!QString::compare(boolString, "no",
								Qt::CaseInsensitive) || !QString::compare(
								boolString, "false", Qt::CaseInsensitive))
							{
								currItem->addDetail(detail.key(), false);
							}
							else
							{
								qWarning() << "JsonScraper: Invalid string-to-bool"
									<< "conversion.";
							}
							break;
						case JsonValue::Number:
							currItem->addDetail(detail.key(), (bool)
								detailValue.toInteger());
							break;
						case JsonValue::Boolean:
							currItem->addDetail(detail.key(), detailValue);
							break;
						case JsonValue::Array: case JsonValue::Object:
						case JsonValue::Null: default:
							qWarning() << "JsonScraper: Invalid detail value"
								<< "while scraping";
							break;
					}
					break;
				case JsonValue::Array: case JsonValue::Object:
				case JsonValue::Null: default:
					currItem->addDetail(detail.key(), detailValue);
					break;
			}
		}
	}
	// icons
	if (proc["add icons"].isArray())
	{
		const JsonArray arr = proc["add icons"].toArray();
		for (auto i : arr)
		{
			if (!i.isString())
			{
				qWarning() << "JsonScraper: Non-string icon while scraping";
			}
			else
			{
				QString iconToAdd = i.toString();
				replaceBackrefs(iconToAdd, refs);
				if (currConfig & JsonScraper::ImportIcons)
				{
					currItem->importIcon(iconToAdd);
				}
				else
				{
					currItem->addIcon(iconToAdd);
				}
			}
		}
	}
	// fanarts
	if (proc["add fanarts"].isArray())
	{
		const JsonArray arr = proc["add fanarts"].toArray();
		for (auto i : arr)
		{
			if (!i.isString())
			{
				qWarning() << "JsonScraper: Non-string fanart while scraping";
			}
			else
			{
				QString fanartToAdd = i.toString();
				replaceBackrefs(fanartToAdd, refs);
				if (currConfig & JsonScraper::ImportFanarts)
				{
					currItem->importFanart(fanartToAdd);
				}
				else
				{
					currItem->addFanart(fanartToAdd);
				}
			}
		}
	}
}

QString JsonScraperPrivate::getFileContents(const QString& file)
{
	if (previouslyReadFiles.contains(file))
	{
		return previouslyReadFiles[files];
	}
	QString contents;
	QTextStream stream(&contents);
	copyFile(file, stream);
	previouslyReadFiles[file] = contents;
	return contents;
}