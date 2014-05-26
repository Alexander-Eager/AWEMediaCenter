#include "file_reader.h"

// for reading web pages
#include "libs/internet_reader/internet_reader.h"
#include <QFile>
#include <QUrl>

bool copyFile(QString file, QTextStream& out)
{
	QUrl url(file);
	if (url.isValid() && !url.isRelative())
	{
		// network file, so read from there
		return readURLIntoStream(file, out);
	}

	// not a network file, so try local
	QFile readMe(file);
	if (readMe.open(QFile::ReadOnly))
	{
		// it exists
		QTextStream reader(&readMe);
		while (!reader.atEnd() && !out.status())
		{
			out << reader.readLine() << "\n";
		}
		return !out.status();
	}

	return false;
}

bool copyFile(QString file, QIODevice& out)
{
	QUrl url(file);
	if (url.isValid() && !url.isRelative())
	{
		// network file, so read from there
		return readURLIntoIODevice(file, out);
	}

	// not a network file, so try local
	QFile readMe(file);
	if (readMe.open(QFile::ReadOnly))
	{
		// it is a local file
		while (!readMe.atEnd())
		{
			out.write(readMe.readLine());
		}
		return !readMe.error();
	}

	return false;
}