// header file
#include "AWEJSONService.h"

// for running the app
#include <QProcess>

using namespace AWE;

JSONService::JSONService(const QDir& file) :
	MediaService(file)
{
	myCommand = getStringMember("command");
}

int JSONService::open()
{
	QProcess process;
	process.start(myCommand);
	return process.waitForFinished();
}