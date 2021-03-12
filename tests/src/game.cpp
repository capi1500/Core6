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

#include "game.hpp"

void Game::run(){
	c6::Scene* scene;
	sf::Time time;
	
	Move move([](sf::Time time, Drawable& r){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			static_cast<sf::RectangleShape*>(r)->move(0, -200 * time.asSeconds());
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			static_cast<sf::RectangleShape*>(r)->move(-200 * time.asSeconds(), 0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			static_cast<sf::RectangleShape*>(r)->move(0, 200 * time.asSeconds());
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			static_cast<sf::RectangleShape*>(r)->move(200 * time.asSeconds(), 0);
	});
	
	while(m_active){
		time = m_clock.restart();
		scene = getScene();
		
		c6::Framework::getInput()->handleInput();
		c6::Framework::getMessage()->processEvents();
		
		//scene->update(time);
		mgr.executeSystem(move, time);
		
		c6::Framework::getRenderer()->lock();
		c6::Framework::getRenderer()->get().clear();
		mgr.executeSystem(c6::ecs::system::draw<Config>, c6::Framework::getRenderer()->get());
		c6::Framework::getRenderer()->get().display();
		c6::Framework::getRenderer()->unlock();
		//scene->draw();
	}
}

c6::Scene* Game::scene1(){
	c6::Scene* scene = new c6::Scene(m_finiteStateMachine, [&](const sf::Event& event){
		if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Num2){
			m_finiteStateMachine.add(scene2());
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Backspace){
			m_finiteStateMachine.pop();
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Numpad2){
			m_finiteStateMachine.replace(scene2());
		}
	});
	return scene;
}

c6::Scene* Game::scene2(){
	c6::Scene* scene = new c6::Scene(m_finiteStateMachine, [&](const sf::Event& event){
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
	c6::Framework::getRenderer()->lock();
	c6::Framework::getRenderer()->get().create(sf::VideoMode(500, 500), "Plugins test");
	c6::Framework::getInput()->registerWindow(&c6::Framework::getRenderer()->get());
	c6::Framework::getRenderer()->unlock();
	
	c6::Framework::getResourceManager()->loadFonts(std::string("../assets/fonts"));
	c6::Framework::getResourceManager()->loadTextures(std::string("../assets/textures"));
	c6::Framework::getResourceManager()->loadSounds(std::string("../assets/sounds"));
	
	//m_console.useMessageType(c6::MessageType::Debug);
	m_console.useMessageType(c6::MessageType::Error);
	m_console.useMessageType(c6::MessageType::Info);
	m_console.useMessageType(c6::MessageType::Loading);
	c6::Framework::getMessage()->add(&m_console);
	
	//loadPlugins(std::string("../mods/"));
	
	Agent& a1 = mgr.newAgent();
	Agent& a2 = mgr.newAgent();
	
	sf::RectangleShape* r1 = new sf::RectangleShape({100, 100}), *r2 = new sf::RectangleShape({200, 200});
	r1->setFillColor(sf::Color::Red);
	r2->setFillColor(sf::Color::Green);
	
	a1.addComponent<Drawable>(r1);
	a1.addTag<Movable>();
	a1.addTag<Rect>();
	
	a2.addComponent<Drawable>(r2);
	a2.addTag<Rect>();
	
	m_finiteStateMachine.add(scene1());
	Application::init();
}
