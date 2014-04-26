// header file
#include "AWEJSONPlayer.h"

// media file class
#include "items/AWEMediaFile.h"

// JSON library
#include "libs/json/json.h"

// for running commands
#include <QProcess>

using namespace AWE;

JSONPlayer::JSONPlayer(Json::Value& player)
{
	myName = player["name"].asCString();
	myProgram = player["program"].asCString();
	myArguments = player["args"].asCString();
}

int JSONPlayer::play(MediaFile* file)
{
	QString args = myArguments;
	args.replace("{1}",
		file->getMediaFile().absolutePath());
	// TODO other replaces
	QProcess prog;
	prog.start(myProgram + " " + args);
	return prog.waitForFinished();
}

const QString& JSONPlayer::getName() const
{
	return myName;
}