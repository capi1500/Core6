//
// Created by Kacper on 08/12/2020.
//

#include <Core6/framework.hpp>
#include <Core6/utils/commonFunctions.hpp>
#include <iostream>
#include "inputHandler.hpp"

namespace c6{
	void InputHandler::handleInput(){
		if(m_window != nullptr){
			sf::Event event;
			while(m_window->pollEvent(event)){
				send(event);
				c6::Framework::getMessage()->send(sfEventToMessage(event));
			}
			processEvents();
		}
	}
	
	void InputHandler::registerWindow(sf::Window* window){
		m_window = window;
	}
	
	InputHandler::~InputHandler(){
		m_window = nullptr;
	}
}