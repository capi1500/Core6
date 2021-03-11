#ifndef MPL_MACROS_HPP
#define MPL_MACROS_HPP

#include <utility>

namespace MPL{
	namespace helper{
		// Shortcut for `std::forward`.
		#define MPL_FWD(mX) ::std::forward<decltype(mX)>(mX)
		
		// Syntactic sugar to retrieve the type from a MPL Type wrapper.
		#define MPL_TYPE(mX) typename decltype(mX)::type
		
		// Pastes two preprocessor tokens together.
		#define MPL_CAT(mA0, mA1) mA0##mA1
	}
}

#endif //MPL_MACROS_HPP
