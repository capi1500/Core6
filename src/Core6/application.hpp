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

#ifndef CORE6_APPLICATION_HPP
#define CORE6_APPLICATION_HPP

#include <Core6/framework.hpp>
#include <Core6/systems/console.hpp>
#include <SFML/System/Clock.hpp>
#include <Core6/state/finiteStateMachine.hpp>
#include <Core6/scene.hpp>
#include <Core6/plugin/plugin.hpp>
#include <Core6/config.hpp>

namespace c6{
	/**
	 * @brief
	 * class managing running the app. It listens for sf::Events.
	 *
	 *
	 */
	template<concepts::Config Config>
	class Application : public Listener<sf::Event>{
		protected:
			using Framework = Framework<Config>;
			using Scene = Scene<Config>;
			
			sf::Clock m_clock;
			FiniteStateMachine m_finiteStateMachine;
			std::vector<Plugin*> m_plugins;
			bool m_active;
			
			Scene* getScene(){
				return dynamic_cast<Scene*>(m_finiteStateMachine.getCurrentState());
			}
			
			void loadPlugins(const Path& path){
				auto loadPlugin = [this](const std::string name){
					m_plugins.push_back(new Plugin());
					m_plugins.back()->load(name);
				};
				path.execute(loadPlugin, "true", ".dll");
			}
		public:
			void onSignal(const sf::Event& signal) override{
				if(signal.type == sf::Event::Closed)
					m_active = false;
			}
			
			virtual void run() = 0;
			virtual void init(){
				m_active = true;
				Framework::getInputHandler().add(this);
			}
			
			virtual ~Application(){
				Console::send(Message("Closing Application", MessageType::Debug));
				Console::send(Message("Clearing Finite State Machine", MessageType::Debug));
				m_finiteStateMachine.clear();
				m_finiteStateMachine.processEvents();
				Console::send(Message("All finite states closed", MessageType::Debug));
				Console::send(Message("Destroing templates", MessageType::Debug));
				EntryPoint::destroy();
				Console::send(Message("Templates destroyed", MessageType::Debug));
				Console::send(Message("Unloadign plugins", MessageType::Debug));
				for(auto& p : m_plugins){
					delete p;
					p = nullptr;
				}
				m_plugins.clear();
				Console::send(Message("Plugins unloaded", MessageType::Debug));
			}
	};
}

#endif //CORE6_APPLICATION_HPP
