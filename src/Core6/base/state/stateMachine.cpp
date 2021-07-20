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

#include "stateMachine.hpp"
#include "stateEvent.hpp"
#include "state.hpp"

namespace c6{
	State* StateMachine::getCurrentState(){
		processEvents();
		if(pushDownAutomata.empty())
			throw std::runtime_error("No active State in StateMachine");
		return pushDownAutomata.top();
	}
	
	void StateMachine::add(State* newState) noexcept{
		notify(StateEvent::add(newState));
	}
	
	void StateMachine::pop(unsigned int count) noexcept{
		notify(StateEvent::pop(count));
	}
	
	void StateMachine::replace(State* newState) noexcept{
		notify(StateEvent::replace(newState));
	}
	
	void StateMachine::clear() noexcept{
		notify(StateEvent::clear());
	}
	
	StateMachine::StateMachine() noexcept : SimpleListener(
			[this](const StateEvent& event){
				switch(event.getType()){
					case StateEvent::Add:
						if(!pushDownAutomata.empty())
							pushDownAutomata.top()->deactivate();
						pushDownAutomata.push(event.getNewState());
						pushDownAutomata.top()->activate();
						break;
					case StateEvent::Pop:
						if(pushDownAutomata.size() < event.getRemoveCount())
							throw std::runtime_error("Cannot remove States from StateMachine: not enough states");
						for(unsigned i = 0; i < event.getRemoveCount(); i++){
							delete pushDownAutomata.top();
							pushDownAutomata.pop();
						}
						if(!pushDownAutomata.empty())
							pushDownAutomata.top()->activate();
						break;
					case StateEvent::Replace:
						if(pushDownAutomata.empty())
							throw std::runtime_error("Cannot replace States in StateMachine: StateMachine is empty");
						delete pushDownAutomata.top();
						pushDownAutomata.pop();
						pushDownAutomata.push(event.getNewState());
						pushDownAutomata.top()->activate();
						break;
					case StateEvent::Clear:
						while(!pushDownAutomata.empty()){
							delete pushDownAutomata.top();
							pushDownAutomata.pop();
						}
						break;
				}
			}){
		addListener(this);
	}
	
	StateMachine::~StateMachine() noexcept{
		removeListener(this);
	}
}