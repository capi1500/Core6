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

#include "framework.hpp"

namespace c6{
	Loader* Framework::m_loader = nullptr;
	ResourceManager* Framework::m_resourceManager = nullptr;
	InputHandler* Framework::m_input = nullptr;
	Renderer* Framework::m_renderer = nullptr;
	SoundBoard* Framework::m_audioManager = nullptr;
	Signal<Message>* Framework::m_message = nullptr;
	Signal<CoreSignal>* Framework::m_coreSignal = nullptr;
	EntryPoint* Framework::m_entryPoint = nullptr;
	
	Loader* Framework::getLoader(){
		if(m_loader == nullptr)
			m_loader = new Loader;
		return m_loader;
	}
	
	InputHandler* Framework::getInput(){
		if(m_input == nullptr)
			m_input = new InputHandler;
		return m_input;
	}
	
	Renderer* Framework::getRenderer(){
		if(m_renderer == nullptr)
			m_renderer = new Renderer;
		return m_renderer;
	}
	
	SoundBoard* Framework::getAudioManager(){
		if(m_audioManager == nullptr)
			m_audioManager = new SoundBoard;
		return m_audioManager;
	}
	
	Signal<Message>* Framework::getMessage(){
		if(m_message == nullptr)
			m_message = new Signal<Message>;
		return m_message;
	}
	
	Signal<CoreSignal>* Framework::getCoreSignal(){
		if(m_coreSignal == nullptr)
			m_coreSignal = new Signal<CoreSignal>;
		return m_coreSignal;
	}
	
	ResourceManager* Framework::getResourceManager(){
		if(m_resourceManager == nullptr)
			m_resourceManager = new ResourceManager;
		return m_resourceManager;
	}
	
	EntryPoint* Framework::getEntryPoint(){
		if(m_entryPoint == nullptr)
			m_entryPoint = new EntryPoint;
		return m_entryPoint;
	}
	
	bool Framework::registerLoader(Loader* loader){
		if(m_loader == nullptr){
			m_loader = loader;
			return false;
		}
		m_loader = loader;
		return true;
	}
	
	bool Framework::registerResourceManager(ResourceManager* assetManager){
		if(m_resourceManager == nullptr){
			m_resourceManager = assetManager;
			return false;
		}
		m_resourceManager = assetManager;
		return true;
	}
	
	bool Framework::registerInput(InputHandler* input){
		if(m_input == nullptr){
			m_input = input;
			return false;
		}
		m_input = input;
		return true;
	}
	
	bool Framework::registerRenderer(Renderer* renderer){
		if(m_renderer == nullptr){
			m_renderer = renderer;
			return false;
		}
		m_renderer = renderer;
		return true;
	}
	
	bool Framework::registerAudioManager(SoundBoard* audioManager){
		if(m_audioManager == nullptr){
			m_audioManager = audioManager;
			return false;
		}
		m_audioManager = audioManager;
		return true;
	}
	
	bool Framework::registerCoreSignal(Signal<CoreSignal>* coreSignal){
		if(m_coreSignal == nullptr){
			m_coreSignal = coreSignal;
			return false;
		}
		m_coreSignal = coreSignal;
		return true;
	}
	
	bool Framework::registerMessage(Signal<Message>* message){
		if(m_message == nullptr){
			m_message = message;
			return false;
		}
		m_message = message;
		return true;
	}
	
	bool Framework::registerEntryPoint(EntryPoint* entryPoint){
		if(m_entryPoint == nullptr){
			m_entryPoint = entryPoint;
			return false;
		}
		m_entryPoint = entryPoint;
		return true;
	}
	
	Framework::~Framework(){
		if(m_loader != nullptr)
			delete m_loader;
		if(m_resourceManager != nullptr)
			delete m_resourceManager;
		if(m_input != nullptr)
			delete m_input;
		if(m_renderer != nullptr)
			delete m_renderer;
		if(m_audioManager != nullptr)
			delete m_audioManager;
		if(m_coreSignal != nullptr)
			delete m_coreSignal;
		if(m_message != nullptr)
			delete m_message;
		if(m_entryPoint != nullptr)
			delete m_entryPoint;
	}
}