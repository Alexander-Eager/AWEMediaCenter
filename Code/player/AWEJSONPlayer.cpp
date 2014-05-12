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
	:	myName(player["name"].asCString()),
		myProgram(player["program"].asCString()),
		myArguments(player["args"].asCString())
{
	for (auto str : player["filetypes"])
	{
		myFileTypes << str.asCString();
	}
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

bool JSONPlayer::canPlay(MediaFile* file)
{
	if (myFileTypes.count() == 0)
	{
		return true;
	}
	QString ext = file->getMediaFile().absolutePath();
	int lastDot = ext.lastIndexOf('.');
	if (lastDot < 0)
	{
		return myFileTypes.contains("");
	}
	ext.replace(0, lastDot, "");
	return myFileTypes.contains(ext);
}

QString JSONPlayer::getName() const
{
	return myName;
}