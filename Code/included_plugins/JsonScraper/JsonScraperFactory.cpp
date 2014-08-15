// header file
#include "JsonScraperFactory.h"

// object this creates
#include "JsonScraper.h"

using namespace AWE;

MetadataScraper* JsonScraperFactory::create(ConfigFile* config)
{
	JsonScraper* ans = new JsonScraper(config);
	if (!ans->isValid())
	{
		delete ans;
		return nullptr;
	}
	return ans;
}