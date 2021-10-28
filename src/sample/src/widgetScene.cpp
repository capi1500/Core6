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
#include <Core6/ecs/entityBuilder.hpp>
#include "widgetScene.hpp"

WidgetScene::WidgetScene(c6::StateMachine& stateMachine) : Scene(stateMachine),
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
	
	c6::EntityBuilder<ecsConfig>()
	        .attach<sf::Sprite>(c6::Provider<sf::Sprite>(
					[]{
						sf::Sprite sprite;
						sprite.setPosition(100, 100);
						sprite.setTexture(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/blue.png"));
						return sprite;
					}))
			.spawn(getECS());
	
	c6::EntityBuilder<ecsConfig>()
			.attach<sf::Sprite>()
			.attach<c6::component::Animation, sf::Sprite>(c6::Callback<c6::component::Animation, sf::Sprite&>(
					[](sf::Sprite& sprite){
						std::shared_ptr<c6::SpriteAnimation> animation = std::make_shared<c6::SpriteAnimation>();
						animation->bindSprite(&sprite);
						animation->addFrame(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/red.png"));
						animation->addFrame(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/green.png"));
						animation->play();
						return animation;
					}))
			.addTag<MovesWASD>()
			.spawn(getECS());
	
	getECS().refresh();
}

void WidgetScene::update(const sf::Time& time){
	Scene::update(time);
	getECS().execute<const sf::Time&>(move, time);
}
