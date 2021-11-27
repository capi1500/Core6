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

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "widgetGraphics.hpp"

namespace c6::widgets{
	template<class T>
	concept BoundedDrawable = requires(T t){
		std::is_base_of_v<sf::Drawable, T>;
		{t.getGlobalBounds()} -> std::same_as<sf::FloatRect>;
	};
	
	template<BoundedDrawable T>
	class Primitive : public WidgetGraphics{
		private:
			T t;
		protected:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
				target.draw(t, states);
			}
		public:
			sf::FloatRect getLocalBounds() const override{
				return t.getGlobalBounds();
			}
			
			T& get(){
				return t;
			}
			
			const T& get() const{
				return t;
			}
			
			void set(T copy){
				t = std::move(copy);
			}
			
			void set(T&& move){
				t = std::forward<T&&>(move);
			}
	};
}