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

#include <MPL/MPL.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <box2d/b2_body.h>
#include <memory>
#include "components/entityState.hpp"
#include "concepts.hpp"

namespace c6{
	template<class... Ts> using Signature = MPL::TypeList<Ts...>;
	template<class... Ts> using ComponentList = MPL::TypeList<Ts...>;
	template<class... Ts> using TagList = MPL::TypeList<Ts...>;
	
	namespace component{
		using Drawable = std::shared_ptr<sf::Drawable>;
		using Transformable = std::shared_ptr<sf::Transformable>;
		using Physic = std::shared_ptr<b2Body>;
	}
	template<class ecsConfig>
	class Widget;
}