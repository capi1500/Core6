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
	bool Console::m_info = false;
	bool Console::m_debug = false;
	bool Console::m_error = false;
	bool Console::m_loader = false;
	
	void Console::useMessageType(MessageType type) noexcept{
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
			case MessageType::Loading:
				m_loader = true;
				break;
		}
	}
	
	void Console::send(const Message& signal) noexcept{
		if(signal.getType() == MessageType::Error and m_error)
			std::cerr << signal.write() << "\n";
		else if(signal.getType() == MessageType::Debug and m_debug)
			std::clog << signal.write() << "\n";
		else if(signal.getType() == MessageType::Info and m_info)
			std::cout << signal.write() << "\n";
		else if(signal.getType() == MessageType::Loading and m_loader)
			std::clog << signal.write() << "\n";
	}
}