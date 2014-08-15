// header file
#include "JsonService.h"

// for opening external programs
#include <QProcess>

// for debug
#include <QDebug>

using namespace AWE;
using namespace JSON;

class JsonServicePrivate
{
	public:
		// the application
		QProcess app;

		// the command string
		QString command;

		// determines if the console is shown
		bool showConsole;

		// validity
		bool valid;

		// open or not
		bool open;

		// the name of the service
		QString name;
};

JsonService::JsonService(ConfigFile* file)
	:	d(new JsonServicePrivate)
{
	d->valid = true;
	if (!file || !file->getMember({"config", "command"}).isString())
	{
		qWarning() << "Player not valid because it is missing important members";
		d->valid = false;
		return;
	}

	// get the name
	d->name = file->getMember({"metadata", "name"}).toString();

	// get the command
	d->command = file->getMember({"config", "command"}).toString();

	// get the console showing
	d->showConsole = file->getMember({"config", "show console"}).toBoolean();

	// make connections for starting/closing
	connect(&d->app, &QProcess::started,
			this,	[this] ()
					{
						emit opened();
					} );
	connect(&d->app, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>
						(&QProcess::finished),
			this,	[this] (int, QProcess::ExitStatus)
					{
						emit closed();
					} );
	d->open = false;
}

JsonService::~JsonService()
{
	delete d;
}

bool JsonService::isValid() const
{
	return d->valid;
}

QString JsonService::getName() const
{
	return d->name;
}

bool JsonService::open()
{
	if (d->open)
	{
		return true;
	}
	d->app.start(d->command);
	if (!d->app.waitForStarted())
	{
		return false;
	}
	d->open = true;
	return true;
}

bool JsonService::close()
{
	if (!d->open)
	{
		return true;
	}
	d->app.terminate();
	if (!d->app.waitForFinished())
	{
		return false;
	}
	d->open = false;
	return true;
}