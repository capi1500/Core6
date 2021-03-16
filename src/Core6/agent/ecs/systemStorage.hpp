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

#ifndef CORE6_SYSTEMSTORAGE_HPP
#define CORE6_SYSTEMSTORAGE_HPP

#include <tuple>
#include <vector>
#include "MPL/MPL.hpp"
#include "../system.hpp"
#include "../agent.hpp"

namespace c6{
	template<typename TConfig, typename TList, typename ...TArgs>
	class SystemStorage{
			using Config = TConfig;
			using SignatureList = TList;
			
			template<typename Signature>
			using System = System<Config, Signature, TArgs...>;
			
			template<typename... Ts>
			using TupleOfSystems = std::tuple<std::vector<System<Ts>>...>;
			
			using Agent = Agent<Config>;
		private:
			MPL::Rename<TupleOfSystems, SignatureList> m_systems;
		public:
			template<typename T>
			void addSystem(const T& system){
				std::get<std::vector<T>>(m_systems).push_back(system);
			}
			
			template<typename T>
			void executeOn(Agent* a, TArgs&&... args){
				auto& v = std::get<std::vector<T>>(m_systems);
				for(auto& s : v)
					a->template applySystem(s, std::forward<TArgs>(args)...);
			}
			
			void executeAllOn(Agent* a, TArgs&&... args){
				MPL::forTuple([this, a, &args...](auto& v){
					for(auto& s : v)
						a->template applySystem(s, std::forward<TArgs>(args)...);
				}, m_systems);
			}
	};
}

#endif //CORE6_SYSTEMSTORAGE_HPP
