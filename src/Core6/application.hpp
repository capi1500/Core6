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

#include <SFML/System/Clock.hpp>
#include <Core6/systems/console.hpp>
#include <Core6/framework.hpp>
#include <Core6/systems/inputHandler.hpp>
#include <iostream>
#include "scene.hpp"

namespace c6{
	template<concepts::Config Config>
	class Application{
		private:
			sf::Clock clock;
			Console console = ConsoleBuilder().create();
			StateMachine scenes;
			
			bool active = true;
			
			Scene<Config>* getScene(){
				return dynamic_cast<Scene<Config>*>(scenes.getCurrentState());
			}
		protected:
			StateMachine& getScenes(){
				return scenes;
			}
			
			virtual void init(){
				Framework::getRenderer()->attachConsole(this->console);
				Framework::getResourceManager()->attachConsole(this->console);
				Framework::getSoundboard()->attachConsole(this->console);
				Framework::getInputHandler()->addListener(new SimpleListener<sf::Event>(
						[this](const sf::Event& event){
							if(event.type == sf::Event::Closed)
								close();
						}
				));
			}
			
			virtual void handleEvents([[maybe_unused]] Scene<Config>& scene){
				if(Framework::getRenderer().isCreated())
					Framework::getInputHandler()->handleEvents(Framework::getRenderer().get());
			}
			
			virtual void update(Scene<Config>& scene, const sf::Time& time){
				scene.update(time);
			}
			
			virtual void draw(Scene<Config>& scene, sf::RenderStates states, sf::Color background){
				if(Framework::getRenderer().isCreated() && Framework::getRenderer()->isOpen()){
					Framework::getRenderer()->clear(background);
					scene.draw(*Framework::getRenderer().get(), states);
					Framework::getRenderer()->display();
				}
			}
			
			virtual void clean(){
				scenes.clear();
				scenes.processEvents();
				Framework::getRenderer().destroy();
				Framework::getResourceManager().destroy();
				Framework::getInputHandler().destroy();
				Framework::getSoundboard().destroy();
			}
		public:
			Application() = default;
			explicit Application(Console console) : console(console){}
			
			void run(){
				init();
				sf::Time time;
				Scene<Config>* scene;
				while(active){
					time = clock.restart();
					scene = getScene();
					handleEvents(*scene);
					update(*scene, time);
					draw(*scene,sf::RenderStates(), sf::Color::Black);
				}
				clean();
			}
			
			virtual void close(){
				active = false;
			}
	};
}

