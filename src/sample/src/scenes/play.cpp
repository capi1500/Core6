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

#include <src/systems/ecsEventHandler.hpp>
#include "play.hpp"
#include "pause.hpp"

Play::Play(c6::Application<ecsConfig>& app, c6::StateMachine& stateMachine) : Scene(
		app,
		stateMachine,
		c6::PhysicsConfig(1, b2Vec2(0, -9.81), 9, 15)){
	
	float pixelsPerSecond = 100;
	c6::EntityBuilder<ecsConfig>(getECS())
	        .attach<sf::Sprite>(c6::Function<sf::Sprite>([]{
				sf::Sprite sprite;
				sprite.setTexture(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/green.png"));
		        return sprite;
			}))
			.attach<c6::component::Updater, c6::component::Transformable>(
					c6::Function<c6::Consumer<const sf::Time&>, c6::component::Transformable&>(
							[pixelsPerSecond](c6::component::Transformable& transformable){
								return [&transformable, pixelsPerSecond](const sf::Time& time){
									if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
										transformable->move(0, -pixelsPerSecond * time.asSeconds());
									if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
										transformable->move(-pixelsPerSecond * time.asSeconds(), 0);
									if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
										transformable->move(0, pixelsPerSecond * time.asSeconds());
									if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
										transformable->move(pixelsPerSecond * time.asSeconds(), 0);
								};
							}
					)
			)
	        .attach<c6::component::EventHandler, c6::component::EntityState>(
			        c6::Function<c6::Consumer<const sf::Event&>, c6::component::EntityState&>(
					        [](c6::component::EntityState& state){
						        return [&state](const sf::Event& event){
							        if(event.type == sf::Event::KeyReleased){
										if(event.key.code == sf::Keyboard::Num1){
											//state.active = !state.active;
										}
										else if(event.key.code == sf::Keyboard::Num2){
											state.visible = !state.visible;
										}
									}
						        };
					        }
			        )
	        )/*
			.attach<c6::component::Physic>(
					c6::Function<c6::component::Physic>([this](){
						b2BodyDef def;
						b2Body* b = getPhysicWorld().CreateBody(&def);
						c6::component::Physic p = std::shared_ptr<b2Body>();
						return p;
					})
			)*/;
	getECS().refresh();
}

void Play::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::Escape)
			getStateMachine().add(new Pause(getApplication(), getStateMachine()));
	}
}