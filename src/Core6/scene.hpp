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
#include <Core6/ecs/entityBuilder.hpp>
#include <Core6/gui/widget.hpp>
#include "physicsConfig.hpp"

#include <Core6/ecs/systems/drawSystem.hpp>
#include <Core6/ecs/systems/syncPhysicsWithGraphics.hpp>
#include <Core6/gui/systems/updateWidgetTree.hpp>
#include <Core6/gui/systems/drawWidget.hpp>

namespace c6{
	template<concepts::Config ecsConfig>
	class Application;
	
	template<concepts::Config ecsConfig>
	class Scene : public State, public Listener<sf::Event>{
		private:
			using Handle = typename EntityComponentSystem<ecsConfig>::Handle;
			
			Application<ecsConfig>& application;
			EntityComponentSystem<ecsConfig> ecs;
			
			bool usesPhysics;
			PhysicsConfig physicsConfig;
			b2World physicWorld;
			
			Handle widgetRoot;
		protected:
			Application<ecsConfig>& getApplication() noexcept{
				return application;
			}
			
			const Application<ecsConfig>& getApplication() const noexcept{
				return application;
			}
			
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
			
			[[nodiscard]]
			const Handle& getWidgetRoot() const{
				return widgetRoot;
			}
			
			[[nodiscard]]
			Handle& getWidgetRoot(){
				return widgetRoot;
			}
		public:
			Scene(Application<ecsConfig>& application, StateMachine& stateMachine, PhysicsConfig physicsConfig) noexcept :
					State(stateMachine),
					application(application),
					usesPhysics(true),
					physicsConfig(physicsConfig),
					physicWorld(physicsConfig.gravity),
					widgetRoot(ecs.addWithHandle()){
				Framework::getInputHandler()->addListener(this);
				EntityBuilder<ecsConfig>(ecs, widgetRoot).template attach<Widget<ecsConfig>>(
						widgetRoot,
						new widgets::Frame(sf::FloatRect(0,
									  0,
									  static_cast<float>(Framework::getRenderer()->getSize().x),
									  static_cast<float>(Framework::getRenderer()->getSize().y)
							  )
					    ),
						nullptr
			    );
				ecs.refresh();
			}
			
			Scene(Application<ecsConfig>& application, StateMachine& stateMachine) noexcept :
					Scene(application, stateMachine, PhysicsConfig(0, b2Vec2_zero, 0, 0)){
				usesPhysics = false;
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
				ecs.template execute<sf::RenderTarget&, sf::RenderStates>(system::Draw<ecsConfig>, target, states);
				ecs.template execute<sf::RenderTarget&, sf::RenderStates>(system::DrawWidget<ecsConfig>, target, states);
			}
			
			virtual void update(const sf::Time& time){
				if(usesPhysics){
					physicWorld.Step(time.asSeconds(), physicsConfig.velocityIterations, physicsConfig.positionIterations);
					ecs.template execute<const PhysicsConfig&>(system::syncPhysicsWithGraphics<ecsConfig>, physicsConfig);
				}
				ecs.template execute(widgetRoot, system::UpdateWidgetTree<ecsConfig>);
			}
			
			void onNotify([[maybe_unused]] const sf::Event& event) noexcept override{
				if(event.type == sf::Event::Resized){
					dynamic_cast<widgets::Frame&>(ecs.template getComponent<Widget<ecsConfig>>(widgetRoot).getGraphics()).setRect({0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
				}
			}
	};
}

