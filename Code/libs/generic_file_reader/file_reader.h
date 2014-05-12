#ifndef FILE_READER_H
#define FILE_READER_H

// for storing output
#include <QString>
#include <QTextStream>
#include <QIODevice>

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
bool copyFile(QString file, QTextStream& out);

/**
 * \brief Copy the contents of a file into an IO device.
 *
 * `file` could be on the local machine or the network;
 * this method figures that out for you.
 *
 * To get the contents as a string, use `std::stringstream`.
 *
 * \param[in] file The path to the file to open.
 * \param[out] out The `QIODevice` to write to.
 *
 * \return `true` if the file was read, `false` otherwise.
 **/
bool copyFile(QString file, QIODevice& out);

#endif