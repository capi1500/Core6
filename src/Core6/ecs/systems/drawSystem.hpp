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

#include "../config.hpp"
#include "../system.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace c6{
	namespace signature{
		using Draw = Signature<component::EntityState, component::Drawable>;
	}
	namespace system{
		template<concepts::Config Config>
		auto Draw = System<Config, signature::Draw, Renderer&, sf::RenderStates>(
				[]([[maybe_unused]] EntityComponentSystem<Config>& ecs, [[maybe_unused]] typename EntityComponentSystem<Config>::EntityId id, component::EntityState& entityState, component::Drawable& drawable, Renderer& renderer, sf::RenderStates renderStates){
					if(entityState.visible){
						// TODO: change below to support transformable component not merged with drawable component
						//if(ecs.template hasComponent<component::Transformable>(id))
						//	renderStates.transform.combine((ecs.template getComponent<component::Transformable>(id))->getTransform());
						renderer.draw(*drawable, renderStates);
					}
				}
		);
	}
}