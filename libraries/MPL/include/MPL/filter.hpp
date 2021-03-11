#ifndef MPL_FILTER_HPP
#define MPL_FILTER_HPP

#include <type_traits>
#include "typeList.hpp"
#include "concat.hpp"

namespace MPL{
	namespace helper{
		// Filter base case: empty list.
		template<template<typename> class TTypePred, typename>
		struct FilterHelper{
			using type = TypeList<>;
		};
	}
	
	// Interface type alias.
	template<template<typename> class TTypePred, typename TTypeList>
	using Filter = typename helper::FilterHelper<TTypePred, TTypeList>::type;
	
	namespace helper{
		// Filter recursive case: concat matching types.
		template<template<typename> class TTypePred, typename T, typename... Ts>
		struct FilterHelper<TTypePred, TypeList<T, Ts...>>{
			using Next = Filter<TTypePred, TypeList<Ts...>>;
			
			using type = std::conditional_t<TTypePred<T>{}, Concat<TypeList<T>, Next>, Next>;
		};
	}
}
#endif //MPL_FILTER_HPP
