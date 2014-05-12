#include "internet_reader.h"

#include <curl/curl.h>
#include <cstddef>
#include <QUrl>

/**
 * \brief Used by libcurl to read pages from the internet.
 *
 * Writes the information from `readFromMe` onto `writeToMe`.
 *
 * NOTE: You really, really, really should never call this function directly.
 *
 * \param[in] readFromMe The data to write to `writeToMe`.
 * \param[in] size Part of the size of `readFromMe`.
 * \param[in] nmemb The other part of the size of `readFromMe`.
 * \param[in] writeToMe A `QTextStream*` to write data to.
 **/
size_t writeCallback(char* readFromMe, size_t size, size_t nmemb, void* writeToMe)
{
	QTextStream* temp = (QTextStream*) writeToMe;
	for (size_t i = 0; i < size * nmemb; ++ i)
	{
		temp->operator<< (readFromMe[i]);
	}
	return size * nmemb;
}

/**
 * \brief Used by libcurl to read pages from the internet.
 *
 * Writes the information from `readFromMe` onto `writeToMe`.
 *
 * NOTE: You really, really, really should never call this function directly.
 *
 * \param[in] readFromMe The data to write to `writeToMe`.
 * \param[in] size Part of the size of `readFromMe`.
 * \param[in] nmemb The other part of the size of `readFromMe`.
 * \param[in] writeToMe A `QIODevice*` to write data to.
 **/
size_t writeCallbackIODevice(char* readFromMe, size_t size, size_t nmemb, void* writeToMe)
{
	QIODevice* temp = (QIODevice*) writeToMe;
	return temp->write(readFromMe, size * nmemb);
}

bool readURLIntoStream(QString pageToRead, QTextStream& out)
{
	// check for url validity
	QUrl url(pageToRead);
	if (!url.isValid() && !url.isRelative())
	{
		return false;
	}

	// now read
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, pageToRead.toStdString().data());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	bool ans = !curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return ans;
}

bool readURLIntoIODevice(QString pageToRead, QIODevice& out)
{
	// check for url validity
	QUrl url(pageToRead);
	if (!url.isValid() && !url.isRelative())
	{
		return false;
	}

	// now read
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, pageToRead.toStdString().data());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallbackIODevice);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	bool ans = !curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return ans;
}