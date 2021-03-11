#ifndef MPL_TYPE_HPP
#define MPL_TYPE_HPP

namespace MPL{
	// Simple wrapper for types that can be instantiated.
	template<typename T>
	struct Type{
		using type = T;
	};
}
#endif //MPL_TYPE_HPP
