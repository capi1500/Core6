/**
 * Core6
 * Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#include "graphic.hpp"

void Graphic::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform.combine(getTransform());
	target.draw(m_rect, states);
}

Graphic::Graphic(const sf::Vector2f& pos){
	m_rect.setSize(sf::Vector2f(100, 100));
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setPosition(pos);
}

Graphic* Graphic::clone(){
	return new Graphic(*this);
}

sf::RectangleShape& Graphic::getRect(){
	return m_rect;
}
