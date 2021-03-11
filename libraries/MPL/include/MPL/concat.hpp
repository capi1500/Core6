#ifndef MPL_CONCACT_HPP
#define MPL_CONCACT_HPP

#include "typeList.hpp"

namespace MPL{
	namespace helper{
		// Concat base case: empty lists.
		template<typename...>
		struct ConcatHelper{
			using type = TypeList<>;
		};
	}
	
	// Interface type alias.
	template<typename... TTypeLists> using Concat = typename helper::ConcatHelper<TTypeLists...>::type;
	
	namespace helper{
		// Concat base case: single non-empty list.
		template<typename... Ts>
		struct ConcatHelper<TypeList<Ts...>>{
			using type = TypeList<Ts...>;
		};
		
		// Concat recursive case: multiple lists.
		template<typename... Ts0, typename... Ts1, typename... TRest>
		struct ConcatHelper<TypeList<Ts0...>, TypeList<Ts1...>, TRest...>{
			using type = Concat<TypeList<Ts0..., Ts1...>, TRest...>;
		};
	}
}
#endif //MPL_CONCACT_HPP
