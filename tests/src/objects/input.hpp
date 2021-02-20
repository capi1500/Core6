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

#ifndef CORE6_INPUT_HPP
#define CORE6_INPUT_HPP

#include <Core6/agent/logicComponent.hpp>
#include <Core6/agent/inputComponent.hpp>
#include <Core6/framework.hpp>
#include "logic.hpp"

class Input : public c6::InputComponent{
	private:
		Logic* m_logic1;
	public:
		void onSignal(const sf::Event& signal) override{
			if(signal.type == sf::Event::KeyPressed){
				if(signal.key.code == sf::Keyboard::Num1)
					m_logic1->setColor(1);
				else if(signal.key.code == sf::Keyboard::Num2)
					m_logic1->setColor(2);
				else if(signal.key.code == sf::Keyboard::Num3)
					m_logic1->setColor(3);
			}
		}
		
		void registerLogic(c6::LogicComponent* logic) override{
			InputComponent::registerLogic(logic);
			m_logic1 = dynamic_cast<Logic*>(logic);
		}
		
		Input* clone() override{
			return new Input(*this);
		}
		
		Input(){
			c6::Framework::getInput()->add(this);
		}
		
		~Input(){
			c6::Framework::getInput()->remove(this);
		}
};

#endif //CORE6_INPUT_HPP
