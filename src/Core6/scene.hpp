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

#include <utility>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <box2d/b2_world.h>

#include <Core6/framework.hpp>
#include <Core6/base/state/state.hpp>
#include <Core6/ecs/entityComponentSystem.hpp>
#include <Core6/ecs/systems.hpp>
#include "physicsConfig.hpp"

namespace c6{
	template<concepts::Config ecsConfig>
	class Scene : public State, public Listener<sf::Event>{
		private:
			EntityComponentSystem<ecsConfig> ecs;
			
			bool usesPhysics;
			PhysicsConfig physicsConfig;
			b2World physicWorld;
		protected:
			[[nodiscard]]
			EntityComponentSystem<ecsConfig>& getECS() noexcept{
				return ecs;
			}
			
			[[nodiscard]]
			const EntityComponentSystem<ecsConfig>& getECS() const noexcept{
				return ecs;
			}
			
			[[nodiscard]]
			const PhysicsConfig& getPhysicsConfig() const noexcept{
				return physicsConfig;
			}
			
			[[nodiscard]]
			b2World& getPhysicWorld() noexcept{
				return physicWorld;
			}
			
			[[nodiscard]]
			const b2World& getPhysicWorld() const noexcept{
				return physicWorld;
			}
		public:
			Scene(StateMachine& stateMachine, PhysicsConfig physicsConfig) noexcept :
					State(stateMachine),
					usesPhysics(true),
					physicsConfig(physicsConfig),
					physicWorld(physicsConfig.gravity){
				Framework::getInputHandler()->addListener(this);
			}
			
			Scene(StateMachine& stateMachine) noexcept :
					State(stateMachine),
					usesPhysics(false),
					physicsConfig(PhysicsConfig(0, b2Vec2_zero, 0, 0)),
					physicWorld(b2Vec2_zero){
				Framework::getInputHandler()->addListener(this);
			}
			
			~Scene() override{
				if(isActive())
					Framework::getInputHandler()->removeListener(this);
			}
			
			void activate() noexcept override{
				Activable::activate();
				Framework::getInputHandler()->addListener(this);
			}
			
			void deactivate() noexcept override{
				Activable::deactivate();
				Framework::getInputHandler()->removeListener(this);
			}
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states){
				ecs.template execute<sf::RenderTarget&, sf::RenderStates>(system::draw<ecsConfig>, target, states);
			}
			
			virtual void update(const sf::Time& time){
				if(usesPhysics){
					physicWorld.Step(time.asSeconds(), physicsConfig.velocityIterations, physicsConfig.positionIterations);
					ecs.template execute<const PhysicsConfig&>(system::syncPhysicsWithGraphics<ecsConfig>, physicsConfig);
				}
				ecs.template execute<const sf::Time&>(system::updateAnimation<ecsConfig>, time);
			}
			
			void onNotify([[maybe_unused]] const sf::Event& event) noexcept override{
			
			}
	};
}

