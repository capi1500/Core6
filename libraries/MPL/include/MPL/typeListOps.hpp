#ifndef MPL_TYPELISTOPS_HPP
#define MPL_TYPELISTOPS_HPP

#include <type_traits>
#include <tuple>
#include "utils/metaFor.hpp"
#include "type.hpp"
#include "typeList.hpp"
#include "rename.hpp"
#include "concat.hpp"
#include "map.hpp"

namespace MPL{
	// Type list as a tuple.
	template<typename TTypeList> using Tuple = Rename<std::tuple, TTypeList>;
	
	// Type list as a tuple of Type<T>.
	template<typename TTypeList> using TypeTuple = Tuple<Map<Type, TTypeList>>;
	
	// "Nth" element of a type list.
	template<std::size_t TIndex, typename TTypeList> using Nth = std::tuple_element_t<TIndex, Tuple<TTypeList>>;
	
	// Adds a type to the back of a type list.
	template<typename TTypeList, typename T> using PushBack = Concat<TTypeList, TypeList<T>>;
	
	// Adds a type to the front of a type list.
	template<typename TTypeList, typename T> using PushFront = Concat<TypeList<T>, TTypeList>;
	
	// Size of a type list.
	template<typename TTypeList>
	constexpr auto size() noexcept{
		return TTypeList::size;
	}
	
	// Execute a function for every type in a type list, wrapped in a
	// Type<T>.
	template<typename TTypeList, typename TFunction>
	constexpr void forTypes(TFunction&& mFunction) noexcept{
		forTuple(mFunction, TypeTuple<TTypeList>{});
	}
	
	// First type of a type list.
	template<typename TTypeList> using Head = Nth<0, TTypeList>;
	
	// Last type of a type list.
	template<typename TTypeList> using Tail = Nth<size<TTypeList>() - 1, TTypeList>;
	
	template <class Wrapper, template <class...> class Template>
	struct unwrap;
	
	template <class... Ts, template <class...> class Template>
	struct unwrap<TypeList<Ts...>, Template> {
		using type = Template<Ts...>;
	};
}
#endif //MPL_TYPELISTOPS_HPP
