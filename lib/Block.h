#include <string>

#if !defined(DALI_BOCK_H)
#define DALI_BOCK_H

namespace Dali {

class Block : public Tag {
public:
	static Tag *		parse( const char *&c, const char *end );
};

} // Dali

#endif // DALI_BOCK_H