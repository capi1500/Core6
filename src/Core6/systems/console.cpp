/**
 * Core6
 * Copyright (C) 2020-2021 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#include <Core6/framework.hpp>
#include <iostream>
#include "console.hpp"

namespace c6{
	Message::Message(const std::string& what, Message::MessageType type) noexcept : what(std::move(what)), type(type){}
	
	void Console::send(const Message& message) const noexcept{
		if(error && message.type == Message::MessageType::Error)
			std::cerr << "ERROR: " + message.what << "\n";
		else if(debug && message.type == Message::MessageType::Debug)
			std::clog << "DEBUG: " + message.what << "\n";
		else if(loader && message.type == Message::MessageType::Loading)
			std::clog << "LOADING: " + message.what << "\n";
		else if(info && message.type == Message::MessageType::Info)
			std::cout << "INFO: " + message.what << "\n";
	}
	
	Console::Console(bool mInfo, bool mDebug, bool mError, bool mLoader) noexcept : info(mInfo), debug(mDebug), error(mError), loader(mLoader){}
	
	Console ConsoleBuilder::create(){
		return Console(info, debug, error, loader);
	}
	
	ConsoleBuilder& ConsoleBuilder::useMessageType(Message::MessageType type) noexcept{
		switch(type){
			case Message::MessageType::Info:
				info = true;
				break;
			case Message::MessageType::Debug:
				debug = true;
				break;
			case Message::MessageType::Error:
				error = true;
				break;
			case Message::MessageType::Loading:
				loader = true;
				break;
		}
		return *this;
	}
}