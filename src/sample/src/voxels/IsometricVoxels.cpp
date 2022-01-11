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

#include "IsometricVoxels.hpp"
#include "../scenes/pause.hpp"

IsometricVoxels::IsometricVoxels(c6::Application<ecsConfig>& app, c6::StateMachine& stateMachine) : Scene(
		app,
		stateMachine,
		c6::PhysicsConfig(1, b2Vec2(0, -9.81), 9, 15)){
	
	
	world.addChunk({0, 0});
	
	
	getView().setCenter(100, 100);
	c6::Framework::getRenderer()->setView(getView());
}

void IsometricVoxels::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::Escape)
			getStateMachine().add(new Pause(getApplication(), getStateMachine()));
	}
	world.onNotify(event);
}

void IsometricVoxels::draw(c6::Renderer& target, sf::RenderStates states){
	target.draw(world, states);
	Scene::draw(target, states);
}

void IsometricVoxels::update(const sf::Time& time){
	Scene::update(time);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		getView().move(0, -1000 * time.asSeconds());
		c6::Framework::getRenderer()->setView(getView());
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		getView().move(-1000 * time.asSeconds(), 0);
		c6::Framework::getRenderer()->setView(getView());
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		getView().move(0, 1000 * time.asSeconds());
		c6::Framework::getRenderer()->setView(getView());
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		getView().move(1000 * time.asSeconds(), 0);
		c6::Framework::getRenderer()->setView(getView());
	}
	world.update(time);
}
