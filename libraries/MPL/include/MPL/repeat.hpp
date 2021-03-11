#ifndef MPL_REPEAT_HPP
#define MPL_REPEAT_HPP

#include <type_traits>
#include "typeList.hpp"
#include "typeListOps.hpp"

namespace MPL{
	namespace helper{
		// Repeat recursive case: `TTimes` repetitions left.
		template<std::size_t TTimes, typename T>
		struct RepeatHelper{
			using type = PushBack<typename RepeatHelper<TTimes - 1, T>::type, T>;
		};
		
		template<typename T>
		struct RepeatHelper<0, T>{
			using type = TypeList<>;
		};
	}
	
	// Interface type alias.
	template<std::size_t TTimes, typename T>
	using Repeat = typename helper::RepeatHelper<TTimes, T>::type;
}
#endif //MPL_REPEAT_HPP
