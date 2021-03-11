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

#ifndef CORE6_AGENTGROUP_HPP
#define CORE6_AGENTGROUP_HPP

#include <Core6/utils/group.hpp>
#include "ecs/componentStorage.hpp"
#include "ecs/signatureStorage.hpp"
#include "agent.hpp"
#include "system.hpp"

namespace c6{
	template <typename TConfig>
	class AgentGroup : public Group{
			using Config = TConfig;
			using SignatureBitsetStorage = SignatureStorage<Config>;
			using ComponentStorage = ComponentStorage<Config>;
			using Agent = Agent<Config>;
		private:
			SignatureBitsetStorage m_signatureStorage;
			ComponentStorage m_componentStorage;
			
			struct token{};
		public:
			template<typename T>
			void executeSystem(const System<Config, T>& system){
				for(size_t i = 0; i < count(); i++){
					if(m_members[i] != nullptr and m_members[i]->isExists()){
						static_cast<Agent*>(m_members[i])->template applySystem(system);
					}
				}
			}
			
			Agent& newAgent(){
				Agent* a = new Agent(token(), count());
				m_componentStorage.grow(count() + 1);
				addToBack(a);
				return *a;
			}
			
			friend Agent;
	};
}

#endif //CORE6_AGENTGROUP_HPP
