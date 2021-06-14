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

#ifndef CORE6_INPUTHANDLER_HPP
#define CORE6_INPUTHANDLER_HPP

#include <Core6/signal/signal.hpp>
#include <SFML/Window.hpp>
#include <memory>

namespace c6{
	namespace base{
		class InputHandler : public Signal<sf::Event>{
		
		};
	}
	
	namespace concepts{
		template<class T> concept InputHandler = requires{
			std::is_base_of_v<base::InputHandler, T>;
		};
	}
	
	class InputHandler : public base::InputHandler{
		private:
			sf::Window* m_window;
		public:
			void handleInput();
			
			void registerWindow(sf::Window* window);
			virtual ~InputHandler();
	};
}

#endif //CORE6_INPUTHANDLER_HPP