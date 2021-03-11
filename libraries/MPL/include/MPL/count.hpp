#ifndef MPL_COUNT_HPP
#define MPL_COUNT_HPP

#include <type_traits>
#include "typeList.hpp"

namespace MPL{
	namespace helper{
		// Count base case: 0.
		template<typename T, typename TTypeList>
		struct CountHelper : std::integral_constant<std::size_t, 0>{};
	}
	
	// Interface type alias.
	template<typename T, typename TTypeList> using Count = helper::CountHelper<T, TTypeList>;
	
	namespace helper{
		// Count recursive case.
		template<typename T, typename T0, typename... Ts>
		struct CountHelper<T, TypeList<T0, Ts...>> : std::integral_constant<std::size_t, (std::is_same<T, T0>{} ? 1 : 0) + Count<T, TypeList<Ts...>>{}>{};
	}
	
	// Alias for `Count > 0`.
	template<typename T, typename TTypeList>
	using Contains = std::integral_constant<bool, (Count<T, TTypeList>{} > 0)>;
}

#endif //MPL_COUNT_HPP
