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

#include "agent.hpp"

namespace c6{
	Agent::Agent(Spawner* spawner){
		m_graphic = spawner->getGraphic()->clone();
		m_audio = spawner->getAudio()->clone();
		m_input = spawner->getInput()->clone();
		m_logic = spawner->getLogic()->clone();
		
		m_logic->registerGraphic(m_graphic);
		m_logic->registerAudio(m_audio);
		m_input->registerLogic(m_logic);
	}
	
	Agent::Agent(Spawner& spawner){
		m_graphic = spawner.getGraphic()->clone();
		m_audio = spawner.getAudio()->clone();
		m_input = spawner.getInput()->clone();
		m_logic = spawner.getLogic()->clone();
		
		m_logic->registerGraphic(m_graphic);
		m_logic->registerAudio(m_audio);
		m_input->registerLogic(m_logic);
	}
	
	void Agent::update(const sf::Time& time){
		m_logic->update(time);
	}
	
	void Agent::draw(){
		Framework::getRenderer()->draw(m_graphic);
	}
	
	Agent::~Agent(){
		kill();
		delete m_graphic;
		m_graphic = nullptr;
		delete m_audio;
		m_audio = nullptr;
		delete m_input;
		m_input = nullptr;
		delete m_logic;
		m_logic = nullptr;
	}
}