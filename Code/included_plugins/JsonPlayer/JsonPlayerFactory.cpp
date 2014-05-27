// header file
#include "JsonPlayerFactory.h"

// the class to create
#include "JsonPlayer.h"

using namespace AWE;

MediaPlayer* JsonPlayerFactory::create(ConfigFile* file)
{
	MediaPlayer* ans = new JsonPlayer(file);
	if (!ans->isValid())
	{
		delete ans;
		return nullptr;
	}
	return ans;
}