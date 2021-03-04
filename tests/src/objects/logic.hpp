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

#ifndef CORE6_LOGIC_HPP
#define CORE6_LOGIC_HPP

#include <Core6/agent/graphicComponent.hpp>
#include <Core6/agent/logicComponent.hpp>
#include "graphic.hpp"

class Logic : public c6::LogicComponent{
	protected:
		int m_color;
		int m_speed;
		
		Graphic* getGraphic() override{
			return static_cast<Graphic*>(m_graphic);
		}
	
	public:
		int getColor() const{
			return m_color;
		}
		
		void setColor(int color){
			m_color = color;
		}
		
		void update(const sf::Time& time) override{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				getGraphic()->move(-m_speed * time.asSeconds(), 0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				getGraphic()->move(0, m_speed * time.asSeconds());
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				getGraphic()->move(m_speed * time.asSeconds(), 0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				getGraphic()->move(0, -m_speed * time.asSeconds());
			if(m_color != -1){
				if(m_color == 1)
					getGraphic()->getRect().setFillColor(sf::Color::Red);
				else if(m_color == 2)
					getGraphic()->getRect().setFillColor(sf::Color::Green);
				else if(m_color == 3)
					getGraphic()->getRect().setFillColor(sf::Color::Blue);
				m_color = -1;
			}
		}
		
		Logic* clone() override{
			return new Logic(*this);
		}
		
		Logic(){
			m_color = -1;
			m_speed = 500;
		}
};

#endif //CORE6_LOGIC_HPP
