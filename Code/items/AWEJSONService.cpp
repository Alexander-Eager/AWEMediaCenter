// header file
#include "AWEJSONService.h"

// for running the app
#include <QProcess>

AWEJSONService::AWEJSONService(const QDir& file) :
	AWEMediaService(file)
{
	myCommand = getStringMember("command");
}

int AWEJSONService::open()
{
	QProcess process;
	process.start(myCommand.c_str());
	return process.waitForFinished();
}