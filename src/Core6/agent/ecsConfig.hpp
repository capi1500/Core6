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

#ifndef CORE6_ECSCONFIG_HPP
#define CORE6_ECSCONFIG_HPP

#include <MPL/MPL.hpp>
#include <bitset>
#include <Core6/utils/commonFunctions.hpp>

namespace c6{
	template<class... Ts> using Signature = MPL::TypeList<Ts...>;
	template<class... Ts> using SignatureList = MPL::TypeList<Ts...>;
	template<class... Ts> using ComponentList = MPL::TypeList<Ts...>;
	template<class... Ts> using TagList = MPL::TypeList<Ts...>;
	
	template<class TCompomentList, class TTagList, class TSignatureList, class TSystemTimeList, class TSystemRenderList>
	struct ECSConfig{
		using ComponentList = typename TCompomentList::TypeList;
		using TagList = typename TTagList::TypeList;
		using SignatureList = typename TSignatureList::TypeList;
		using SystemTimeList = typename TSystemTimeList::TypeList;
		using SystemRenderList = typename TSystemRenderList::TypeList;
		using ThisType = ECSConfig<ComponentList, TagList, SignatureList, SystemTimeList, SystemRenderList>;
		
		template<class T>
		static constexpr bool isComponent() noexcept{
			return MPL::Contains<T, ComponentList>{};
		}
		
		template<class T>
		static constexpr bool isTag() noexcept{
			return MPL::Contains<T, TagList>{};
		}
		
		template<class T>
		static constexpr bool isSignature() noexcept{
			return MPL::Contains<T, SignatureList>{};
		}
		
		static constexpr std::size_t componentCount() noexcept{
			return MPL::size<ComponentList>();
		}
		
		static constexpr std::size_t tagCount() noexcept{
			return MPL::size<TagList>();
		}
		
		static constexpr std::size_t signatureCount() noexcept{
			return MPL::size<SignatureList>();
		}
		
		template<class T>
		static constexpr std::size_t componentID() noexcept{
			return MPL::IndexOf<T, ComponentList>{};
		}
		
		template<class T>
		static constexpr std::size_t tagID() noexcept{
			return MPL::IndexOf<T, TagList>{};
		}
		
		template<class T>
		static constexpr std::size_t signatureID() noexcept{
			return MPL::IndexOf<T, SignatureList>{};
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
		template<class T> concept ECSConfig = requires{
			typename T::ComponentList;
			typename T::TagList;
			typename T::SignatureList;
			typename T::SystemTimeList;
			typename T::SystemRenderList;
			{T::template isComponent<helper::Obj>()} -> std::same_as<bool>;
			{T::template isTag<helper::Obj>()} -> std::same_as<bool>;
			{T::template isSignature<helper::Obj>()} -> std::same_as<bool>;
			{T::componentCount()} -> std::convertible_to<std::size_t>;
			{T::tagCount()} -> std::convertible_to<std::size_t>;
			{T::signatureCount()} -> std::convertible_to<std::size_t>;
			{T::template componentID<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template tagID<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template signatureID<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template componentBit<helper::Obj>()} -> std::convertible_to<std::size_t>;
			{T::template tagBit<helper::Obj>()} -> std::convertible_to<std::size_t>;
		};
		
		namespace helper{
			template<ECSConfig Config, class Sig>
			struct IsSignature{
				static constexpr bool value = Config::template isSignature<Sig>();
			};
		}
		
		template<class Config, class Sig> concept IsSignature = requires{
			helper::IsSignature<Config, Sig>::value;
		};
	}
}

#endif //CORE6_ECSCONFIG_HPP
