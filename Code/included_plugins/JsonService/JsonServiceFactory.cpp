// header file
#include "JsonServiceFactory.h"

// the class to create
#include "JsonService.h"

using namespace AWE;

MediaService* JsonServiceFactory::create(ConfigFile* file)
{
	MediaService* ans = new JsonService(file);
	if (!ans->isValid())
	{
		delete ans;
		return nullptr;
	}
	return ans;
}