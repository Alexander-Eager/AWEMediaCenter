#ifndef INTERNET_READER_H
#define INTERNET_READER_H

// backend library macros
#include "macros/BackendLibraryMacros.h"

#include <QString>
#include <QTextStream>
#include <QIODevice>

/** \brief Read the given web page.
 *
 * \param pageToRead The address of the page to read.
 * \param out The output stream to write the data to.
 *
 * \returns `true` if `pageToRead` is a valid URL and
 *					`out` had no errors,
 *			`false` if an error occured.
 */
AWEMC_BACKEND_LIBRARY auto readURLIntoStream(QString pageToRead,
                                             QTextStream& out) -> bool;

/** \brief Read the given web file.
 *
 * \param pageToRead The address of the file to read.
 * \param out The output device to write the data to.
 *
 * \returns `true` if `pageToRead` is a valid URL and
 *					`out` had no errors,
 *			`false` if an error occured.
 */
AWEMC_BACKEND_LIBRARY auto readURLIntoIODevice(QString pageToRead,
                                               QIODevice& out) -> bool;

#endif
