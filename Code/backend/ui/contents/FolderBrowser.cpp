// header file
#include "FolderBrowser.h"

// main window class
#include "ui/MainWindow.h"

// media file class
#include "items/MediaFile.h"

// media service class
#include "items/MediaServiceHandler.h"

// settings
#include "settings/AWEMC.h"

// debug
#include <QDebug>

// internal data stuff
#include <QStack>

// the layouts used
#include <QStackedLayout>
#include <QHBoxLayout>

// a bunch of widget classes for displaying everything
#include <QLabel>
#include "ui/pane/ImagePane.h"
#include "ui/pane/InfoPane.h"
#include "ui/pane/FolderPane.h"
#include "ui/pane/TextPane.h"
#include "ui/widgets/items/ImageItemWidget.h"

using namespace AWE;

namespace UI
{
	class FolderBrowserPrivate
	{
		public:
			// this is all data stuff

			/** \brief The folder browsing history. **/
			QStack<AWE::Folder*> browserHistory;

			// this is all UI stuff

			/** \brief The main widget for folder browsing. **/
			QWidget* mainWidget;

			/** \brief The stacked layout with everything on it. **/
			QStackedLayout* mainLayout;

			/** \brief The background image. **/
			ImageItemWidget* backgroundImage;

			/** \brief The foreground layouts. **/
			QWidget* foregroundWidget;
			/** \brief The foreground layouts. **/
			QVBoxLayout* foregroundMainLayout;
			/** \brief The foreground layouts. **/
			QHBoxLayout* foregroundLayout;

			/** \brief The title bar. **/
			TextPane* titleBar;

			/** \brief The item image pane. **/
			ImagePane* imagePane;

			/** \brief The folder pane. **/
			FolderPane* folderPane;

			/** \brief The item info pane. **/
			InfoPane* infoPane;
	};
}

using namespace UI;

FolderBrowser::FolderBrowser()
	:	d(new FolderBrowserPrivate)
{
	// make everything
	d->mainWidget = new QWidget(nullptr);
	d->mainLayout = new QStackedLayout(d->mainWidget);
	d->backgroundImage = new ImageItemWidget(d->mainWidget, -1, QPixmap());
	d->foregroundWidget = new QWidget(d->mainWidget);
	d->foregroundMainLayout = new QVBoxLayout(d->foregroundWidget);
	d->foregroundLayout = new QHBoxLayout;
	d->titleBar = new TextPane(d->mainWidget, "", "biggest");
	d->imagePane = new ImagePane(d->mainWidget);
	d->folderPane = new FolderPane(d->mainWidget);
	d->infoPane = new InfoPane(d->mainWidget);

	/* set up all of the layout/widget organization */
	// makes it a layer-type stack instead of only one widget at a time
	d->mainLayout->setStackingMode(QStackedLayout::StackAll);
	d->mainLayout->setContentsMargins(0, 0, 0, 0);
	// add all of the widgets/layouts
	d->backgroundImage->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
	d->mainLayout->addWidget(d->backgroundImage);
	d->mainLayout->addWidget(d->foregroundWidget);
	d->mainLayout->setCurrentIndex(1);
	d->foregroundMainLayout->addWidget(d->titleBar);
	d->foregroundMainLayout->addLayout(d->foregroundLayout);
	d->foregroundLayout->addWidget(d->imagePane, 1);
	d->foregroundLayout->addWidget(d->folderPane, 1);
	d->foregroundLayout->addWidget(d->infoPane, 1);

	/* make all of the connections */
	// when an item is highlighted, it should change the images and info
	d->mainWidget->connect(d->folderPane, &FolderPane::itemHighlighted,
							d->imagePane, &ImagePane::setItem);
	d->mainWidget->connect(d->folderPane, &FolderPane::itemHighlighted,
							d->infoPane, &InfoPane::setItem);
	// opening an item
	d->mainWidget->connect(d->folderPane, &FolderPane::itemSelected,
							this, &FolderBrowser::openItem);
	d->mainWidget->connect(d->infoPane, &InfoPane::wantsToOpenFolder,
							this, &FolderBrowser::openItem);
	// going up one folder
	d->mainWidget->connect(d->folderPane, &FolderPane::goUpOne,
							this, &FolderBrowser::moveUpOneFolder);
	// changing the background image
	d->mainWidget->connect(d->imagePane, &ImagePane::fanartChanged,
							this, &FolderBrowser::setBackgroundImage);
	// scrape for metadata
	d->mainWidget->connect(d->infoPane, &InfoPane::wantsToScrapeForMetadata,
							this, &FolderBrowser::scrapeForMetadata);
}

FolderBrowser::~FolderBrowser()
{
	delete d->imagePane;
	delete d->folderPane;
	delete d->infoPane;
	delete d->titleBar;
	delete d->foregroundLayout;
	delete d->foregroundMainLayout;
	delete d->foregroundWidget;
	delete d->mainLayout;
	delete d->mainWidget;
	delete d;
}

QString FolderBrowser::getType()
{
	return "Folder Browser";
}

void FolderBrowser::setParent(MainWindow* parent)
{
	// disconnect old open item connections
	if (d->mainWidget->nativeParentWidget())
	{
		d->infoPane->disconnect(d->infoPane, 0,
								d->mainWidget->nativeParentWidget(), 0);
	}
	// set the widget's parent
	d->mainWidget->setParent(parent);
	// make new open item connections
	d->infoPane->connect(d->infoPane, &InfoPane::wantsToOpenFile,
						parent, &MainWindow::openFile);
	d->infoPane->connect(d->infoPane, &InfoPane::wantsToOpenService,
						parent, &MainWindow::openService);
}

QWidget* FolderBrowser::getWidget()
{
	return d->mainWidget;
}

void FolderBrowser::open()
{
	openItem(AWEMC::settings()->getRootFolder());
}

AWE::Folder* FolderBrowser::getCurrentFolder()
{
	return d->browserHistory.top();
}

void FolderBrowser::openItem(MediaItem* item)
{
	if (item->isFolder())
	{
		// open the folder
		d->folderPane->setFolder((Folder*) item);
		// push it onto the stack
		d->browserHistory.push((Folder*) item);
		// change the title bar
		setTitleBarText(item->getName());
		// set the other two panes
		d->imagePane->setItem(item);
		d->infoPane->setItem(item);
	}
	else
	{
		// pass it on to the main window
		MainWindow* window = (MainWindow*) d->mainWidget->nativeParentWidget();
		if (item->isFile())
		{
			MediaFile* file = (MediaFile*) item;
			window->openFile(file, file->getDefaultPlayer());
		}
		else if (item->isService())
		{
			MediaServiceHandler* service = (MediaServiceHandler*) item;
			window->openService(service);
		}
	}
}

void FolderBrowser::moveUpOneFolder()
{
	if (d->browserHistory.count() > 1)
	{
		d->browserHistory.pop();
		d->folderPane->setFolder(getCurrentFolder());
		setTitleBarText(getCurrentFolder()->getName());
		// get the background image
		setBackgroundImage(getCurrentFolder()->getDefaultFanart());
		// change the item for the other two panes
		d->imagePane->setItem(getCurrentFolder());
		d->infoPane->setItem(getCurrentFolder());
	}
}

void FolderBrowser::setTitleBarText(QString text)
{
	d->titleBar->setText(text);
}

void FolderBrowser::setBackgroundImage(QPixmap image)
{
	d->backgroundImage->setImage(image);
}

void FolderBrowser::scrapeForMetadata(MetadataHolder* item,
	MetadataScraperHandler* scraper, int flags)
{
	// scrape
	if (scraper->prepare())
	{
		if (!scraper->addMetadata(item, flags))
		{
			// didn't work in its entirety
			qWarning() << "FolderBrowser: Scraping failed for item"
				<< item->getName();
		}
	}
	else
	{
		// the scraper just flat out isn't valid
		qWarning() << "FolderBrowser: Scraper" << scraper->getName()
			<< "not valid.";
		return;
	}
	scraper->deactivate();
}