#ifndef BACKEND_LIBRARY_MACROS_H
#define BACKEND_LIBRARY_MACROS_H

#ifdef MAKING_AWEMC_BACKEND_LIBRARY

#	define AWEMC_BACKEND_LIBRARY Q_DECL_EXPORT

#else

#	define AWEMC_BACKEND_LIBRARY Q_DECL_IMPORT

#endif

#endif // BACKEND_LIBRARY_MACROS_H