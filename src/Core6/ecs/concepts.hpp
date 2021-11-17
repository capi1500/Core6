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

namespace c6{
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
}