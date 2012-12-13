#include <string>

#if !defined(DALI_TAG_H)
#define DALI_TAG_H

namespace Dali {

class Tag {
public:
	virtual ~Tag() = 0;
	
	virtual std::string 	toString() = 0;
	static Tag *		parse( const char *&c, const char *end );
};

} // Dali

#endif // DALI_TAG_H