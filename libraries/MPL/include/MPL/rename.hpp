#ifndef MPL_RENAME_HPP
#define MPL_RENAME_HPP

namespace MPL{
	namespace helper{
		template<template<typename...> class TNewName, typename T>
		struct RenameHelper;
		
		// "Renames" `TOldName<Ts...>` to `TNewName<Ts...>`.
		template<template<typename...> class TNewName,
				template<typename...> class TOldName, typename... Ts>
		struct RenameHelper<TNewName, TOldName<Ts...>>{
			using type = TNewName<Ts...>;
		};
	}
	
	template<template<typename...> class TNewName, typename T>
	using Rename = typename helper::RenameHelper<TNewName, T>::type;
}

#endif //MPL_RENAME_HPP
