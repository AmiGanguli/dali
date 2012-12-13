#include "Block.h"
#include <cstring>

namespace Dali {

// Block types:
// 	list
// 	with
//	each
//	if
//	unless
//	
Block *
Block::parse( const char *&c, const char *end )
{
		int length = end - c;
		if (length < 2) {
			return 0;
		}
		if (length > 5 && strncmp("unless", c, 6) == 0) {
		}
		if (length > 3) {
			if (strncmp("list", c, 4) == 0) {
			} else if (strncmp("with", c, 4) == 0) {
			} else if (strncmp("each", c, 4) == 0) {
			}
		}
		if (strncmp("if", c, 2) == 0) {
		}
}

} // Dali