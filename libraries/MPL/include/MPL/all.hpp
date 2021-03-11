#ifndef MPL_ALL_HPP
#define MPL_ALL_HPP

#include <type_traits>
#include "typeList.hpp"
#include "rename.hpp"

namespace MPL{
	// All base case: return true.
	template<template<typename> class, typename...>
	struct All : std::true_type{
	};
	
	// All recursive case: test multiple types.
	template<template<typename> class TTypePred, typename T, typename... Ts>
	struct All<TTypePred, T, Ts...> : std::integral_constant<bool, TTypePred<T>{} && All<TTypePred, Ts...>{}>{};
	
	// Bind All's predicate to `TMF`.
	template<template<typename> class TMF>
	struct BoundAll{
		template<typename... Ts> using type = All<TMF, Ts...>;
	};
	
	// Unpack a type list into All.
	template<template<typename> class TMF, typename TL> using AllTypes = Rename<BoundAll<TMF>::template type, TL>;
}

#endif //MPL_ALL_HPP
