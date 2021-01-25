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

#ifndef CORE6_APPLICATION_HPP
#define CORE6_APPLICATION_HPP

#include <Core6/framework.hpp>
#include <Core6/systems/console.hpp>
#include <SFML/System/Clock.hpp>
#include <Core6/state/finiteStateMachine.hpp>
#include <Core6/scene.hpp>
#include "bundle.hpp"

namespace c6{
	class Application : public Listener<CoreSignal>{
		protected:
			Console m_console;
			sf::Clock m_clock;
			FiniteStateMachine m_finiteStateMachine;
			
			Scene* getScene();
		public:
			void onSignal(const CoreSignal& signal) override;
			
			virtual void run() = 0;
	};
}

#endif //CORE6_APPLICATION_HPP
