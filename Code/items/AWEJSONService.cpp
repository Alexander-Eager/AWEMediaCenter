// header file
#include "AWEJSONService.h"

// for running the app
#include <QProcess>

using namespace AWE;

JSONService::JSONService(QDir file) :
	MediaService(file)
{
	myCommand = getStringMember("command");
}

int JSONService::open()
{
	QProcess process;
	process.start(myCommand);
	return process.waitForFinished(-1);
}