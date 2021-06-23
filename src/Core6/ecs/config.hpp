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

#include <MPL/MPL.hpp>
#include <bitset>

namespace c6{
	MPL_STRONG_TYPEDEF(std::size_t, EntityId);
	MPL_STRONG_TYPEDEF(std::size_t, DataId);
	MPL_STRONG_TYPEDEF(std::size_t, HandleDataId);
	MPL_STRONG_TYPEDEF(int, HandleCounter);
	
	/**
	 * Class which holds the configuration of the Entity Component System
	 * @tparam TComponentList - list of components
	 * @tparam TTagList - list of tags
	 */
	template<class TComponentList, class TTagList/*, class TSignatureList*/>
	class Config{
		public:
			using ComponentList = TComponentList;
			using TagList = TTagList;
			
			using ThisType = Config<ComponentList, TagList>;
			
			template<class T>
			static constexpr bool isComponent() noexcept{
				return MPL::Contains<T, ComponentList>{};
			}
			
			template<class T>
			static constexpr bool isTag() noexcept{
				return MPL::Contains<T, TagList>{};
			}
		private:
			template<class Sig>
			class IsSignature{
					template<class T>
					using IsInvalidFilter = std::integral_constant<bool, !(ThisType::isTag<T>() || ThisType::isComponent<T>())>;
				public:
					static constexpr bool value = MPL::Filter<IsInvalidFilter, Sig>::size == 0;
			};
		public:
			template<class T>
			static constexpr bool isSignature() noexcept{
				return IsSignature<T>::value;
			}
			
			static constexpr std::size_t componentCount() noexcept{
				return MPL::size<ComponentList>();
			}
			
			static constexpr std::size_t tagCount() noexcept{
				return MPL::size<TagList>();
			}
			
			template<class T>
			static constexpr std::size_t componentID() noexcept{
				return MPL::IndexOf<T, ComponentList>{};
			}
			
			template<class T>
			static constexpr std::size_t tagID() noexcept{
				return MPL::IndexOf<T, TagList>{};
			}
			
			using Key = std::bitset<componentCount() + tagCount()>;
			
			template<class T>
			static constexpr std::size_t componentBit() noexcept{
				return componentID<T>();
			}
			
			template<class T>
			static constexpr std::size_t tagBit() noexcept{
				return componentCount() + tagID<T>();
			}
	};
	
	namespace concepts{
		namespace helper{
			struct Obj{};
		}
		
		template<class T>
		concept Config = requires{
			typename T::ComponentList;
			typename T::TagList;
			typename T::Key;
			{T::template isComponent<helper::Obj>()} -> std::same_as<bool>;
			{T::template isTag<helper::Obj>()} -> std::same_as<bool>;
			{T::template isSignature<helper::Obj>()} -> std::same_as<bool>;
			{T::componentCount()} -> std::convertible_to<std::size_t>;
			{T::tagCount()} -> std::convertible_to<std::size_t>;
			{T::template componentID<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template tagID<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template componentBit<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template tagBit<helper::Obj>()} -> std::convertible_to<std::size_t>;
		};
		
		namespace helper{
			template<Config TConfig, class Component>
			struct IsComponent{
				static constexpr bool value = TConfig::template isComponent<Component>();
			};
			
			template<Config TConfig, class Tag>
			struct IsTag{
				static constexpr bool value = TConfig::template isTag<Tag>();
			};
			
			template<Config TConfig, class T>
			struct IsComponentOrTag{
				static constexpr bool value = IsComponent<TConfig, T>::value || IsTag<TConfig, T>::value;
			};
			
			template<Config TConfig, class Sig>
			struct IsSignature{
				static constexpr bool value = TConfig::template isSignature<Sig>();
			};
		}
		
		template<class Sig, class Config>
		concept Signature = helper::IsSignature<Config, Sig>::value;
		
		template<class Comp, class Config>
		concept Component = helper::IsComponent<Config, Comp>::value;
		
		template<class T, class Config>
		concept Tag = helper::IsTag<Config, T>::value;
		
		template<class T, class Config>
		concept ComponentOrTag = helper::IsComponentOrTag<Config, T>::value;
	}
	
	template<class... Ts> using Signature = MPL::TypeList<Ts...>;
	template<class... Ts> using SignatureList = MPL::TypeList<Ts...>;
	template<class... Ts> using ComponentList = MPL::TypeList<Ts...>;
	template<class... Ts> using TagList = MPL::TypeList<Ts...>;
}
