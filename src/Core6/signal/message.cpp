//
// Created by Kacper on 08/12/2020.
//

#include "message.hpp"

namespace c6{
	Message::Message(const std::string& message, MessageType type) : m_type(type){
		std::string prefix;
		switch(type){
			case MessageType::Info:
				prefix = "INFO: ";
				break;
			case MessageType::Debug:
				prefix = "DEBUG: ";
				break;
			case MessageType::Error:
				prefix = "ERROR: ";
				break;
		}
		m_message = prefix + message;
	}
	
	std::string Message::write() const{
		return m_message;
	}
	
	MessageType Message::getType() const{
		return m_type;
	}
}