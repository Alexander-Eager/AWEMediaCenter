#ifndef DEBUG_H
#define DEBUG_H

#	define SHOULD_DEBUG 0

#	if SHOULD_DEBUG

#		include <QDebug>

#		define DEBUG_OUT(STR) qDebug() << STR;

#		define DEBUG(STR) STR

#	else

#		define DEBUG_OUT(STR)

#		define DEBUG(STR)

#	endif

#endif