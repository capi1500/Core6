#ifndef MPL_TYPELIST_HPP
#define MPL_TYPELIST_HPP

#include <type_traits>

namespace MPL{
	template<class... Ts>
	struct TypeList{
		// Size of the list.
		static constexpr std::size_t size{sizeof...(Ts)};
	};
}

#endif //MPL_TYPELIST_HPP
