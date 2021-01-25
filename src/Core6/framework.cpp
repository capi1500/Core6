//
// Created by Kacper on 08/12/2020.
//

#include "framework.hpp"

namespace c6{
	Loader* Framework::m_loader = nullptr;
	AssetManager* Framework::m_assetManager = nullptr;
	InputHandler* Framework::m_input = nullptr;
	Renderer* Framework::m_renderer = nullptr;
	AudioManager* Framework::m_audioManager = nullptr;
	Signal<Message>* Framework::m_message = nullptr;
	Signal<CoreSignal>* Framework::m_coreSignal = nullptr;
	
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
	
	AudioManager* Framework::getAudioManager(){
		if(m_audioManager == nullptr)
			m_audioManager = new AudioManager;
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
	
	AssetManager* Framework::getAssetManager(){
		if(m_assetManager == nullptr)
			m_assetManager = new AssetManager;
		return m_assetManager;
	}
	
	bool Framework::registerLoader(Loader* loader){
		if(m_loader == nullptr){
			m_loader = loader;
			return false;
		}
		m_loader = loader;
		return true;
	}
	
	bool Framework::registerAssetManager(AssetManager* assetManager){
		if(m_assetManager == nullptr){
			m_assetManager = assetManager;
			return false;
		}
		m_assetManager = assetManager;
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
	
	bool Framework::registerAudioManager(AudioManager* audioManager){
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
	
	bool Framework::registerMesage(Signal<Message>* message){
		if(m_message == nullptr){
			m_message = message;
			return false;
		}
		m_message = message;
		return true;
	}
	
	Framework::~Framework(){
		if(m_loader != nullptr)
			delete m_loader;
		if(m_assetManager != nullptr)
			delete m_assetManager;
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
	}
}