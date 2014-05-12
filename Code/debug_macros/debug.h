#ifndef DEBUG_H
#define DEBUG_H

#	define SHOULD_DEBUG 1

#	if SHOULD_DEBUG

#		include <QDebug>

#		include "libs/cli_output/column_group.h"

#		define DEBUG_OUT(STR) std::cout << STR << std::endl;

#		define DEBUG_ERR(STR) std::cout << TCOM::Color::RED \
											<< STR << TCOM::Command::ResetGraphics() \
											<< std::endl;

#		define DEBUG_WARN(STR) std::cout << TCOM::Color::CYAN \
											<< STR << TCOM::Command::ResetGraphics() \
											<< std::endl;

#		define DEBUG(STR) STR

#	else

#		define DEBUG_OUT(STR)

#		define DEBUG_ERR(STR)

#		define DEBUG_WARN(STR)

#		define DEBUG(STR)

#	endif

#endif