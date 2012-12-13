#include <string>
#include <list>

#if !defined(DALI_FRAGMENT_H)
#define DALI_FRAGMENT_H

namespace Dali {

class Fragment {
private:
public:
	virtual std::string 		toString() = 0;
};

} // Dali

#endif // DALI_FRAGMENT_H