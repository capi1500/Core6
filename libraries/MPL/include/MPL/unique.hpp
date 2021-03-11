#ifndef MPL_UNIQUE_HPP
#define MPL_UNIQUE_HPP

#include <type_traits>
#include "typeList.hpp"
#include "count.hpp"

namespace MPL{
	namespace helper{
		template<typename TTypeList>
		struct UniqueHelper : std::true_type{};
		
		template<typename T, typename... Ts>
		struct UniqueHelper<TypeList<T, Ts...>> : std::integral_constant<bool, (Count<T, TypeList<T, Ts...>>{} <= 1) && UniqueHelper<TypeList<Ts...>>{}>{
		};
	}
}
#endif //MPL_UNIQUE_HPP
