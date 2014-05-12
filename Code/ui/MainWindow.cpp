// header file
#include "MainWindow.h"

// settings
#include "settings/AWEMC.h"

using namespace AWE;
using namespace UI;

MainWindow::MainWindow(QWidget* parent)
	:	QWidget(parent),
		myFolderBrowser(new FolderBrowser(AWEMC::settings())),
		myCurrentContents(myFolderBrowser),
		myLayout(new QVBoxLayout(this))
{
	myLayout->setContentsMargins(0, 0, 0, 0);
	myFolderBrowser->setParent(this);
	myLayout->addWidget(myCurrentContents->getWidget());
	myCurrentContents->open();
}

MainWindow::~MainWindow()
{
	delete myFolderBrowser;
	delete myLayout;
}

void MainWindow::open()
{
	resize(1336, 768);
	showFullScreen();
	myCurrentContents->open();
}

void MainWindow::setContents(WindowContents* contents)
{
	if (contents)
	{
		myLayout->removeWidget(myCurrentContents->getWidget());
		myCurrentContents = contents;
		myLayout->addWidget(myCurrentContents->getWidget());
	}
}

WindowContents* MainWindow::getContents()
{
	return myCurrentContents;
}

FolderBrowser* MainWindow::getFolderBrowser()
{
	return myFolderBrowser;
}

void MainWindow::switchToFolderBrowser()
{
	setContents(getFolderBrowser());
}

// TODO settings browser stuff

void MainWindow::openFile(MediaFile* file, MediaPlayer* player)
{
	player->play(file);
}

void MainWindow::openService(MediaService* service)
{
	service->open();
}