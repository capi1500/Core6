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

#include "spawner.hpp"

namespace c6{
	GraphicComponent* Spawner::getGraphic(){
		return m_graphic;
	}
	
	AudioComponent* Spawner::getAudio(){
		return m_audio;
	}
	
	InputComponent* Spawner::getInput(){
		return m_input;
	}
	
	LogicComponent* Spawner::getLogic(){
		return m_logic;
	}
	
	Spawner::Spawner(GraphicComponent* graphic, AudioComponent* audio, InputComponent* input, LogicComponent* logic) : m_graphic(graphic), m_audio(audio), m_input(input), m_logic(logic){
	
	}
	
	Spawner::~Spawner(){
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