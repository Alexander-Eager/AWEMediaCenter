// header file
#include "MainWindow.h"

// settings
#include "settings/AWEMC.h"

// widgets
#include <QStackedLayout>

// debug
#include <QDebug>

using namespace AWE;

namespace UI
{
	class MainWindowPrivate
	{
		public:
			FolderBrowser* folderBrowser;
			WindowContents* currentContents;
			QStackedLayout* layout;
	};
}

using namespace UI;

MainWindow::MainWindow(QWidget* parent)
	:	QWidget(parent),
		d(new MainWindowPrivate)
{
	d->folderBrowser = new FolderBrowser;
	d->currentContents = d->folderBrowser;
	d->layout = new QStackedLayout(this);

	d->layout->setContentsMargins(0, 0, 0, 0);
	d->folderBrowser->setParent(this);
	d->layout->addWidget(d->currentContents->getWidget());
}

MainWindow::~MainWindow()
{
	delete d->folderBrowser;
	delete d->layout;
	delete d;
}

void MainWindow::open()
{
	showFullScreen();
	d->currentContents->open();
}

void MainWindow::setContents(WindowContents* contents)
{
	if (contents)
	{
		d->layout->removeWidget(d->currentContents->getWidget());
		d->currentContents = contents;
		d->layout->addWidget(d->currentContents->getWidget());
	}
}

WindowContents* MainWindow::getContents()
{
	return d->currentContents;
}

FolderBrowser* MainWindow::getFolderBrowser()
{
	return d->folderBrowser;
}

void MainWindow::switchToFolderBrowser()
{
	setContents(getFolderBrowser());
}

void MainWindow::openFile(MediaFile* file, MediaPlayerHandler* player)
{
	if (player)
	{
		player->play(file);
	}
	else
	{
		qWarning() << "MainWindow: Tried to use null player";
	}
}

void MainWindow::openService(MediaServiceHandler* service)
{
	if (service)
	{
		service->open();
	}
	else
	{
		qWarning() << "MainWindow: Tried to open null service";
	}
}