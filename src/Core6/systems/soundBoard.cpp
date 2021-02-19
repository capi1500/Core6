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

#include "soundBoard.hpp"
#include <SFML/Audio/SoundBuffer.hpp>

namespace c6{
	long long SoundBoard::playSound(const sf::Sound& sound){
		long long id = sound.getBuffer()->getDuration().asMicroseconds() + m_clock.getElapsedTime().asMicroseconds();
		m_sound[id] = sound;
		m_sound[id].play();
		return id;
	}
	
	sf::Sound& SoundBoard::getSound(const long long int id){
		return m_sound[id];
	}
	
	void SoundBoard::clean(){
		for(auto it = m_sound.begin(); it != m_sound.end();){
			if(it->second.getStatus() == sf::Sound::Stopped)
				it = m_sound.erase(it);
			else
				it++;
		}
	}
}