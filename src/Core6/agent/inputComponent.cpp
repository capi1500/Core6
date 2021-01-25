//
// Created by Kacper on 08/12/2020.
//

#include "inputComponent.hpp"

namespace c6{
	void InputComponent::registerLogic(LogicComponent* logic){
		m_logic = logic;
	}
	
	void InputComponent::onSignal(const sf::Event& signal){
	}
}
