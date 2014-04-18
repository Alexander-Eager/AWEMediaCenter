#ifndef DEBUG_H
#define DEBUG_H

#	define SHOULD_DEBUG 0

#	if SHOULD_DEBUG

#		include <iostream>

#		define DEBUG_OUT(STR) std::cout << STR << std::endl;

#		define DEBUG(STR) STR

#	else

#		define DEBUG_OUT(STR)

#		define DEBUG(STR)

#	endif

#endif