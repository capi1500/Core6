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

#pragma once

#include <Core6/scene.hpp>
#include <Core6/systems/renderer.hpp>
#include <Core6/systems/inputHandler.hpp>
#include <Core6/ecs/components.hpp>
#include "init.hpp"

class Pong : public c6::Scene<ecsConfig>{
	private:
		ECS::Handle player1;
		ECS::Handle player2;
		ECS::Handle ball;
		
		c6::System<ecsConfig, c6::Signature<Player, c6::component::Physic>, const sf::Time&> movePalletes;
	public:
		Pong(c6::StateMachine& stateMachine, const c6::PhysicsConfig& physicsConfig);
		void onNotify(const sf::Event& event) noexcept override;
		
		void update(const sf::Time& time) override;
};