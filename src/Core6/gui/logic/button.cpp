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
#include <Core6/gui/graphics/widgetGraphics.hpp>
#include <iostream>
#include "button.hpp"

namespace c6::widgets{
	Button::Button(WidgetGraphics* graphics, const Runnable& runnable) : callback([graphics, runnable](const sf::Event& event){
			if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
				if(graphics->getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
					runnable();
			}
		}){
	}
	
	void Button::onNotify(const sf::Event& event) noexcept{
		callback(event);
	}
}