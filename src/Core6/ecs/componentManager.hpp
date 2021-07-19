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

#include <tuple>
#include <vector>
#include <MPL/MPL.hpp>
#include "Core6/ecs/config.hpp"

namespace c6{
	template<concepts::Config Config>
	class ComponentManager{
			using ComponentList = typename Config::ComponentList;
			template<class... Ts>
			using TupleOfVectors = std::tuple<std::vector<Ts>...>;
			using Components = MPL::Rename<TupleOfVectors, ComponentList>;
		private:
			Components components;
		public:
			void resize(size_t size){
				MPL::forTuple([this, size](auto& v){
					v.resize(size);
				}, components);
			}
			
			template<concepts::Component<Config> T>
			T& getComponent(std::size_t i) noexcept{
				return std::get<std::vector<T>>(components)[i];
			}
	};
}

