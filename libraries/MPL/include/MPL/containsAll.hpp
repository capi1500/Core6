#ifndef MPL_CONTAINSALL_HPP
#define MPL_CONTAINSALL_HPP

#include <type_traits>
#include "typeList.hpp"
#include "count.hpp"

namespace MPL{
	namespace helper{
		template<typename TCheckTypeList, typename TTypeList>
		struct ContainsAllHelper;
	}
	template<typename TCheckTypeList, typename TTypeList> using ContainsAll = typename helper::ContainsAllHelper<TCheckTypeList, TTypeList>::type;
	
	namespace helper{
		template<typename T, typename... TRest, typename TTypeList>
		struct ContainsAllHelper<TypeList<T, TRest...>, TTypeList> : std::integral_constant<bool, Contains<T, TTypeList>{} && ContainsAll<TypeList<TRest...>, TTypeList>{}>{
		};
		
		template<typename TTypeList>
		struct ContainsAllHelper<TypeList<>, TTypeList> : std::true_type{
		};
	}
}
#endif //MPL_CONTAINSALL_HPP
