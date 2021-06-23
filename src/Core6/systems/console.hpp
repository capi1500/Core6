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

#ifndef CORE6_CONSOLE_HPP
#define CORE6_CONSOLE_HPP

#include <Core6/signal/message.hpp>

namespace c6{
	class Console{
		private:
			static bool m_info;
			static bool m_debug;
			static bool m_error;
			static bool m_loader;
		public:
			static void useMessageType(MessageType type) noexcept;
			
			static void send(const Message& message) noexcept;
	};
}

#endif //CORE6_CONSOLE_HPP
