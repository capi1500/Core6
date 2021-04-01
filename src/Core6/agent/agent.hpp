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

#ifndef CORE6_AGENT_HPP
#define CORE6_AGENT_HPP

#include <Core6/utils/gizmo.hpp>
#include "system.hpp"
#include <cassert>
#include <MPL/MPL.hpp>
#include <Core6/systems/console.hpp>
#include "ecs/signatureStorage.hpp"
#include "ecs/componentStorage.hpp"

namespace c6{
	template<concepts::Config TConfig>
	class AgentGroup;
	
	template<concepts::Config TConfig>
	class Agent : public Gizmo{
			using ECSConfig = typename TConfig::ECSConfig;
			using Key = typename ECSConfig::Key;
			using ThisType = Agent<TConfig>;
			using AgentGroup = AgentGroup<TConfig>;
			using ComponentStorage = ComponentStorage<TConfig>;
			using SignatureStorage = SignatureStorage<TConfig>;
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
			
			template<concepts::Signature<ECSConfig> T, typename TF, typename ...TArgs>
			void expandSignatureCall(TF&& function, TArgs&&... args){
				using RequiredComponents = typename helper::SignatureKey<TConfig>::template SignatureComponents<T>;
				
				using Helper = MPL::Rename<ExpandCallHelper, RequiredComponents>;
				
				Helper::call(*this, function, std::forward<TArgs>(args)...);
			}
			
			template<typename ...Ts>
			struct ExpandCallHelper{
				template<typename TF, typename ...TArgs>
				static void call(ThisType& agent, TF&& function, TArgs&&... args){
					function(agent.getGroup()->m_componentStorage.template getComponent<Ts>(agent.m_id)..., std::forward<TArgs>(args)...);
				}
			};
		public:
			template<concepts::Tag<ECSConfig> T>
			bool hasTag() const noexcept{
				return m_key[ECSConfig::template tagBit<T>()];
			}
			
			template<concepts::Tag<ECSConfig> T>
			void addTag() noexcept{
				m_key[ECSConfig::template tagBit<T>()] = true;
			}
			
			template<concepts::Tag<ECSConfig> T>
			void deleteTag() noexcept{
				m_key[ECSConfig::template tagBit<T>()] = false;
			}
			
			template<concepts::Component<ECSConfig> T>
			bool hasComponent() const noexcept{
				return m_key[ECSConfig::template componentBit<T>()];
			}
			
			template<concepts::Component<ECSConfig> T>
			auto& getComponent() noexcept{
				if(not hasComponent<T>())
					Console::send(Message("trying to access component in agent, that doesn't have it"));
				return getGroup()->m_componentStorage.template getComponent<T>(m_id);
			}
			
			template<concepts::Component<ECSConfig> T, typename ...Targs>
			auto& addComponent(Targs&& ...args) noexcept{
				m_key[ECSConfig::template componentBit<T>()] = true;
				
				auto& c = getComponent<T>();
				c = T(MPL_FWD(args)...);
				
				return c;
			}
			
			template<concepts::Component<ECSConfig> T>
			void deleteComponent() noexcept{
				m_key[ECSConfig::template componentBit<T>()] = false;
			}
			
			template<concepts::Signature<ECSConfig> T>
			bool matchesSignature() const noexcept{
				const auto& sigKey = getGroup()->m_signatureStorage.template getSignatureKey<T>();
				
				return (sigKey & m_key) == sigKey;
			}
			
			template<concepts::Signature<ECSConfig> T, typename ...TArgs>
			void applySystem(const System<TConfig, T, TArgs...>& system, TArgs&&... args){
				if(matchesSignature<T>())
					expandSignatureCall<T>(system.function, std::forward<TArgs>(args)...);
			}
			
			Agent(typename AgentGroup::token, size_t id) : m_id(id){}
	};
}

#endif //CORE6_AGENT_HPP
