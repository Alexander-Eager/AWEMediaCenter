#ifndef BACKEND_LIBRARY_MACROS_H
#define BACKEND_LIBRARY_MACROS_H

// forward declarations (making linking faster)
#include "BackendForwards.h"

// Q_DECL_EXPORT and Q_DECL_IMPORT, among other things
#include <QtGlobal>

// QObject is the eventual base of everything, so we just include it here
#include <QObject>

#ifdef MAKING_AWEMC_BACKEND_LIBRARY

#	define AWEMC_BACKEND_LIBRARY Q_DECL_EXPORT

#else

#	define AWEMC_BACKEND_LIBRARY Q_DECL_IMPORT

#endif

#endif // BACKEND_LIBRARY_MACROS_H
