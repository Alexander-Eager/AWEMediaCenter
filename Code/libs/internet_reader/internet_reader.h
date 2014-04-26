#ifndef INTERNET_READER_H
#define INTERNET_READER_H

#include <QString>
#include <QTextStream>

/** \brief Read the given web page.
 *
 * \param pageToRead The address of the page to read.
 * \param out The output stream to write the data to.
 **/
void readURLIntoStream(const QString& pageToRead, QTextStream& out);

#endif