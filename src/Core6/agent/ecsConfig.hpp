/**
 * Core6
 * Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

namespace c6{
	MPL_STRONG_TYPEDEF(std::size_t, DataIndex);
	MPL_STRONG_TYPEDEF(std::size_t, AgentIndex);
	MPL_STRONG_TYPEDEF(std::size_t, HandleDataIndex);
	MPL_STRONG_TYPEDEF(int, Counter);
	
	template<typename... Ts> using Signature = MPL::TypeList<Ts...>;
	template<typename... Ts> using SignatureList = MPL::TypeList<Ts...>;
	template<typename... Ts> using ComponentList = MPL::TypeList<Ts...>;
	template<typename... Ts> using TagList = MPL::TypeList<Ts...>;
	
	template<typename TCompomentList, typename TTagList, typename TSignatureList>
	struct ECSConfig{
		using ComponentList = typename TCompomentList::TypeList;
		using TagList = typename TTagList::TypeList;
		using SignatureList = typename TSignatureList::TypeList;
		using ThisType = ECSConfig<ComponentList, TagList, SignatureList>;
		
		template<typename T>
		static constexpr bool isComponent() noexcept{
			return MPL::Contains<T, ComponentList>{};
		}
		
		template<typename T>
		static constexpr bool isTag() noexcept{
			return MPL::Contains<T, TagList>{};
		}
		
		template<typename T>
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
		
		template<typename T>
		static constexpr std::size_t componentID() noexcept{
			return MPL::IndexOf<T, ComponentList>{};
		}
		
		template<typename T>
		static constexpr std::size_t tagID() noexcept{
			return MPL::IndexOf<T, TagList>{};
		}
		
		template<typename T>
		static constexpr std::size_t signatureID() noexcept{
			return MPL::IndexOf<T, SignatureList>{};
		}
		
		using Key = std::bitset<componentCount() + tagCount()>;
		
		template<typename T>
		static constexpr std::size_t componentBit() noexcept{
			return componentID<T>();
		}
		
		template<typename T>
		static constexpr std::size_t tagBit() noexcept{
			return componentCount() + tagID<T>();
		}
	};
}

#endif //CORE6_ECSCONFIG_HPP
