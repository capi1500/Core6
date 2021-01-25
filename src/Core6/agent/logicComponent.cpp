//
// Created by Kacper on 08/12/2020.
//

#include "logicComponent.hpp"

namespace c6{
	void LogicComponent::registerGraphic(GraphicComponent* graphic){
		m_graphic = graphic;
	}
	
	void LogicComponent::registerAudio(AudioComponent* audio){
		m_audio = audio;
	}
}