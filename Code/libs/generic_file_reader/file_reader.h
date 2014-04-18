#ifndef FILE_READER_H
#define FILE_READER_H

// for reading generic files
#include <iostream>
#include <fstream>

// for reading web pages
#include "libs/internet_reader/internet_reader.h"

// for storing output
#include <string>

/**
 * \brief Copy the contents of a file onto an output stream.
 *
 * `file` could be on the local machine or the network;
 * this method figures that out for you.
 *
 * To get the contents as a string, use `std::stringstream`.
 *
 * \param[in] file The path to the file to open.
 * \param[out] out The `std::ostream` to write to.
 *
 * \return `true` if the file was read, `false` otherwise.
 **/
bool copyFile(const std::string& file, std::ostream& out);

#endif