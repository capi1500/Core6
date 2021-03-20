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

#ifndef CORE6_AGENTGROUP_HPP
#define CORE6_AGENTGROUP_HPP

#include <Core6/utils/group.hpp>
#include <iostream>
#include "ecs/componentStorage.hpp"
#include "ecs/signatureStorage.hpp"
#include "agent.hpp"
#include "system.hpp"
#include "factory.hpp"
#include "ecs/systemStorage.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <Core6/framework.hpp>

namespace c6{
	template<concepts::Config TConfig>
	class AgentGroup : public Group{
			using ECSConfig = typename TConfig::ECSConfig;
			using SignatureBitsetStorage = SignatureStorage<TConfig>;
			using ComponentStorage = ComponentStorage<TConfig>;
			
			using TimeSystemList = typename ECSConfig::SystemTimeList;
			using RenderSystemList = typename ECSConfig::SystemRenderList;
			using TimeSystemStorage = SystemStorage<TConfig, TimeSystemList, const sf::Time&>;
			using RenderSystemStorage = SystemStorage<TConfig, RenderSystemList, sf::RenderWindow&>;
			
			using Framework = Framework<TConfig>;
			using Agent = Agent<TConfig>;
		private:
			SignatureBitsetStorage m_signatureStorage;
			ComponentStorage m_componentStorage;
			
			TimeSystemStorage m_timeSystemStorage;
			RenderSystemStorage m_renderSystemStorage;
			
			struct token{};
		public:
			template<typename T, typename ...TArgs>
			void executeSystem(const System<TConfig, T, TArgs...>& system, TArgs&&... args){
				for(size_t i = 0; i < count(); i++){
					if(m_members[i] != nullptr and m_members[i]->isExists()){
						static_cast<Agent*>(m_members[i])->template applySystem(system, std::forward<TArgs>(args)...);
					}
				}
			}
			/*
			template<typename T, typename ...TArgs>
			void executeSystem(const System<Config, T, TArgs...>& system, TArgs... args){
				for(size_t i = 0; i < count(); i++){
					if(m_members[i] != nullptr and m_members[i]->isExists()){
						static_cast<Agent*>(m_members[i])->template applySystem(system, std::forward<TArgs>(args)...);
					}
				}
			}*/
			
			template<typename ...TArgs>
			void newAgent(Factory<TConfig, TArgs...>& factory, TArgs... args){
				Agent* a = new Agent(token(), count());
				m_componentStorage.grow(count() + 1);
				addToBack(a);
				factory.init(*a, std::forward<TArgs>(args)...);
			}
			/*
			template<typename ...TArgs>
			void newAgent(Factory<Config>& factory, TArgs... args){
				Agent* a = new Agent(token(), count());
				m_componentStorage.grow(count() + 1);
				addToBack(a);
				factory.init(*a, std::forward<TArgs>(args)...);
			}*/
			
			template<typename T>
			void addTimeSystem(const System<TConfig, T, const sf::Time&>& timeSystem){
				m_timeSystemStorage.template addSystem(timeSystem);
			}
			
			template<typename T>
			void addRenderSystem(const System<TConfig, T, sf::RenderWindow&>& renderSystem){
				m_renderSystemStorage.template addSystem(renderSystem);
			}
			
			void update(const sf::Time& time) override{
				for(size_t i = 0; i < count(); i++){
					if(m_members[i] != nullptr and m_members[i]->isExists())
						m_timeSystemStorage.executeAllOn(static_cast<Agent*>(m_members[i]), time);
				}
			}
			
			void draw() override{
				for(size_t i = 0; i < count(); i++){
					if(m_members[i] != nullptr and m_members[i]->isExists())
						m_renderSystemStorage.executeAllOn(static_cast<Agent*>(m_members[i]), Framework::getRenderer().get());
				}
			}
			
			friend Agent;
	};
}

#endif //CORE6_AGENTGROUP_HPP
