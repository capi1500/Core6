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

#include "init.hpp"

// Physics Config
const float PhysicsConfig::scaleFactor = 30;
const b2Vec2 PhysicsConfig::gravity = b2Vec2(0, 10);
const unsigned PhysicsConfig::velocityIterations = 8;
const unsigned PhysicsConfig::positionIterations = 3;

// Rest

c6::ecs::system::Draw<Config> draw = c6::ecs::system::draw<Config>;
c6::ecs::system::PhysicsTransformableSync<Config> physics = c6::ecs::system::physicsTransformableSync<Config>;

Move move([](const sf::Time& time, Transformable& t){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		t->move(0, -200 * time.asSeconds());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		t->move(-200 * time.asSeconds(), 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		t->move(0, 200 * time.asSeconds());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		t->move(200 * time.asSeconds(), 0);
});

MovePlayer playerMove([]([[maybe_unused]] const sf::Time& t, Physic& p){
	b2Vec2 v(0, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		v.y -= 30;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		v.x -= 30;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		v.y += 30;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		v.x += 30;
	p->SetLinearVelocity(v);
});