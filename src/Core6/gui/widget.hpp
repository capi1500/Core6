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

namespace c6{
	class Widget : public sf::Drawable, public sf::Transformable{
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
			const Widget* parent = nullptr; // nullptr - aligns to window
			Alignment alignment = Free;
			sf::Vector2i shift = sf::Vector2i(0, 0);
			sf::Vector2f factorShift = sf::Vector2f(0, 0);
			bool cropToFrame;
			
			Adjustment adjustment = Default;
			bool keepRatio = true;
			
			void recalculatePosition() noexcept;
		public:
			virtual ~Widget() = default;
			
			/**
			 * @brief set adjustment of the widget
			 * @param adjustment
			 */
			void adjust(Adjustment adjustment, bool keepRatio = true) noexcept;
			
			void align() noexcept;
			void align(const sf::Vector2i& shift) noexcept;
			void align(const sf::Vector2f& factorShift) noexcept;
			void align(const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept;
			void align(Alignment alignment) noexcept;
			void align(Alignment alignment, const sf::Vector2i& shift) noexcept;
			void align(Alignment alignment, const sf::Vector2f& factorShift) noexcept;
			void align(Alignment alignment, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept;
			void align(const Widget* widget) noexcept;
			void align(const Widget* widget, const sf::Vector2i& shift) noexcept;
			void align(const Widget* widget, const sf::Vector2f& factorShift) noexcept;
			void align(const Widget* widget, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept;
			void align(const Widget* widget, Alignment alignment) noexcept;
			void align(const Widget* widget, Alignment alignment, const sf::Vector2i& shift) noexcept;
			void align(const Widget* widget, Alignment alignment, const sf::Vector2f& factorShift) noexcept;
			void align(const Widget* widget, Alignment alignment, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept;
			
			void setCropToFrame(bool cropToFrame);
			
			virtual sf::FloatRect getLocalBounds() const = 0;
			virtual sf::FloatRect getGlobalBounds() const = 0;
	};
}

