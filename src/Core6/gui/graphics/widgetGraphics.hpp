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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Core6/base/listener/emitter.hpp>

namespace c6{
	class WidgetGraphics : public sf::Drawable{
		public:
			enum Alignment{
				Free,
				TopRightCorner,
				BottomRightCorner,
				TopLeftCorner,
				BottomLeftCorner,
				TopSide,
				BottomSide,
				LeftSide,
				RightSide,
				Center
			};
			
			enum Adjustment{
				Default,
				FitToWidth,
				FitToHeight,
				FitToSize
			};
		private:
			Alignment alignment = Free;
			Adjustment adjustment = Default;
			
			bool updated = true;
			bool keepRatio = true;
			bool cropToParent;
			
			sf::Transform global;
			sf::Transformable frame;
		public:
			virtual sf::FloatRect getLocalBounds() const = 0;
			sf::FloatRect getGlobalBounds() const;
			
			const sf::Transform& getGlobalTransform() const;
			
			void recalculateTransformations(const sf::Transform& parent, const sf::Transform& localTransform);
	};
}