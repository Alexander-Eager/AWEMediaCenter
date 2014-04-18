// header file
#include "AWEJSONPlayer.h"

// media file class
#include "items/AWEMediaFile.h"

// JSON library
#include "libs/json/json.h"

// for reading in the JSON file
#include "libs/generic_file_reader/file_reader.h"
#include <sstream>

// for running commands
#include <QProcess>

AWEJSONPlayer::AWEJSONPlayer(Json::Value& player)
{
	myName = player["name"].asString();
	myProgram = player["program"].asString();
	myArguments = player["args"].asString();
	// TODO other arguments
}

int AWEJSONPlayer::play(AWEMediaFile* file)
{
	std::string args = myArguments;
	args.replace(args.find_first_of("{1}"), 3, 
		file->getMediaFile().absolutePath().toStdString());
	// TODO other replaces
	QProcess prog;
	prog.start(QString((myProgram + " " + args).c_str()));
	return prog.waitForFinished();
}

const std::string& AWEJSONPlayer::getName() const
{
	return myName;
}