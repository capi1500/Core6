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

#ifndef CORE6_PHYSICSCONFIG_HPP
#define CORE6_PHYSICSCONFIG_HPP

#include <concepts>
#include <box2d/b2_math.h>
#include <SFML/System/Vector2.hpp>

namespace c6{
	struct PhysicsConfig{
		static const float scaleFactor;
		static const b2Vec2 gravity;
		static const unsigned velocityIterations;
		static const unsigned positionIterations;
		
		static b2Vec2 pixelToMeter(const sf::Vector2f& pixel){
			return b2Vec2(pixel.x / scaleFactor, pixel.y / scaleFactor);
		}
		
		static sf::Vector2f meterToPixel(const b2Vec2& meter){
			return sf::Vector2f(meter.x * scaleFactor, meter.y * scaleFactor);
		}
	};
	
	namespace concepts{
		template<class T> concept PhysicsConfig = requires{
			{T::scaleFactor} -> std::convertible_to<float>;
			{T::gravity} -> std::convertible_to<b2Vec2>;
			{T::velocityIterations} -> std::convertible_to<unsigned>;
			{T::positionIterations} -> std::convertible_to<unsigned>;
		};
	}
}

#endif //CORE6_PHYSICSCONFIG_HPP
