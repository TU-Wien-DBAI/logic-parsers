#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif
#include "debug.hpp"

#ifdef DEBUG
std::ostream &logic::Debug::stream = std::cout;
#endif // DEBUG
