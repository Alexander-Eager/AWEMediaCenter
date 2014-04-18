#ifndef INTERNET_READER_H
#define INTERNET_READER_H

#include <cstddef>
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

/** \brief Read the given web page.
 *
 * \param pageToRead The address of the page to read.
 * \param out The output stream to write the data to.
 **/
void readURLIntoStream(const std::string& pageToRead, std::ostream& out);

#endif