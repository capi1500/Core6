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

#ifndef CORE6_AGENT_HPP
#define CORE6_AGENT_HPP

#include <Core6/utils/gizmo.hpp>
#include "system.hpp"
#include <cassert>
#include <MPL/MPL.hpp>
#include "ecs/signatureStorage.hpp"
#include "ecs/componentStorage.hpp"

namespace c6{
	template <typename TConfig>
	class AgentGroup;
	
	template <typename TConfig>
	class Agent : public Gizmo{
			using Config = TConfig;
			using Key = typename Config::Key;
			using ThisType = Agent<Config>;
			using AgentGroup = AgentGroup<Config>;
			using ComponentStorage = ComponentStorage<Config>;
			using SignatureStorage = SignatureStorage<Config>;
		private:
			Key m_key;
			size_t m_id;
			
			AgentGroup* getGroup() noexcept{
				return static_cast<AgentGroup*>(m_parent);
			};
			
			const AgentGroup* getGroup() const noexcept{
				return static_cast<AgentGroup*>(m_parent);
			};
			
			template<typename ...Ts>
			struct ExpandCallHelper;
			
			template<typename T, typename TF>
			void expandSignatureCall(TF&& function){
				static_assert(Config::template isSignature<T>(), "ERROR: c6::Agent::expandSignatureCall(): Type is not a Signature");
				
				using RequiredComponents = typename helper::SignatureKey<Config>::template SignatureComponents<T>;
				
				using Helper = MPL::Rename<ExpandCallHelper, RequiredComponents>;
				
				Helper::call(*this, function);
			}
			
			template<typename ...Ts>
			struct ExpandCallHelper{
				template<typename TF>
				static void call(ThisType& agent, TF&& function){
					function(agent.getGroup()->m_componentStorage.template getComponent<Ts>(agent.m_id)...);
				}
			};
		public:
			template<typename T>
			bool hasTag() const noexcept{
				static_assert(Config ::template isTag<T>(), "ERROR: c6::Agent::hasTag(): Type is not a Tag");
				return m_key[Config::template tagBit<T>()];
			}
			
			template<typename T>
			void addTag() noexcept{
				static_assert(Config ::template isTag<T>(), "ERROR: c6::Agent::addTag(): Type is not a Tag");
				m_key[Config::template tagBit<T>()] = true;
			}
			
			template<typename T>
			void deleteTag() noexcept{
				static_assert(Config ::template isTag<T>(), "ERROR: c6::Agent::deleteTag(): Type is not a Tag");
				m_key[Config::template tagBit<T>()] = false;
			}
			
			template<typename T>
			bool hasComponent() const noexcept{
				static_assert(Config::template isComponent<T>(), "ERROR: c6::Agent::hasComponent(): Type is not a Component");
				return m_key[Config::template componentBit<T>()];
			}
			
			template<typename T>
			auto& getComponent() noexcept{
				static_assert(Config::template isComponent<T>(), "ERROR: c6::Agent::getComponent(): Type is not a Component");
				assert(hasComponent<T>());
				
				return getGroup()->m_componentStorage.template getComponent<T>(m_id);
			}
			
			template<typename T, typename ...Targs>
			auto& addComponent(Targs&& ...args) noexcept{
				static_assert(Config::template isComponent<T>(), "ERROR: c6::Agent::addComponent(): Type is not a Component");
				
				m_key[Config::template componentBit<T>()] = true;
				
				auto& c = getComponent<T>();
				c = T(MPL_FWD(args)...);
				
				return c;
			}
			
			template<typename T>
			void deleteComponent() noexcept{
				static_assert(Config::template isComponent<T>(), "ERROR: c6::Agent::deleteComponent(): Type is not a Component");
				m_key[Config::template componentBit<T>()] = false;
			}
			
			template<typename T>
			bool matchesSignature() const noexcept{
				static_assert(Config::template isSignature<T>(), "ERROR: c6::Agent::matchesSignature(): Type is not a Signature");
				
				const auto& sigKey = getGroup()->m_signatureStorage.template getSignatureKey<T>();
				
				return (sigKey & m_key) == sigKey;
			}
			
			template<typename T>
			void applySystem(const System<Config, T>& system){
				if(matchesSignature<T>())
					expandSignatureCall<T>(system.function);
			}
			
			Agent(typename AgentGroup::token, size_t id) : m_id(id) {};
	};
}

#endif //CORE6_AGENT_HPP
