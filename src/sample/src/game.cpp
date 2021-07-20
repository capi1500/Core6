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

#include "game.hpp"
#include "pong.hpp"

Game::Game() : Application(c6::ConsoleBuilder().useMessageType(c6::Message::Info)
                                               .useMessageType(c6::Message::Error)
                                               .useMessageType(c6::Message::Debug)
                                               .useMessageType(c6::Message::Loading)
                                               .create()),
                           physicsConfig(30,
                                         b2Vec2(0, 0),
                                         8,
                                         3){
	
}

void Game::init(){
	Application::init();
	c6::Framework::getRenderer().getWindow().create(sf::VideoMode(800, 500), "test");
	c6::Framework::getRenderer().getWindow().setFramerateLimit(60);
	getScenes().add(new Pong(getScenes(), physicsConfig));
}

void Game::clean(){
	c6::Framework::getRenderer().getWindow().close();
	Application::clean();
}
