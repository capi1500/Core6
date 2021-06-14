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
			case MessageType::Loading:
				prefix = "LOADER: ";
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