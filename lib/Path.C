#include "Path.h"

namespace Dali {

std::string
Path::toString()
{
	std::string out;
	for (int i = 0; i < up_; i ++) {
		out.append("../");
	}
	bool first = true;
	for (std::list<std::string>::iterator i = segments_.begin(); i != segments_.end(); i ++) {
		if (!first) {
			out.append(1,'.');
		}
		first = false;
		out.append(*i);
	}
	return out;
}

Path *
Path::parse( const char *&c, const char *end )
{
	Path *path = new Path();
	// This is a very permissive parser.  More error handling might be
	// wise at some point.  For now we don't object to identifiers with
	// embedded quotes, or number of other heinous crimes.
	//
	// The basic rules:
	// 	- the start of the string may contain a set of '../', each
	// 	  one signalling that we should go up a level.
	//	- segments are separated by '.'
	//	- white space at the start of a segment is consumed silently
	//	- white space elsewhere marks the end of input
	//	- '}' marks the end of input, and is not consumed
	//
		// Consume white space at the start.
	while (c < end && *c == ' ' || *c == '\t' || *c == '\n') {
		c ++;
	}

	// Consume '../'s.
	while (end - c >= 3 && *c == '.' && *(c+1) == '.' && *(c+2) == '/') {
		c += 3;
		path->up_ ++;
	}

	// Now consume the rest of the path.
	bool start = true;
	bool stop = false;
	while (c < end && !stop) {
		if (*c == '.') {
			start = true;
		} else if (*c == '}') {
			// Ends the path - don't consume this char
			//
			stop = true;
			c --;
		} else if (*c == ' ' || *c == '\t' || *c == '\n') {
			// Allow whitespace at the start.  Other
			// whitespace ends the path.
			//
			if (!start) {
				stop = true;
			}
		} else {
			if (start) {
				path->segments_.push_back(std::string(1, *c));
				start = false;
			} else {
				path->segments_.back().append(1,*c);
			}
		}
		c++;
	}
	return path;
}

} // Dali