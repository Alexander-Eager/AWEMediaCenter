// for loading the user settings
#include <QDir>
#include "settings/GlobalSettings.h"

// for the UI
#include "ui/MainWindow.h"
#include <QApplication>

// curl setup
#include <curl/curl.h>

using namespace std;
using namespace AWE;
using namespace UI;

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);

	// get the main settings
	QDir mainSettings(QDir::home());
#if defined(__linux__) // linux
	mainSettings.cd(".awemc");
	mainSettings = mainSettings.absoluteFilePath("settings.json");
#elif defined(__APPLE__) // OS X
	mainSettings.cd(".awemc");
	mainSettings = mainSettings.absoluteFilePath("settings.json");
#elif defined(_WIN64) || defined(_WIN32)
	mainSettings = QDir::current();
	mainSettings = mainSettings.absoluteFilePath("settings.json");
#endif

	// create the application
	QApplication app(argc, argv);
	
	// load all of the program settings
	GlobalSettings* settings = new GlobalSettings(mainSettings.absolutePath());

	// create the main window
	MainWindow* window = new MainWindow(nullptr);
	window->open();

	int result = app.exec();

	// cleanup
	delete settings;
	delete window;

	curl_global_cleanup();

	return result;
}