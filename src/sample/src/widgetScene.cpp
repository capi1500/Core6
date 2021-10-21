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

#include <Core6/animations/spriteAnimation.hpp>
#include <iostream>
#include "widgetScene.hpp"

WidgetScene::WidgetScene(c6::StateMachine& stateMachine) : Scene(stateMachine),
														   updateAnimation([this](const sf::Time& time){
															   animation.update(time);
														   }),
														   move([](c6::component::Transformable& transformable, const sf::Time& time){
															   if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
																   transformable->move(0, -time.asSeconds() * 50);
															   if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
																   transformable->move(0, time.asSeconds() * 50);
															   if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
																   transformable->move(-time.asSeconds() * 50, 0);
															   if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
																   transformable->move(time.asSeconds() * 50, 0);
														   }){
	c6::Framework::getResourceManager()->loadTextures("../assets/textures/rgb/");
	
	std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/red.png"));
	
	animation.bindSprite(sprite.get());
	animation.addFrame(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/red.png"));
	animation.addFrame(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/green.png"));
	animation.play();
	
	auto entity = getECS().add();
	getECS().addComponent<c6::component::Drawable>(entity, sprite);
	getECS().addComponent<c6::component::Transformable>(entity, sprite);
	getECS().refresh();
}

void WidgetScene::update(const sf::Time& time){
	Scene::update(time);
	getECS().execute<const sf::Time&>(move, time);
	animation.update(time);
}
