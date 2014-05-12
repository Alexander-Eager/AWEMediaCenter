// header file
#include "FolderBrowser.h"

// MainWindow class
#include "ui/MainWindow.h"

// MediaFile class
#include "items/AWEMediaFile.h"

// MediaService class
#include "items/AWEMediaService.h"

// debug
#include "debug_macros/debug.h"

using namespace AWE;
using namespace UI;
using namespace Json;

FolderBrowser::FolderBrowser(GlobalSettings* settings)
	:	QObject(nullptr),
		myGlobalSettings(settings),
		myBrowserHistory(),
		myMainWidget(new QWidget(nullptr)),
		myMainLayout(new QStackedLayout(myMainWidget)),
		myBackgroundImage(new ImageItemWidget(myMainWidget, -1,
								QPixmap())),
		myForegroundWidget(new QWidget(myMainWidget)),
		myForegroundMainLayout(new QVBoxLayout(myForegroundWidget)),
		myForegroundLayout(new QHBoxLayout),
		myTitleBar(new TextPane(myMainWidget, "", settings->getFontByName("biggest"))),
		myImagePane(new ImagePane(myMainWidget)),
		myFolderPane(new FolderPane(myMainWidget)),
		myInfoPane(new InfoPane(myMainWidget, settings))
{
	/* set up all of the layout/widget organization */
	// makes it a layer-type stack instead of only one widget at a time
	myMainLayout->setStackingMode(QStackedLayout::StackAll);
	myMainLayout->setContentsMargins(0, 0, 0, 0);
	// add all of the widgets/layouts
	myBackgroundImage->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
	myMainLayout->addWidget(myBackgroundImage);
	myMainLayout->addWidget(myForegroundWidget);
	myMainLayout->setCurrentIndex(1);
	myForegroundMainLayout->addWidget(myTitleBar);
	myForegroundMainLayout->addLayout(myForegroundLayout);
	myForegroundLayout->addWidget(myImagePane, 1);
	myForegroundLayout->addWidget(myFolderPane, 1);
	myForegroundLayout->addWidget(myInfoPane, 1);

	/* make all of the connections */
	// when an item is highlighted, it should change the images and info
	myMainWidget->connect(myFolderPane, &FolderPane::itemHighlighted,
							myImagePane, &ImagePane::setItem);
	myMainWidget->connect(myFolderPane, &FolderPane::itemHighlighted,
							myInfoPane, &InfoPane::setItem);
	// opening an item
	myMainWidget->connect(myFolderPane, &FolderPane::itemSelected,
							this, &FolderBrowser::openItem);
	myMainWidget->connect(myInfoPane, &InfoPane::wantsToOpenFolder,
							this, &FolderBrowser::openItem);
	// going up one folder
	myMainWidget->connect(myFolderPane, &FolderPane::goUpOne,
							this, &FolderBrowser::moveUpOneFolder);
	// changing the background image
	myMainWidget->connect(myImagePane, &ImagePane::fanartChanged,
							this, &FolderBrowser::setBackgroundImage);
	// refresh the folder pane
	myMainWidget->connect(myImagePane, &ImagePane::iconChanged,
							this, &FolderBrowser::respondToIconChange);
	// scrape for metadata
	myMainWidget->connect(myInfoPane, &InfoPane::wantsToScrapeForMetadata,
							this, &FolderBrowser::scrapeForMetadata);
}

FolderBrowser::~FolderBrowser()
{
	delete myImagePane;
	delete myFolderPane;
	delete myInfoPane;
	delete myTitleBar;
	delete myForegroundLayout;
	delete myForegroundMainLayout;
	delete myForegroundWidget;
	delete myMainLayout;
	delete myMainWidget;
}

QString FolderBrowser::getType()
{
	return "Folder Browser";
}

void FolderBrowser::setParent(MainWindow* parent)
{
	// disconnect old open item connections
	if (myMainWidget->nativeParentWidget())
	{
		myInfoPane->disconnect(myInfoPane, 0,
								myMainWidget->nativeParentWidget(), 0);
	}
	// set the widget's parent
	myMainWidget->setParent(parent);
	// make new open item connections
	myInfoPane->connect(myInfoPane, &InfoPane::wantsToOpenFile,
						parent, &MainWindow::openFile);
	myInfoPane->connect(myInfoPane, &InfoPane::wantsToOpenService,
						parent, &MainWindow::openService);
}

QWidget* FolderBrowser::getWidget()
{
	return myMainWidget;
}

void FolderBrowser::open()
{
	openItem(myGlobalSettings->getRootFolder());
}

void FolderBrowser::openItem(MediaItem* item)
{
	if (item->getItemType() == FOLDER_TYPE)
	{
		// open the folder
		myFolderPane->setFolder((Folder*) item);
		// push it onto the stack
		myBrowserHistory.push((Folder*) item);
		// change the title bar
		setTitleBarText(item->getName());
		// set the other two panes
		myImagePane->setItem(item);
		myInfoPane->setItem(item);
	}
	else
	{
		// pass it on to the main window
		MainWindow* window = (MainWindow*) myMainWidget->nativeParentWidget();
		if (item->getItemType() == FILE_TYPE)
		{
			MediaFile* file = (MediaFile*) item;
			window->openFile(file, file->getDefaultPlayer());
		}
		else if (item->getItemType() == SERVICE_TYPE)
		{
			MediaService* service = (MediaService*) item;
			window->openService(service);
		}
	}
}

void FolderBrowser::moveUpOneFolder()
{
	if (myBrowserHistory.count() > 1)
	{
		myBrowserHistory.pop();
		myFolderPane->setFolder(myBrowserHistory.top());
		setTitleBarText(myBrowserHistory.top()->getName());
		// get the background image
		QDir imageFile = myBrowserHistory.top()->getConfigFile().absolutePath();
		imageFile.cdUp();
		int ind = myBrowserHistory.top()->getIntMember("metadata.fanarts.default");
		Value& files = myBrowserHistory.top()->getMember("metadata.fanarts.files");
		if ((uint) ind >= files.size())
		{
			setBackgroundImage(QPixmap());
		}
		else
		{
			setBackgroundImage(QPixmap(imageFile.absoluteFilePath(files[ind].asCString())));	
		}
		// change the item for the other two panes
		myImagePane->setItem(myBrowserHistory.top());
		myInfoPane->setItem(myBrowserHistory.top());
	}
}

void FolderBrowser::setTitleBarText(QString text)
{
	myTitleBar->setText(text);
}

void FolderBrowser::setBackgroundImage(QPixmap image)
{
	myBackgroundImage->setImage(image);
}

void FolderBrowser::scrapeForMetadata(AWE::MediaItem* item,
										AWE::MetadataScraper* scraper,
										bool askUser, bool import,
										bool inheritMetadata)
{
	// scrape
	if (scraper->prepare(myGlobalSettings))
	{
		if (!scraper->scrapeDataForFile(item, askUser, import, inheritMetadata))
		{
			// didn't work in its entirety
			DEBUG_OUT("ERROR scraping for "
					<< item->getStringMember("metadata.location").toStdString())
		}
	}
	else
	{
		// the scraper just flat out isn't valid
		DEBUG_ERR("ERROR: \"" << scraper->getName().toStdString() << "\" not valid")
		return;
	}
	scraper->deactivate();
	// refresh items
	myInfoPane->setItem(item);
	myImagePane->setItem(item);
	myFolderPane->setFolder(myBrowserHistory.top());
}

void FolderBrowser::respondToIconChange(QPixmap)
{
	myFolderPane->refresh();
}