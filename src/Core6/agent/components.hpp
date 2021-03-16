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
#include <Core6/agent/ecsConfig.hpp>
#include <Core6/agent/system.hpp>

namespace c6{
	namespace ecs{
		namespace component{
			using Drawable = sf::Drawable*;
			using Transformable = sf::Transformable*;
			
			using StdComponents = ComponentList<Drawable, Transformable>;
		}
		namespace tag{
			struct EventResponsible{};
			
			using StdTags = TagList<EventResponsible>;
		}
		namespace signature{
			using Draw = Signature<component::Drawable>;
			
			using StdSignatures = SignatureList<Draw>;
		}
		namespace system{
			template<typename Config>
			using Draw = System<Config, signature::Draw, sf::RenderWindow&>;
			
			template<typename Config>
			auto draw = Draw<Config>([](sf::RenderWindow& renderer, component::Drawable& r){
				renderer.draw(*r);
			});
		}
	}
}

#endif //CORE6_COMPONENTS_HPP
