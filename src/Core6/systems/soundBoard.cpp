//
// Created by Kacper on 09/12/2020.
//

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