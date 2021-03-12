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

#ifndef CORE6_SCENE_HPP
#define CORE6_SCENE_HPP

#include <Core6/state/finiteState.hpp>
#include <Core6/camera.hpp>
#include <Core6/signal/listener.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <Core6/agent/agentGroup.hpp>
#include "framework.hpp"
#include <Core6/agent/components.hpp>

namespace c6{
	/**
	 * @brief Class managing storing, updating and drawing Agents
	 */
	template<typename TConfig>
	class Scene : public AgentGroup<TConfig>, public FiniteState, public Listener<sf::Event>{
		using Config = TConfig;
		private:
			Camera m_camera;
			
			void resize(size_t size){
				while(size >= Group::count())
					this->template addToBack(new Group);
			};
		public:
			/**
			 * @brief draw all stored Agents
			 */
			void draw() override{
				Framework::getRenderer()->lock();
				Framework::getRenderer()->get().setView(m_camera);
				Framework::getRenderer()->get().clear();
				this->template executeSystem(ecs::system::draw<Config>, Framework::getRenderer()->get());
				Framework::getRenderer()->get().display();
				Framework::getRenderer()->unlock();
			};
			
			void onSignal(const sf::Event& signal) override{
				if(isActive()){
					Listener::onSignal(signal);
				}
			};
			
			/**
			 * @brief constructor of scene
			 */
			Scene(FiniteStateMachine& finiteStateMachine, const std::function<void(const sf::Event&)>& f) : FiniteState(finiteStateMachine), Listener<sf::Event>(f){
				Framework::getInput()->add(this);
			};
			
			/**
			 * @brief constructor of scene
			 */
			Scene(FiniteStateMachine& finiteStateMachine) : FiniteState(finiteStateMachine), Listener<sf::Event>(){
				Framework::getInput()->add(this);
			}
			
			~Scene(){
				Framework::getInput()->remove(this);
			};
	};
}


#endif //CORE6_SCENE_HPP
