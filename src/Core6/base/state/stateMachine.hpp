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

#pragma once

#include <stack>
#include "../listener/listener.hpp"
#include "../listener/emitter.hpp"
#include <Core6/utils/functional.hpp>

namespace c6{
	class State;
	
	class StateMachine : public SimpleListener<Runnable>, public Emitter<Runnable>{
		private:
			std::stack<State*> pushDownAutomata;
		public:
			State* getCurrentState();
			
			void add(State* newState) noexcept;
			void pop(unsigned count = 1) noexcept;
			void replace(State* newState) noexcept;
			void clear() noexcept;
			
			StateMachine() noexcept;
			~StateMachine() noexcept override;
	};
}


