// for loading the user settings
#include <QString>
#include "settings/AWEGlobalSettings.h"

// for the UI
#include "items/AWEFolder.h"
#include "items/AWEMediaFile.h"
#include <string>
#include <iostream>
#include <QStack>

using namespace std;
using namespace AWE;

int main(int argc, char* argv[])
{
	// get the main settings
	QString mainSettings;
	if (argc <= 1)
	{
		mainSettings = "settings.json";
	}
	else
	{
		mainSettings = argv[1];
	}
	
	// load all of the program from settings
	GlobalSettings* settings = new GlobalSettings(mainSettings);

	// UI stuff
	// TODO replace with Qt gui
	int result = 0;

	QStack<Folder*> stack;
	stack.push(settings->getRootFolder());
	string buffer;
	while (stack.size() != 0)
	{
		cout << "> ";
		buffer = "";
		getline(cin, buffer);
		// go back a directory
		if (buffer == "back")
		{
			cout << "cd .." << endl;
			stack.pop_back();
		}
		// list everything
		else if (buffer == "ls")
		{
			for (auto i : stack.top()->getItems())
			{
				cout << i->getName().toStdString() << endl;
			}
		}
		// open the file or folder
		else if (buffer.substr(0, 4) == "open")
		{
			string temp = buffer.substr(5, buffer.size() - 5);
			cout << "Item " << temp << endl;
			for (auto i : stack.back()->getItems())
			{
				if (i->getName().toStdString() == temp)
				{
					if (i->getItemType() == FILE_TYPE)
					{
						cout << "Playing file \"" 
							<< i->getName().toStdString() << "\"" << endl;
						((MediaFile*) i)->play();
					}
					else if (i->getItemType() == FOLDER_TYPE)
					{
						cout << "Opening folder \"" 
							<< i->getName().toStdString() << "\"" << endl;
						stack.push_back((Folder*) i);
					}
					// TODO services
				}
			}
		}
		else
		{
			cout << "Commands: open back ls" << endl;
		}
	}

	// cleanup
	delete settings;

	return result;
}