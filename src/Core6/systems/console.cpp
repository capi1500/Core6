//
// Created by Kacper on 08/12/2020.
//

#include <Core6/framework.hpp>
#include <iostream>
#include "console.hpp"

namespace c6{
	Console::Console(){
		Framework::getMessage()->add(this);
		m_info = m_debug = m_error = false;
	}
	
	Console::~Console(){
		Framework::getMessage()->remove(this);
	}
	
	void Console::useMessageType(MessageType type){
		switch(type){
			case MessageType::Info:
				m_info = true;
				break;
			case MessageType::Debug:
				m_debug = true;
				break;
			case MessageType::Error:
				m_error = true;
				break;
		}
	}
	
	void Console::onSignal(const Message& signal){
		if(signal.getType() == MessageType::Error and m_error)
			std::cerr << signal.write() << "\n";
		else if(signal.getType() == MessageType::Debug and m_debug)
			std::clog << signal.write() << "\n";
		else if(signal.getType() == MessageType::Info and m_info)
			std::cout << signal.write() << "\n";
	}
}