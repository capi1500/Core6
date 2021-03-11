#ifndef MPL_MAP_HPP
#define MPL_MAP_HPP

#include <type_traits>
#include "typeList.hpp"
#include "concat.hpp"

namespace MPL{
	namespace helper{
		// Map base case: empty list.
		template<template<typename> class TTypeFn, typename>
		struct MapHelper{
			using type = TypeList<>;
		};
	}
	
	// Interface type alias.
	template<template<typename> class TTypeFn, typename TTypeList> using Map = typename helper::MapHelper<TTypeFn, TTypeList>::type;
	
	namespace helper{
		// Map recursive case: non-empty list.
		template<template<typename> class TTypeFn, typename T, typename... Ts>
		struct MapHelper<TTypeFn, TypeList<T, Ts...>>{
			using type = Concat<TypeList<TTypeFn<T>>, Map<TTypeFn, TypeList<Ts...>>>;
		};
	}
}
#endif //MPL_MAP_HPP
