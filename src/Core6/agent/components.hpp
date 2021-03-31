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

#ifndef CORE6_COMPONENTS_HPP
#define CORE6_COMPONENTS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Core6/config.hpp>
#include <Core6/agent/system.hpp>
#include <box2d/b2_body.h>

namespace c6{
	namespace ecs{
		namespace component{
			using Drawable = sf::Drawable*;
			using Transformable = sf::Transformable*;
			using Physic = b2Body*;
			
			using StdComponents = ComponentList<Drawable, Transformable, Physic>;
		}
		namespace tag{
			struct EventResponsible{};
			struct PhysicallyMoving{};
			using StdTags = TagList<EventResponsible, PhysicallyMoving>;
		}
		namespace signature{
			using Draw = Signature<component::Drawable>;
			using PhysicsTransformableSync = Signature<tag::PhysicallyMoving, component::Transformable, component::Physic>;
			
			using StdSignatures = SignatureList<Draw, PhysicsTransformableSync>;
		}
		namespace system{
			template<concepts::Config Config>
			using Draw = System<Config, signature::Draw, sf::RenderWindow&, sf::RenderStates>;
			
			template<concepts::Config Config>
			auto draw = Draw<Config>([](component::Drawable& r, sf::RenderWindow& renderer, sf::RenderStates states = sf::RenderStates()){
				renderer.draw(*r, states);
			});
			
			template<concepts::Config Config>
			using PhysicsTransformableSync = System<Config, signature::PhysicsTransformableSync, const sf::Time&>;
			
			template<concepts::Config Config>
			auto physicsTransformableSync = PhysicsTransformableSync<Config>([](component::Transformable& t, component::Physic& p, [[maybe_unused]] const sf::Time& time){
				t->setPosition(Config::PhysicsConfig::meterToPixel(p->GetPosition()));
				t->setRotation(180 * p->GetAngle() / b2_pi);
			});
		}
	}
}

#endif //CORE6_COMPONENTS_HPP
