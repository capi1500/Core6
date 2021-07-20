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

#include <Core6/base/listener/emitter.hpp>
#include <Core6/base/listener/listener.hpp>
#include <Core6/base/interfaces/builder.hpp>
#include <string>

namespace c6{
	struct Message{
		enum MessageType{
			Info,
			Debug,
			Error,
			Loading
		};
		
		const std::string what;
		const MessageType type;
		Message(const std::string& what, MessageType type) noexcept;
	};
	
	class Console{
		private:
			bool info;
			bool debug;
			bool error;
			bool loader;
		public:
			void send(const Message& message) const noexcept;
			Console(bool mInfo, bool mDebug, bool mError, bool mLoader) noexcept;
	};
	
	class ConsoleBuilder : public Builder<Console>{
		private:
			bool info = false;
			bool debug = false;
			bool error = false;
			bool loader = false;
		public:
			ConsoleBuilder& useMessageType(Message::MessageType type) noexcept;
			Console create() override;
	};
}

#endif //CORE6_CONSOLE_HPP
