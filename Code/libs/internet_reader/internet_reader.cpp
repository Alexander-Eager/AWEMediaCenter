#include "internet_reader.h"
//#include "debug_macros/debug.h"

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
 * \param[in] writeToMe An `std::ostream*` to write data to.
 **/
size_t writeCallback(char* readFromMe, size_t size, size_t nmemb, void* writeToMe)
{
	((std::ostream*) writeToMe)->write(readFromMe, size * nmemb);
	return size * nmemb;
}

/**
 * \brief Write the data from a web page onto an output stream.
 *
 * Reads the webpage described by the `pageToRead` parameter
 * and writes all of the data it gets to `out`.
 *
 * You can use this function to, for example, download an image
 * file from the internet.
 *
 * \param[in] pageToRead The URL of the desired web page.
 * \param[out] out The stream to write the contents of said web page to.
 **/
void readURLIntoStream(const std::string& pageToRead, std::ostream& out)
{
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, pageToRead.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}