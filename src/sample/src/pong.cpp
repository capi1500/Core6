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
 *	you must not claim that you wrote the original software.
 *	If you use this software in a product, an acknowledgment
 *	in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *	and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#include "pong.hpp"
#include <Core6/framework.hpp>
#include <iostream>
#include <box2d/box2d.h>

Pong::Pong(c6::StateMachine& stateMachine, const c6::PhysicsConfig& physicsConfig) :
		Scene(stateMachine, physicsConfig),
		movePalletes([](Player& player, c6::component::Physic& physic, const sf::Time& time){
			b2Vec2 v(0, 0);
			if(sf::Keyboard::isKeyPressed(player.up))
				v.y -= time.asSeconds() * 200;
			if(sf::Keyboard::isKeyPressed(player.down))
				v.y += time.asSeconds() * 200;
			physic->SetLinearVelocity(v);
		}){
	c6::EntityFactory<ecsConfig, sf::Keyboard::Key, sf::Keyboard::Key, sf::Vector2f> playerFactory(
			[&physicsConfig, this](ECS& entityManager, EntityId id, sf::Keyboard::Key&& up, sf::Keyboard::Key&& down, sf::Vector2f&& position){
				std::shared_ptr<sf::RectangleShape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(20, 100));
				rect->setFillColor(sf::Color::White);
				rect->setOrigin(10, 50);
				
				entityManager.addComponent<c6::component::Drawable>(id, rect);
				entityManager.addComponent<c6::component::Transformable>(id, rect);
				
				Player& player = entityManager.addComponent<Player>(id);
				player.up = up;
				player.down = down;
				player.points = 0;
				
				
				b2BodyDef bodyDef;
				bodyDef.type = b2_kinematicBody;
				bodyDef.fixedRotation = true;
				bodyDef.position = physicsConfig.pixelToMeter(position);
				
				b2PolygonShape shape;
				b2Vec2 size = physicsConfig.pixelToMeter({10, 50});
				shape.SetAsBox(size.x, size.y);
				
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = 1.f;
				fixtureDef.friction = 0.3f;
				
				c6::component::Physic& physic = entityManager.addComponent<c6::component::Physic>(id, getPhysicWorld().CreateBody(&bodyDef), [](void*){});
				physic->CreateFixture(&fixtureDef);
			}
	);
	c6::EntityFactory<ecsConfig, sf::Vector2f> groundFactory(
			[&physicsConfig, this](ECS& entityManager, EntityId id, sf::Vector2f&& position){
				b2BodyDef bodyDef;
				bodyDef.type = b2_staticBody;
				bodyDef.position = physicsConfig.pixelToMeter(position);
				
				b2PolygonShape shape;
				b2Vec2 size = physicsConfig.pixelToMeter({400, 10});
				shape.SetAsBox(size.x, size.y);
				
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = 1.f;
				fixtureDef.friction = 0.f;
				
				c6::component::Physic& physic = entityManager.addComponent<c6::component::Physic>(id, getPhysicWorld().CreateBody(&bodyDef), [](void*){});
				physic->CreateFixture(&fixtureDef);
			}
	);
	c6::EntityFactory<ecsConfig> ballFactory(
			[&physicsConfig, this](ECS& entityManager, EntityId id){
				std::shared_ptr<sf::CircleShape> circle = std::make_shared<sf::CircleShape>(10);
				circle->setFillColor(sf::Color::White);
				circle->setOrigin(10, 10);
				
				entityManager.addComponent<c6::component::Drawable>(id, circle);
				entityManager.addComponent<c6::component::Transformable>(id, circle);
				
				entityManager.addTag<Ball>(id);
				
				
				b2BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.fixedRotation = true;
				bodyDef.position = physicsConfig.pixelToMeter({400, 250});
				bodyDef.linearVelocity = {5, 0};
				bodyDef.bullet = true;
				
				b2CircleShape shape;
				shape.m_radius = physicsConfig.pixelToMeter({10, 0}).x;
				
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = 1.f;
				fixtureDef.friction = 0.f;
				fixtureDef.restitution = 1.f;
				
				c6::component::Physic& physic = entityManager.addComponent<c6::component::Physic>(id, getPhysicWorld().CreateBody(&bodyDef), [](void*){});
				physic->CreateFixture(&fixtureDef);
			}
	);
	
	player1 = getECS().addWithHandleFromFactory(playerFactory, sf::Keyboard::W, sf::Keyboard::S, {30, 250});
	player2 = getECS().addWithHandleFromFactory(playerFactory, sf::Keyboard::Up, sf::Keyboard::Down, {770, 250});
	ball = getECS().addWithHandleFromFactory(ballFactory);
	getECS().addFromFactory(groundFactory, {400, -10});
	getECS().addFromFactory(groundFactory, {400, 510});
	
	getECS().refresh();
}

void Pong::onNotify([[maybe_unused]] const sf::Event& event) noexcept{

}

void Pong::update(const sf::Time& time){
	Scene::update(time);
	getECS().execute<const sf::Time&>(movePalletes, time);
}
