#include "file_reader.h"

// for reading web pages
#include "libs/internet_reader/internet_reader.h"

#include <QFile>

bool copyFile(const QString& file, QTextStream& out)
{
	// try to open locally first
	QFile readMe(file);
	if (readMe.open(QFile::ReadOnly))
	{
		// it is a local file
		QTextStream reader(&readMe);
		out << reader.readAll().status();
		return !out.status();
	}

	// it was not a local file, so try the network
	readURLIntoStream(file, out);
}