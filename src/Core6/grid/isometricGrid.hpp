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

#include <SFML/Graphics/Transform.hpp>
#include <Core6/utils/functional.hpp>
#include "grid.hpp"

namespace c6{
	class IsometricGrid : public Grid{
		private:
			sf::Vector2f origin;
			sf::Transform transform;
		public:
			IsometricGrid() = default;
			IsometricGrid(const sf::Vector2f& origin, const sf::Vector2f& ihat, const sf::Vector2f& jhat);
			explicit IsometricGrid(const sf::Vector2f& size);
			
			[[nodiscard]] sf::Vector2i mapPointToCoordinate(const sf::Vector2f& point) const override;
			[[nodiscard]] sf::Vector2f mapCoordinateToPoint(const sf::Vector2i& coordinate) const override;
			
			[[nodiscard]] sf::Vector2f getSize() const;
			const sf::Vector2f& getOrigin() const;
	};
}