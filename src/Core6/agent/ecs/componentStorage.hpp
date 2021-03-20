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

#ifndef CORE6_COMPONENTSTORAGE_HPP
#define CORE6_COMPONENTSTORAGE_HPP

#include <vector>
#include <type_traits>
#include <MPL/MPL.hpp>
#include "../ecsConfig.hpp"
#include <Core6/config.hpp>

namespace c6{
	template <concepts::Config TConfig>
	class ComponentStorage{
			using ECSConfig = typename TConfig::ECSConfig;
			using ComponentList = typename ECSConfig::ComponentList;
			template<typename... Ts>
			using TupleOfVectors = std::tuple<std::vector<Ts>...>;
		private:
			MPL::Rename<TupleOfVectors, ComponentList> m_components;
		public:
			void grow(size_t size){
				MPL::forTuple([this, size](auto& v){
					v.resize(size);
				}, m_components);
			}
			
			template<typename T>
			auto& getComponent(size_t i) noexcept{
				return std::get<std::vector<T>>(m_components)[i];
			}
	};
}

#endif //CORE6_COMPONENTSTORAGE_HPP
