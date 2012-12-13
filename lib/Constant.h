#include <string>
#include <list>

#include "Fragment.h"

#if !defined(DALI_CONSTANT_H)
#define DALI_CONSTANT_H

namespace Dali {

class Constant : public Fragment {
private:
	char *text_;

public:
	Constant(char *text) : text_(text) {}
	~Constant()
	{
		delete[] text_;
	}

	virtual std::string	toString();
	static Constant *	parse( const char *&c, const char *end );
};

} // Dali

#endif // DALI_CONSTANT_H