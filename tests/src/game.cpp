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

#include <src/objects/logic.hpp>
#include <src/objects/input.hpp>
#include "game.hpp"

void Game::run(){
	sf::Time time;
	
	c6::Scene* scene;
	while(m_active){
		time = m_clock.restart();
		scene = getScene();
		
		c6::Framework::getInput()->handleInput();
		c6::Framework::getMessage()->processEvents();
		
		scene->update(time);
		
		scene->draw();
	}
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
	
	c6::Scene* scene = new c6::Scene(m_finiteStateMachine);
	
	c6::Framework::getEntryPoint()->setDefaultTemplate("graphic", new Graphic);
	
	loadPlugins(std::string("../mods/"));
	
	c6::Spawner factory(c6::Framework::getEntryPoint()->get<Graphic>("graphic"), new c6::AudioComponent, new Input, new Logic);
	scene->addAgent(factory);
	factory.getGraphic()->move(200, 200);
	scene->addAgent(factory);
	
	m_finiteStateMachine.add(scene);
	Application::init();
}
