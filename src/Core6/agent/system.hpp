/**
 * Core6
 * Copyright (C) 2020-2021 Kacper Chętkowski (kacper.chetkowski@gmail.com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CORE6_SYSTEM_HPP
#define CORE6_SYSTEM_HPP

#include <functional>
#include <MPL/MPL.hpp>

namespace c6{
	namespace helper{
		template<typename>
		struct SystemUnwrapper;
		
		template<typename ...Args>
		struct SystemUnwrapper<MPL::TypeList<Args...>>{
			using type = std::function<void(Args...)>;
		};
		
		template<typename>
		struct AddReference;
		
		template<typename ...Args>
		struct AddReference<MPL::TypeList<Args...>>{
			using type = MPL::TypeList<Args&...>;
		};
	}
	
	template<typename TConfig, typename TSignature, typename ...TArgs>
	class System{
			using Config = TConfig;
			using Signature = TSignature;
			using Key = typename Config::Key;
			using ThisType = System<Config, Signature>;
			
			template<typename T>
			using IsComponentFilter = std::integral_constant<bool, Config::template isComponent<T>()>;
			using ReqComponents = typename helper::AddReference<MPL::Filter<IsComponentFilter, Signature>>::type;
			using ExternArguments = MPL::TypeList<TArgs...>;
			
			using AllArguments = MPL::Concat<ExternArguments, ReqComponents>;
			
		public:
			using FunctionType = typename helper::SystemUnwrapper<AllArguments>::type;
			
			FunctionType function;
			
			System(const FunctionType& function) : function(function){}
	};
}

#endif //CORE6_SYSTEM_HPP
