#ifndef FILE_READER_H
#define FILE_READER_H

// for storing output
#include <QString>
#include <QTextStream>

/**
 * \brief Copy the contents of a file onto an output stream.
 *
 * `file` could be on the local machine or the network;
 * this method figures that out for you.
 *
 * To get the contents as a string, use `std::stringstream`.
 *
 * \param[in] file The path to the file to open.
 * \param[out] out The `QTextStream` to write to.
 *
 * \return `true` if the file was read, `false` otherwise.
 **/
bool copyFile(const QString& file, QTextStream& out);

#endif