#include <string>
#include <list>

#if !defined(DALI_PATH_H)
#define DALI_PATH_H

namespace Dali {

class Path {
private:
	int up_;
	std::list<std::string> segments_;

public:
	Path() : up_(0)
	{}

	std::string 	toString();
	static Path *	parse( const char *&c, const char *end );
};

} // Dali

#endif // DALI_PATH_H