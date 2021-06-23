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

#pragma once

#include <functional>
#include <Core6/ecs/config.hpp>
#include <MPL/MPL.hpp>

namespace c6{
	template<concepts::Config Config>
	class EntityComponentSystem;
	
	template<concepts::Config Config, class Signature, class... TArgs>
	requires concepts::Signature<Signature, Config>
	class System{
			template<class>
			struct AddReference;
			
			template<class... Args>
			struct AddReference<MPL::TypeList<Args...>>{
				using type = MPL::TypeList<Args& ...>;
			};
			
			using Key = typename Config::Key;
			
			template<class T>
			using IsComponentFilter = std::integral_constant<bool, Config::template isComponent<T>()>;
			template<typename T>
			using IsTagFilter = std::integral_constant<bool, Config::template isTag<T>()>;
			
			using RequiredComponents = typename AddReference<MPL::Filter<IsComponentFilter, Signature>>::type;
			using RequiredTags = typename AddReference<MPL::Filter<IsTagFilter, Signature>>::type;
			using Arguments = MPL::Concat<RequiredComponents, MPL::TypeList<TArgs...>>;
			
			template<class>
			struct SystemUnwrapper;
			
			template<class... Args>
			struct SystemUnwrapper<MPL::TypeList<Args...>>{
				using type = std::function<void(const EntityComponentSystem<Config>&, EntityId, Args...)>;
			};
			
			static constexpr Key initKey(){
				Key key;
				
				MPL::forTypes<RequiredComponents>([&](auto t){
					key[Config::template componentBit<MPL_TYPE(t)>()] = true;
				});
				MPL::forTypes<RequiredTags>([&](auto t){
					key[Config::template tagBit<MPL_TYPE(t)>()] = true;
				});
				
				return key;
			}
		public:
			using FunctionType = typename SystemUnwrapper<Arguments>::type;
			
			static constexpr Key key = initKey();
			const FunctionType function;
			
			System(const FunctionType& function) noexcept : function(function){};
			
			System(FunctionType&& function) noexcept : function(std::forward<>(function)){};
	};
}
