// header file
#include "AWEMC.h"

using namespace AWE;

GlobalSettings* AWEMC::mySettings = nullptr;

GlobalSettings* AWEMC::settings()
{
	return mySettings;
}

AWEMC::AWEMC() { }