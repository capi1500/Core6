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

#include <cmath>
#include "ortographicGrid.hpp"

namespace c6{
	OrtographicGrid::OrtographicGrid(const sf::Vector2f& origin, const sf::Vector2f& ihat, const sf::Vector2f& jhat) :
			origin(origin),
			transform(ihat.x, jhat.x, 0,
					  ihat.y, jhat.y, 0,
					  0, 0, 1),
		    angle(std::acos(
					(ihat.x * jhat.x + ihat.x * jhat.x) /
				       (std::sqrt(ihat.x * ihat.x + ihat.y * ihat.y) * std::sqrt(jhat.x * jhat.x + jhat.y * jhat.y))
			     )
		    ){}
	
	OrtographicGrid::OrtographicGrid(const sf::Vector2f& size) : OrtographicGrid({size.x / 2, 0}, {-size.x / 2, size.y / 2}, {size.x / 2, size.y / 2}){}
	
	sf::Vector2i OrtographicGrid::mapPointToCoordinate(const sf::Vector2f& point) const{
		sf::Vector2f tmp = transform.getInverse().transformPoint(point - origin);
		return sf::Vector2i(std::floor(tmp.x), std::floor(tmp.y));
	}
	
	sf::Vector2f OrtographicGrid::mapCoordinateToPoint(const sf::Vector2i& coordinate) const{
		return transform.transformPoint(coordinate.x, coordinate.y) + origin;
	}
	
	sf::Vector2f OrtographicGrid::getSize() const{
		sf::Vector2f ihat = mapCoordinateToPoint({1, 0});
		sf::Vector2f jhat = mapCoordinateToPoint({0, 1});
		return {std::abs(ihat.x) + std::abs(jhat.x), std::abs(ihat.y) + std::abs(jhat.y)};
	}
	
	const sf::Vector2f& OrtographicGrid::getOrigin() const{
		return origin;
	}
	
	float OrtographicGrid::getAngle() const{
		return angle;
	}
}