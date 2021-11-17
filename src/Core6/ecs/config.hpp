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
#include "concepts.hpp"
#include "components.hpp"

namespace c6{
	/**
	 * Class which holds the configuration of the Entity Component System
	 * @tparam TComponentList - list of components
	 * @tparam TTagList - list of tags
	 */
	template<class TComponentList, class TTagList>
	class Config{
			using ThisType = Config<TComponentList, TTagList>;
			using DefaultComponents = MPL::TypeList<component::EntityState,
			                                        component::Drawable,
			                                        component::Transformable,
			                                        component::Physic,
													Widget<ThisType>>;
		public:
			using ComponentList = MPL::Concat<TComponentList, DefaultComponents>;
			using TagList = TTagList;
			
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
					using IsInvalidFilter = std::integral_constant<bool, !(ThisType::template isTag<T>() || ThisType::template isComponent<T>())>;
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
}
