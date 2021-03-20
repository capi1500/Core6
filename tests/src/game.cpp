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

#include <src/objects/rectComponent.hpp>
#include "game.hpp"

void Game::run(){
	Scene* scene;
	sf::Time time;
	
	while(m_active){
		time = m_clock.restart();
		scene = getScene();
		
		Framework::getInputHandler().handleInput();
		
		scene->update(time);
		
		scene->draw();
	}
}

c6::Scene<Config>* Game::scene1(){
	c6::Scene<Config>* scene = new c6::Scene<Config>(m_finiteStateMachine, [&](const sf::Event& event){
		if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Num2){
			m_finiteStateMachine.add(scene2());
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Backspace){
			m_finiteStateMachine.pop();
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Numpad2){
			m_finiteStateMachine.replace(scene2());
		}
	});
	scene->addTimeSystem(move);
	scene->addRenderSystem(draw);
	
	Factory<int, int, sf::Color> f([](Agent& a, int x, int y, sf::Color color){
		RectComponent* r = new RectComponent(c6::EntryPoint::getTemplate<RectComponent>("rect"));
		r->r.setFillColor(color);
		r->setPosition(x, y);
		a.addComponent<Drawable>(r);
		a.addComponent<Transformable>(r);
		a.addTag<Rect>();
	});
	
	scene->newAgent(f, 100, 100, sf::Color::Red);
	scene->newAgent(f, 0, 0, sf::Color::Green);
	
	return scene;
}

c6::Scene<Config>* Game::scene2(){
	c6::Scene<Config>* scene = new c6::Scene<Config>(m_finiteStateMachine, [&](const sf::Event& event){
		if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Num1){
			m_finiteStateMachine.add(scene1());
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Backspace){
			m_finiteStateMachine.pop();
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Numpad1){
			m_finiteStateMachine.replace(scene1());
		}
	});
	return scene;
}

void Game::init(){
	Framework::getRenderer().lock();
	Framework::getRenderer().get().create(sf::VideoMode(500, 500), "Plugins test");
	Framework::getInputHandler().registerWindow(&Framework::getRenderer().get());
	Framework::getRenderer().unlock();
	
	Framework::getResourceManager().loadFonts(std::string("../assets/fonts"));
	Framework::getResourceManager().loadTextures(std::string("../assets/textures"));
	Framework::getResourceManager().loadSounds(std::string("../assets/sounds"));
	
	//c6::Console::useMessageType(c6::MessageType::Debug);
	c6::Console::useMessageType(c6::MessageType::Error);
	c6::Console::useMessageType(c6::MessageType::Info);
	//c6::Console::useMessageType(c6::MessageType::Loading);
	
	RectComponent* r = new RectComponent;
	r->r.setSize({100, 100});
	c6::EntryPoint::addDefaultTemplate("rect", r);
	
	loadPlugins(std::string("../mods/"));
	
	m_finiteStateMachine.add(scene1());
	Application::init();
}
