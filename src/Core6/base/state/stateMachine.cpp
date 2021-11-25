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

#include <Core6/utils/functional.hpp>
#include <iostream>
#include "stateMachine.hpp"
#include "state.hpp"

namespace c6{
	State* StateMachine::getCurrentState(){
		//std::cout << "Event count: " << eventCount() << "\n";
		processEvents();
		if(pushDownAutomata.empty())
			throw std::runtime_error("No active State in StateMachine");
		return pushDownAutomata.top();
	}
	
	void StateMachine::add(State* newState) noexcept{
		notify([this, newState]{
			if(!pushDownAutomata.empty())
				pushDownAutomata.top()->deactivate();
			pushDownAutomata.push(newState);
			pushDownAutomata.top()->activate();
		});
	}
	
	void StateMachine::pop(unsigned int count) noexcept{
		notify([this, count]{
			if(pushDownAutomata.size() < count)
				throw std::runtime_error("Cannot remove States from StateMachine: not enough states");
			for(unsigned i = 0; i < count; i++){
				delete pushDownAutomata.top();
				pushDownAutomata.pop();
			}
			if(!pushDownAutomata.empty())
				pushDownAutomata.top()->activate();
		});
	}
	
	void StateMachine::replace(State* newState) noexcept{
		notify([this, newState]{
			if(pushDownAutomata.empty())
				throw std::runtime_error("Cannot replace States in StateMachine: StateMachine is empty");
			delete pushDownAutomata.top();
			pushDownAutomata.pop();
			pushDownAutomata.push(newState);
			pushDownAutomata.top()->activate();
		});
	}
	
	void StateMachine::clear() noexcept{
		notify([this]{
			while(!pushDownAutomata.empty()){
				delete pushDownAutomata.top();
				pushDownAutomata.pop();
			}
		});
	}
	
	StateMachine::StateMachine() noexcept : SimpleListener([](const Runnable& event){event();}){
		addListener(this);
	}
	
	StateMachine::~StateMachine() noexcept{
		removeListener(this);
	}
}