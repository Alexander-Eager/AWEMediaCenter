// header file
#include "JsonPlayer.h"

// for playing media
#include <QProcess>

// for matching files
#include <QStringList>
#include <QRegExp>

// for debug
#include <QDebug>

using namespace AWE;
using namespace JSON;

class JsonPlayerPrivate
{
	public:
		// the application
		QProcess app;

		// the currently open file
		MediaFile* currentFile;

		// the command string
		QString command;

		// file types this can play
		QStringList playable;

		// determines if the console is shown
		bool showConsole;

		// validity
		bool valid;

		// the name of the player
		QString name;
};

JsonPlayer::JsonPlayer(ConfigFile* file)
	:	d(new JsonPlayerPrivate)
{
	d->currentFile = nullptr;
	d->valid = true;
	if (!file || !file->getMember({"config", "command"}).isString()
		|| !file->getMember({"config", "can play"}).isArray())
	{
		qWarning() << "Player not valid because it is missing important members";
		d->valid = false;
		return;
	}

	// get the name
	d->name = file->getMember({"metadata", "name"}).toString();

	// get the command
	d->command = file->getMember({"config", "command"}).toString();

	// get the playable files
	const JsonArray arr = file->getMember({"config", "can play"}).toArray();
	for (auto str : arr)
	{
		if (str.isString())
		{
			d->playable << str.toString();
		}
	}
	if (d->playable.isEmpty())
	{
		qWarning() << "Player not valid because it cannot play anything";
		d->valid = false;
		return;
	}

	// get the console showing
	d->showConsole = file->getMember({"config", "show console"}).toBoolean();

	// make connections for starting/closing
	connect(&d->app, &QProcess::started,
			this,	[this] ()
					{
						emit startedPlaying();
						emit startedPlaying(d->currentFile);
					} );
	/*connect(&d->app, &QProcess::finished,
			this,	[this] (int, QProcess::ExitStatus)
					{
						emit closed();
						emit closed(d->currentFile);
						d->currentFile = nullptr;
					} );*/
}

JsonPlayer::~JsonPlayer()
{
	delete d;
}

QString JsonPlayer::getName() const
{
	return d->name;
}

bool JsonPlayer::canPlay(MediaFile* file) const
{
	if (!d->valid || !file)
	{
		return false;
	}
	QRegExp regex;
	QString f = file->getMediaFile();
	for (auto str : d->playable)
	{
		regex.setPattern(str);
		regex.setPatternSyntax(QRegExp::Wildcard);
		if (regex.exactMatch(f))
		{
			return true;
		}
	}
	return false;
}

bool JsonPlayer::isPlaying() const
{
	return d->app.state();
}

bool JsonPlayer::isPlaying(MediaFile* file) const
{
	return d->currentFile == file;
}

bool JsonPlayer::isValid() const
{
	return d->valid;
}

bool JsonPlayer::play(MediaFile* file) 
{
	// TODO show console if desired
	if (!canPlay(file))
	{
		return false;
	}
	if (isPlaying())
	{
		if (!close())
		{
			return false;
		}
	}
	// replace the special sequences like {0}
	QString comm = d->command;
	QString f = file->getMediaFile();
	comm.replace("{0}", f);
	d->app.start(comm);
	if (!d->app.waitForStarted())
	{
		return false;
	}
	d->currentFile = file;
	return true;
}

bool JsonPlayer::close()
{
	if (!isPlaying())
	{
		return true;
	}
	d->app.terminate();
	if (!d->app.waitForFinished())
	{
		return false;
	}
	return true;
}

bool JsonPlayer::close(MediaFile* file)
{
	if (!isPlaying(file))
	{
		return false;
	}
	return close();
}