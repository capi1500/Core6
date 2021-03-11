#ifndef MPL_METAFOR_HPP
#define MPL_METAFOR_HPP

#include "macros.hpp"
#include <tuple>

namespace MPL{
	namespace helper{
		template<typename TFunction, typename TTuple, std::size_t... TIndices>
		constexpr decltype(auto) tupleApply(TFunction&& function, TTuple&& tuple, std::index_sequence<TIndices...>){
			return MPL_FWD(function)(std::get<TIndices>(MPL_FWD(tuple))...);
		}
	}
	
	// "Unpacks" the contents of a tuple inside a function call.
	template<typename TFunction, typename TTuple>
	constexpr decltype(auto) tupleApply(TFunction&& function, TTuple&& tuple){
		using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<TTuple>>::value>;
		return helper::tupleApply(MPL_FWD(function), MPL_FWD(tuple), Indices{});
	}
	
	// Invokes a function on every passed object.
	template<typename TFunction, typename... Ts>
	constexpr decltype(auto) forArgs(TFunction&& function, Ts&& ... args){
		return (void)std::initializer_list<int>{(function(MPL_FWD(args)), 0)...};
	}
	
	// Invokes a function on every element of a tuple.
	template<typename TFunction, typename TTuple>
	constexpr decltype(auto) forTuple(TFunction&& function, TTuple&& tuple){
		return tupleApply([&function](auto&& ... xs){
			forArgs(function, MPL_FWD(xs)...);
		}, MPL_FWD(tuple));
	}
}

#endif //MPL_METAFOR_HPP
