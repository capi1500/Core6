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

#include <Core6/ecs/config.hpp>
#include <Core6/ecs/system.hpp>
#include <Core6/ecs/components.hpp>
#include "../widget.hpp"

namespace c6::system{
		template<concepts::Config Config>
		System<Config, Signature<component::EntityState, Widget<Config>>> UpdateWidgetTree = System<Config, Signature<component::EntityState, Widget<Config>>>(
				[](EntityComponentSystem<Config>& ecs, [[maybe_unused]] typename EntityComponentSystem<Config>::EntityId id, component::EntityState& entityState, Widget<Config>& widget){
					if(widget.hasGraphics()){
						sf::Transform parents = sf::Transform::Identity;
						if(widget.hasParent()){
							Widget<Config>& parent = ecs.template getComponent<Widget<Config>>(widget.getParent());
							if(parent.hasGraphics())
								parents = parent.getGraphics().getGlobalTransform();
							component::EntityState& parentState = ecs.template getComponent<component::EntityState>(widget.getParent());
							entityState.visible &= parentState.visible;
							entityState.active &= parentState.active;
						}
						sf::Transform local = sf::Transform::Identity;
						if(ecs.template hasComponent<component::Transformable>(id)){
							local = ecs.template getComponent<component::Transformable>(id)->getTransform();
						}
						widget.getGraphics().recalculateTransformations(parents, local);
						for(auto& child : widget.getChildren()){
							ecs.template execute(child, UpdateWidgetTree<Config>);
						}
					}
				}
		);
	}