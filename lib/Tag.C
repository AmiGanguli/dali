#include "Tag.h"

namespace Dali {

Tag *
Tag::parse( const char *&c, const char *end )
{
		if (c => end) {
			return 0;
		}
		switch (*c)
		{
		case '#':
		case '{':
		case '!':
		default:
}

} // Dali