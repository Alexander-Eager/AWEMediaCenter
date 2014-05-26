// header file
#include "InfoPane.h"

// font stuff
#include <QFontMetrics>

// for settings
#include "settings/AWEMC.h"

// transparent scroll area
#include "ui/widgets/TransparentScrollArea.h"

// debug
#include <QDebug>

// UI related classes
#include <QString>
#include <QFrame>
#include <QWidget>
#include "ui/widgets/items/TextItemWidget.h"
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>

using namespace AWE;

namespace UI
{
	class InfoPanePrivate
	{
		public:
			// parent pointer
			InfoPane* p;
			/**
			 * \brief Helper function that creates the details
			 **/
			void makeDetailUIElements();

			/**
			 * \brief Helper funciton that fills the drop down menus.
			 **/
			void makeDropdownMenus();

			/** \brief The currently represented item. **/
			MediaItem* mediaItem;

			/** \brief The main layout of this widget. **/
			QVBoxLayout* mainLayout;

			/** \brief Name of the item. **/
			TextItemWidget* name;

			/** \brief Media type of this item. **/
			TextItemWidget* mediaType;

			/** \brief Separates the name and type from the details. **/
			QFrame* firstSeparator;

			/** \brief Scrollable area holding all of the details. **/
			QScrollArea* detailScrollArea;

			/** \brief Widget holding all of the details. **/
			QWidget* detailWidget;

			/** \brief Detail layout. **/
			QGridLayout* detailLayout;

			/** \brief List of the details. **/
			QList<TextItemWidget*> details;

			/** \brief List of the detail values. **/
			QList<TextItemWidget*> detailValues;

			/** \brief Separates the details from the description. **/
			QFrame* secondSeparator;

			/** \brief Scroll area for the description. **/
			QScrollArea* descriptionScrollArea;

			/** \brief Description of the item. **/
			TextItemWidget* description;

			/** \brief Metadata scraper button layout. **/
			QHBoxLayout* scraperLayout;

			/** \brief Button to start scraping. **/
			QPushButton* scrapeButton;

			/** \brief Drop down for selecting the scraper to use. **/
			QComboBox* scraperSelections;

			// depending on the displayed type, there can be different buttons
			/** \brief Switchable layout for different kinds of items. **/
			QStackedLayout* buttonArea;

			// file type
			/** \brief Widget for media files. **/
			QWidget* mediaFileButtons;

			/** \brief Layout for the media file buttons. **/
			QHBoxLayout* mediaFileLayout;

			/** \brief Button for playing a media file. **/
			QPushButton* playButton;

			/** \brief Drop down for choosing the desired media player. **/
			QComboBox* playerSelections;

			// service type
			/** \brief Button for opening a media service. **/
			QPushButton* serviceButton;

			// folder type
			/** \brief Button for opening a folder. **/
			QPushButton* folderButton;
	};
}

using namespace UI;

InfoPane::InfoPane(QWidget* parent)
	:	Pane(parent),
		d(new InfoPanePrivate)
{
	d->p = this;
	
	/* Create everything */
	d->mediaItem = AWEMC::settings()->getRootFolder();
	d->mainLayout = new QVBoxLayout(this);
	d->name = new TextItemWidget(this, d->mediaItem->getName(), "big");
	d->mediaType = new TextItemWidget(this, d->mediaItem->getType(), "normal");
	d->firstSeparator = new QFrame(this);
	d->detailScrollArea = new TransparentScrollArea(this);
	d->detailWidget = new QWidget(this);
	d->detailLayout = new QGridLayout(d->detailWidget);
	d->detailLayout->setColumnStretch(0, 1);
	d->detailLayout->setColumnStretch(1, 4);
	d->secondSeparator = new QFrame(this);
	d->descriptionScrollArea = new TransparentScrollArea(this);
	d->description = new TextItemWidget(this, d->mediaItem->getDescription(),
		"normal");
	d->scraperLayout = new QHBoxLayout;
	d->scrapeButton = new QPushButton(tr("Get Metadata"), this);
	d->scraperSelections = new QComboBox(this);
	d->buttonArea = new QStackedLayout;
	d->mediaFileButtons = new QWidget(this);
	d->mediaFileLayout = new QHBoxLayout(d->mediaFileButtons);
	d->playButton = new QPushButton(tr("Play"), this);
	d->playerSelections = new QComboBox(this);
	d->serviceButton = new QPushButton(tr("Open"), this);
	d->folderButton = new QPushButton(tr("Open"), this);

	/* set up the layouts */
	d->firstSeparator->setFrameShape(QFrame::HLine);
	d->secondSeparator->setFrameShape(QFrame::HLine);
	// add the stuff to the main layout
	d->mainLayout->addWidget(d->name);
	d->mainLayout->addWidget(d->mediaType);
	d->mainLayout->addWidget(d->firstSeparator);
	d->mainLayout->addWidget(d->detailScrollArea, 1);
	d->detailScrollArea->setContentsMargins(0, 0, 0, 0);
	d->detailWidget->setContentsMargins(0, 0, 0, 0);
	d->detailLayout->setContentsMargins(0, 0, 0, 0);
	d->detailScrollArea->setWidget(d->detailWidget);
	d->detailScrollArea->setWidgetResizable(true);
	d->detailScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	d->mainLayout->addWidget(d->secondSeparator);
	d->mainLayout->addWidget(d->descriptionScrollArea, 1);
	d->descriptionScrollArea->setWidget(d->description);
	d->descriptionScrollArea->setWidgetResizable(true);
	d->descriptionScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	d->mainLayout->addLayout(d->scraperLayout);
	d->scraperLayout->addWidget(d->scrapeButton);
	d->scraperLayout->addWidget(d->scraperSelections);
	d->mainLayout->addLayout(d->buttonArea);
	// add the details for the current item
	d->makeDetailUIElements();
	d->makeDropdownMenus();
	// add the buttons to the button area
	d->buttonArea->setContentsMargins(0, 0, 0, 0);
	d->mediaFileLayout->setContentsMargins(0, 0, 0, 0);
	d->mediaFileButtons->setContentsMargins(0, 0, 0, 0);
	d->buttonArea->addWidget(d->mediaFileButtons);
	d->mediaFileLayout->addWidget(d->playButton);
	d->mediaFileLayout->addWidget(d->playerSelections);
	d->buttonArea->addWidget(d->serviceButton);
	d->buttonArea->addWidget(d->folderButton);
	d->buttonArea->setCurrentIndex(2);

	/* connections */
	connect(d->playButton, &QPushButton::clicked,
			this, &InfoPane::respondToPlayButton);
	connect(d->serviceButton, &QPushButton::clicked,
			this, &InfoPane::respondToOpenButton);
	connect(d->folderButton, &QPushButton::clicked,
			this, &InfoPane::respondToFolderOpen);
	connect(d->scrapeButton, &QPushButton::clicked,
			this, &InfoPane::respondToScrapeButton);
}

InfoPane::~InfoPane()
{
	delete d->name;
	delete d->mediaType;
	delete d->firstSeparator;
	for (auto i : d->details)
	{
		delete i;
	}
	for (auto i : d->detailValues)
	{
		delete i;
	}
	delete d->detailLayout;
	delete d->detailWidget;
	delete d->detailScrollArea;
	delete d->secondSeparator;
	delete d->description;
	delete d->descriptionScrollArea;
	delete d->scrapeButton;
	delete d->scraperSelections;
	delete d->scraperLayout;
	delete d->buttonArea;
	delete d->playButton;
	delete d->playerSelections;
	delete d->mediaFileLayout;
	delete d->mediaFileButtons;
	delete d->serviceButton;
	delete d->folderButton;
	delete d->mainLayout;
	delete d;
}

void InfoPane::setItem(MediaItem* item)
{
	d->mediaItem = item;
	// reset the name, type, and description
	d->name->setText(item->getName());
	d->mediaType->setText(item->getType());
	d->description->setText(item->getDescription());
	// reset the details
	for (auto i : d->details)
	{
		d->detailLayout->removeWidget(i);
		delete i;
	}
	for (auto i : d->detailValues)
	{
		d->detailLayout->removeWidget(i);
		delete i;
	}
	d->details.clear();
	d->detailValues.clear();
	// change the button area
	if (item->isFile())
	{
		while (d->playerSelections->count() > 0)
		{
			d->playerSelections->removeItem(0);
		}
		MediaPlayerHandler* player = ((MediaFile*) item)->getDefaultPlayer();
		if (player)
		{
			d->playerSelections->addItem(player->getName());
			d->buttonArea->setCurrentIndex(0);	
		}
	}
	else if (item->isService())
	{
		d->buttonArea->setCurrentIndex(1);
	}
	else // folder
	{
		d->buttonArea->setCurrentIndex(2);
	}
	d->makeDetailUIElements();
	d->makeDropdownMenus();
}

void InfoPane::respondToPlayButton()
{
	emit wantsToOpenFile((MediaFile*) d->mediaItem,
		AWEMC::settings()->getPlayerHandler(d->playerSelections->currentText()));
}

void InfoPane::respondToOpenButton()
{
	emit wantsToOpenService((MediaServiceHandler*) d->mediaItem);
}

void InfoPane::respondToFolderOpen()
{
	emit wantsToOpenFolder((Folder*) d->mediaItem);
}

void InfoPane::respondToScrapeButton()
{
	if (d->scraperSelections->count() != 0)
	{
		emit wantsToScrapeForMetadata(d->mediaItem,
			AWEMC::settings()->getScraperHandler(d->scraperSelections->currentText()),
			0);
	}
}

void InfoPanePrivate::makeDetailUIElements()
{
	QFontMetrics met = AWEMC::settings()->getCurrentSkin()
		->getFont("normal").getFontMetrics();
	int w = 0;
	int maxWidth = 0;
	for (int i = 0; i < mediaItem->numDetails(); ++ i)
	{
		// add the widgets
		TextItemWidget* detail = new TextItemWidget(p,
			mediaItem->getDetailName(i), "normal");
		TextItemWidget* detailValue = new TextItemWidget(p, 
			mediaItem->getDetailValueAsString(i), "normal");
		details << detail;
		detailValues << detailValue;
		detailLayout->addWidget(detail, i, 0);
		detailLayout->addWidget(detailValue, i, 1);

		// get the detail name width
		w = met.width(detail->getText()) + 10;
		if (w > maxWidth)
		{
			maxWidth = w;
		}
	}
	// adjust the widths
	for (int i = 0; i < details.count(); ++ i)
	{
		details[i]->setMinimumWidth(maxWidth);
	}
}

void InfoPanePrivate::makeDropdownMenus()
{
	// get the scrapers
	scraperSelections->clear();
	const QList<MetadataScraperHandler*> scrapers 
		= AWEMC::settings()->getScrapersForItem(mediaItem);
	for (auto scraper : scrapers)
	{
		// get the index to place it at
		int i;
		for (i = 0; i < scraperSelections->count(); ++ i)
		{
			if (scraper->getName() > scraperSelections->itemText(i))
			{
				break;
			}
		}
		// put it in the list
		scraperSelections->insertItem(i, scraper->getName());
	}
	// enable/disable buttons
	if (scraperSelections->count() == 0)
	{
		scrapeButton->setEnabled(false);
		scraperSelections->setEnabled(false);
	}
	else
	{
		scrapeButton->setEnabled(true);
		scraperSelections->setEnabled(true);
	}

	// get the players
	playerSelections->clear();
	if (mediaItem->isFile())
	{
		MediaFile* file = (MediaFile*) mediaItem;
		int indexOfDefault = -1;
		const QList<MediaPlayerHandler*> players 
			= AWEMC::settings()->getPlayersForFile(file);
		for (auto player : players)
		{
			// get the index to place it at
			int i;
			for (i = 0; i < playerSelections->count(); ++ i)
			{
				if (player->getName() > playerSelections->itemText(i))
				{
					break;
				}
			}
			// put it in the list
			playerSelections->insertItem(i, player->getName());
			// change the default's index if necessary
			if (player == file->getDefaultPlayer())
			{
				indexOfDefault = i;
			}
			else if (i <= indexOfDefault)
			{
				++ indexOfDefault;
			}
		}
		if (indexOfDefault != -1)
		{
			playerSelections->setCurrentIndex(indexOfDefault);
		}
		// enable/disable buttons
		if (playerSelections->count() == 0)
		{
			playButton->setEnabled(false);
			playerSelections->setEnabled(false);
		}
		else
		{
			playButton->setEnabled(true);
			playerSelections->setEnabled(true);
		}
	}
}