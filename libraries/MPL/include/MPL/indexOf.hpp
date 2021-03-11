#ifndef MPL_INDEXOF_HPP
#define MPL_INDEXOF_HPP

#include <type_traits>
#include "typeList.hpp"

namespace MPL{
	template<typename, typename>
	struct IndexOf;
	
	// IndexOf base case: found the type we're looking for.
	template<typename T, typename... Ts>
	struct IndexOf<T, TypeList < T, Ts...>> : std::integral_constant<std::size_t, 0>{};

	// IndexOf recursive case: 1 + IndexOf the rest of the types.
	template<typename T, typename TOther, typename... Ts>
	struct IndexOf<T, TypeList < TOther, Ts...>> : std::integral_constant<std::size_t, 1 + IndexOf<T, TypeList<Ts...>>{}>{};
	
}
#endif //MPL_INDEXOF_HPP
