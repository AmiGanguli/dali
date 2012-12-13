#include "Constant.h"

namespace Dali {

std::string
Constant::toString()
{
	return std::string(text_);
}

Constant *
Constant::parse( const char *&c, const char *end )
{
	bool brace = false;
	bool stop = false;
	const char *start = c;
	const char *last_char = c;
	
	while (c < end && !stop) {
		if (*c == '{' && brace) {
			brace = false;
			stop = true;
		} else if (*c == '{') {
			brace = true;
		} else {
			brace = false;
			last_char = c + 1;
		}
		c++;
	}
	if (brace) {
		last_char ++;
	}
	
	Constant *constant = 0;
	int length = last_char - start;
	if (length) {
		char *text = new char[length + 1];
		int i;
		for (i = 0; i < length; i ++) {
			text[i] = start[i];
		}
		text[i] = 0;
		constant = new Constant(text);
	}
	return constant;
}

} // Dali