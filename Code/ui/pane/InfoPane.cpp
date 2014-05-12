// header file
#include "InfoPane.h"

// debug
#include "debug_macros/debug.h"

// font stuff
#include <QFontMetrics>

// transparent scroll area
#include "ui/widgets/TransparentScrollArea.h"

using namespace AWE;
using namespace UI;
using namespace Json;

InfoPane::InfoPane(QWidget* parent, GlobalSettings* settings)
	:	Pane(parent),
		myGlobalSettings(settings),
		myMediaItem(settings->getRootFolder()),
		myMainLayout(new QVBoxLayout(this)),
		myName(new TextItemWidget(this, myMediaItem->getName(), 
				settings->getFontByName("big"), true)),
		myMediaType(new TextItemWidget(this,
					myMediaItem->getStringMember("metadata.type"), 
					settings->getFontByName("normal"), true)),
		myFirstSeparator(new QFrame(this)),
		myDetailScrollArea(new TransparentScrollArea(this)),
		myDetailWidget(new QWidget(this)),
		myDetailLayout(new QGridLayout(myDetailWidget)),
		myDetails(),
		myDetailValues(),
		mySecondSeparator(new QFrame(this)),
		myDescriptionScrollArea(new TransparentScrollArea(this)),
		myDescription(new TextItemWidget(this,
						myMediaItem->getStringMember("metadata.description"),
						settings->getFontByName("normal"), true)),
		myScraperLayout(new QHBoxLayout),
		myScrapeButton(new QPushButton(tr("Get Metadata"), this)),
		myScraperSelections(new QComboBox(this)),
		myScraperOptionsLayout(new QHBoxLayout),
		myAskUserBox(new QCheckBox(tr("Ask Me"), this)),
		myImportBox(new QCheckBox(tr("Import Files"), this)),
		myInheritMetadataBox(new QCheckBox(tr("Inherit Metadata"), this)),
		myButtonArea(new QStackedLayout),
		myMediaFileButtons(new QWidget(this)),
		myMediaFileLayout(new QHBoxLayout(myMediaFileButtons)),
		myPlayButton(new QPushButton(tr("Play"), this)),
		myPlayerSelections(new QComboBox(this)),
		myServiceButton(new QPushButton(tr("Open"), this)),
		myFolderButton(new QPushButton(tr("Open"), this))
{
	/* set up the layouts */
	myFirstSeparator->setFrameShape(QFrame::HLine);
	mySecondSeparator->setFrameShape(QFrame::HLine);
	// add the stuff to the main layout
	myMainLayout->addWidget(myName);
	myMainLayout->addWidget(myMediaType);
	myMainLayout->addWidget(myFirstSeparator);
	myMainLayout->addWidget(myDetailScrollArea, 1);
	myDetailScrollArea->setContentsMargins(0, 0, 0, 0);
	myDetailWidget->setContentsMargins(0, 0, 0, 0);
	myDetailLayout->setContentsMargins(0, 0, 0, 0);
	myDetailScrollArea->setWidget(myDetailWidget);
	myDetailScrollArea->setWidgetResizable(true);
	myDetailScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	myMainLayout->addWidget(mySecondSeparator);
	myMainLayout->addWidget(myDescriptionScrollArea, 1);
	myDescriptionScrollArea->setWidget(myDescription);
	myDescriptionScrollArea->setWidgetResizable(true);
	myDescriptionScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	myMainLayout->addLayout(myScraperLayout);
	myScraperLayout->addWidget(myScrapeButton);
	myScraperLayout->addWidget(myScraperSelections);
	myMainLayout->addLayout(myScraperOptionsLayout);
	myScraperOptionsLayout->addWidget(myAskUserBox);
	myScraperOptionsLayout->addWidget(myImportBox);
	myScraperOptionsLayout->addWidget(myInheritMetadataBox);
	myMainLayout->addLayout(myButtonArea);
	// add the details for the current item
	makeDetailUIElements();
	makeDropdownMenus();
	// add the buttons to the button area
	myButtonArea->setContentsMargins(0, 0, 0, 0);
	myMediaFileLayout->setContentsMargins(0, 0, 0, 0);
	myMediaFileButtons->setContentsMargins(0, 0, 0, 0);
	myButtonArea->addWidget(myMediaFileButtons);
	myMediaFileLayout->addWidget(myPlayButton);
	myMediaFileLayout->addWidget(myPlayerSelections);
	myButtonArea->addWidget(myServiceButton);
	myButtonArea->addWidget(myFolderButton);
	myButtonArea->setCurrentIndex(2);

	/* connections */
	connect(myPlayButton, &QPushButton::clicked,
			this, &InfoPane::respondToPlayButton);
	connect(myServiceButton, &QPushButton::clicked,
			this, &InfoPane::respondToOpenButton);
	connect(myFolderButton, &QPushButton::clicked,
			this, &InfoPane::respondToFolderOpen);
	connect(myScrapeButton, &QPushButton::clicked,
			this, &InfoPane::respondToScrapeButton);

	/* widget settings */
	myAskUserBox->setTristate(false);
	myAskUserBox->setCheckState(Qt::Checked);
	myImportBox->setTristate(false);
	myImportBox->setCheckState(Qt::Unchecked);
	myInheritMetadataBox->setTristate(false);
	myInheritMetadataBox->setCheckState(Qt::Unchecked);
}

InfoPane::~InfoPane()
{
	delete myName;
	delete myMediaType;
	delete myFirstSeparator;
	for (auto i : myDetails)
	{
		delete i;
	}
	for (auto i : myDetailValues)
	{
		delete i;
	}
	delete myDetailLayout;
	delete myDetailWidget;
	delete myDetailScrollArea;
	delete mySecondSeparator;
	delete myDescription;
	delete myDescriptionScrollArea;
	delete myScrapeButton;
	delete myScraperSelections;
	delete myScraperLayout;
	delete myButtonArea;
	delete myPlayButton;
	delete myPlayerSelections;
	delete myMediaFileLayout;
	delete myMediaFileButtons;
	delete myServiceButton;
	delete myFolderButton;
	delete myMainLayout;
}

void InfoPane::setItem(MediaItem* item)
{
	myMediaItem = item;
	// reset the name, type, and description
	myName->setText(item->getName());
	myMediaType->setText(item->getStringMember("metadata.type"));
	myDescription->setText(item->getStringMember("metadata.description"));
	// reset the details
	for (auto i : myDetails)
	{
		myDetailLayout->removeWidget(i);
		delete i;
	}
	for (auto i : myDetailValues)
	{
		myDetailLayout->removeWidget(i);
		delete i;
	}
	myDetails.clear();
	myDetailValues.clear();
	// change the button area
	if (item->getItemType() == FILE_TYPE)
	{
		while (myPlayerSelections->count() > 0)
		{
			myPlayerSelections->removeItem(0);
		}
		myPlayerSelections->addItem(((MediaFile*) item)->getDefaultPlayer()->getName());
		myButtonArea->setCurrentIndex(0);
	}
	else if (item->getItemType() == SERVICE_TYPE)
	{
		myButtonArea->setCurrentIndex(1);
	}
	else // folder
	{
		myButtonArea->setCurrentIndex(2);
	}
	makeDetailUIElements();
	makeDropdownMenus();
}

void InfoPane::respondToPlayButton()
{
	emit wantsToOpenFile((MediaFile*) myMediaItem,
		myGlobalSettings->getPlayerByName(myPlayerSelections->currentText()));
}

void InfoPane::respondToOpenButton()
{
	emit wantsToOpenService((MediaService*) myMediaItem);
}

void InfoPane::respondToFolderOpen()
{
	emit wantsToOpenFolder((Folder*) myMediaItem);
}

void InfoPane::respondToScrapeButton()
{
	if (myScraperSelections->count() != 0)
	{
		emit wantsToScrapeForMetadata(myMediaItem,
			myGlobalSettings->getScraperByName(myScraperSelections->currentText()),
			myAskUserBox->isChecked(), myImportBox->isChecked(),
			myInheritMetadataBox->isChecked());
	}
}

void InfoPane::makeDetailUIElements()
{
	Value& details = myMediaItem->getMember("metadata.details");
	int row = 0;
	QFont f(myGlobalSettings->getFontByName("normal"));
	QFontMetrics metrics(f);
	int maxDetailWidth = 0;
	int w;
	for (auto det : details["_order"])
	{
		// add the widgets
		TextItemWidget* detail = new TextItemWidget(this, det.asCString(),
													f);
		TextItemWidget* detailValue = new TextItemWidget(this, 
											stringFor(details[det.asString()]),
											f);
		myDetails << detail;
		myDetailValues << detailValue;
		myDetailLayout->addWidget(detail, row, 0);
		myDetailLayout->addWidget(detailValue, row, 1);
		// figure out detail width
		w = metrics.width(detail->getText()) + 21;
		if (w > maxDetailWidth)
		{
			maxDetailWidth = w;
		}
		++ row;
	}
	for (auto i : myDetails)
	{
		i->fixSizeToFitIn(QSize(maxDetailWidth, 16777215));
	}
}

void InfoPane::makeDropdownMenus()
{
	// get the scrapers
	myScraperSelections->clear();
	const QList<MetadataScraper*> scrapers 
		= myGlobalSettings->getAllScrapersForItem(myMediaItem);
	for (auto scraper : scrapers)
	{
		// get the index to place it at
		int i;
		for (i = 0; i < myScraperSelections->count(); ++ i)
		{
			if (scraper->getName() > myScraperSelections->itemText(i))
			{
				break;
			}
		}
		// put it in the list
		myScraperSelections->insertItem(i, scraper->getName());
	}
	// enable/disable buttons
	if (myScraperSelections->count() == 0)
	{
		myScrapeButton->setEnabled(false);
		myAskUserBox->setEnabled(false);
		myImportBox->setEnabled(false);
		myInheritMetadataBox->setEnabled(false);
		myScraperSelections->setEnabled(false);
	}
	else
	{
		myScrapeButton->setEnabled(true);
		myAskUserBox->setEnabled(true);
		myImportBox->setEnabled(true);
		myScraperSelections->setEnabled(true);
		// only enable inherit metadata if the types work
		QDir parentFolder(myMediaItem->getConfigFile().absolutePath());
		parentFolder.cdUp();
		if (myMediaItem->getItemType() == FOLDER_TYPE)
		{
			parentFolder.cdUp();
		}
		MediaItem* container = myGlobalSettings
			->getMediaItemByJSONFile(parentFolder.absoluteFilePath("config.json"));
		if (container)
		{
			FolderGenerator* parents 
				= myGlobalSettings->getFolderGeneratorForType(container->getType());
			FolderGenerator* mine
				= myGlobalSettings->getFolderGeneratorForType(myMediaItem->getType());
			if (parents->getSubGenerators().contains(mine))
			{
				myInheritMetadataBox->setEnabled(true);
			}
			else
			{
				myInheritMetadataBox->setEnabled(false);
				myInheritMetadataBox->setCheckState(Qt::Unchecked);
			}
		}
		else
		{
			myInheritMetadataBox->setEnabled(false);
			myInheritMetadataBox->setCheckState(Qt::Unchecked);
		}
	}
	// get the players
	myPlayerSelections->clear();
	if (myMediaItem->getItemType() == FILE_TYPE)
	{
		int indexOfDefault = -1;
		const QList<MediaPlayer*> players 
			= myGlobalSettings->getAllPlayersForFile((MediaFile*) myMediaItem);
		for (auto player : players)
		{
			// get the index to place it at
			int i;
			for (i = 0; i < myPlayerSelections->count(); ++ i)
			{
				if (player->getName() > myPlayerSelections->itemText(i))
				{
					break;
				}
			}
			// put it in the list
			myPlayerSelections->insertItem(i, player->getName());
			// change the default's index if necessary
			if (player == ((MediaFile*) myMediaItem)->getDefaultPlayer())
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
			myPlayerSelections->setCurrentIndex(indexOfDefault);
		}
		// enable/disable buttons
		if (myPlayerSelections->count() == 0)
		{
			myPlayButton->setEnabled(false);
			myPlayerSelections->setEnabled(false);
		}
		else
		{
			myPlayButton->setEnabled(true);
			myPlayerSelections->setEnabled(true);
		}
	}
}

QString InfoPane::stringFor(Value& val)
{
	// strings should just be as is
	if (val.isString())
	{
		return val.asCString();
	}
	// numbers should be the decimal representation
	else if (val.isInt())
	{
		return QString::number(val.asInt());
	}
	// booleans are "Yes" or "No"
	else if (val.isBool())
	{
		if (val.asBool())
		{
			return tr("Yes");
		}
		else
		{
			return tr("No");
		}
	}
	// arrays should be comma-separated lists of the strings for each member
	else if (val.isArray() && val.size() > 0)
	{
		QString text = stringFor(val[0]);
		for (uint i = 1; i < val.size(); ++ i)
		{
			text += ", " + stringFor(val[i]);
		}
		return text;
	}
	// objects shouldn't occur, so make it empty
	return "";
}