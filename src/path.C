#include <iostream>
#include <list>
#include <string>

#include "Path.h"
#include "Constant.h"

int
main(int argc, char* argv[])
{
	if (argc > 1) {
		std::string p(argv[1]);
		const char *start = p.c_str();
		const char *end = start + p.length();
		
		Dali::Path *path = Dali::Path::parse(start, end);
		std::cout << "Path: " << path->toString() << std::endl;
		std::cout << "Rest: " << start << std::endl << std::endl;
		delete path;

		start = p.c_str();
		end = start + p.length();
		Dali::Constant *constant = Dali::Constant::parse(start, end);
		if (!constant) {
			std::cout << "Constant was null" << std::endl;
		} else {
			std::cout << "Constant: " << constant->toString() << std::endl;
			std::cout << "Rest: " << start << std::endl << std::endl;
			delete constant;
		}
	}

	return 0;
}
