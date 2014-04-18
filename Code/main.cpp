// for loading the user settings
#include <string>
#include "settings/AWEGlobalSettings.h"

// for the UI
#include "items/AWEFolder.h"
#include "items/AWEMediaFile.h"
#include <iostream>
#include <deque>

using namespace std;
using namespace AWE;

int main(int argc, char* argv[])
{
	// get the main settings
	string mainSettings;
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

	deque<Folder*> stack;
	stack.push_back(settings->getRootFolder());
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
			for (auto i : stack.back()->getItems())
			{
				cout << i->getName() << endl;
			}
		}
		// open the file or folder
		else if (buffer.substr(0, 4) == "open")
		{
			string temp = buffer.substr(5, buffer.size() - 5);
			cout << "Item " << temp << endl;
			for (auto i : stack.back()->getItems())
			{
				if (i->getName() == temp)
				{
					if (i->getItemType() == FILE_TYPE)
					{
						cout << "Playing file \"" 
							<< i->getName() << "\"" << endl;
						((MediaFile*) i)->play();
					}
					else if (i->getItemType() == FOLDER_TYPE)
					{
						cout << "Opening folder \"" 
							<< i->getName() << "\"" << endl;
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