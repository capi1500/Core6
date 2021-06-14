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

#include <Core6/signal/message.hpp>
#include "finiteStateMachine.hpp"
#include <Core6/systems/console.hpp>
#include <Core6/signal/signal.hpp>

namespace c6{
	FiniteState* FiniteStateMachine::getCurrentState(){
		processEvents();
		if(m_pushdownAutomaton.empty()){
			Console::send(Message("No active FiniteStates in FiniteStateMachine", MessageType::Error));
			return nullptr;
		}
		return m_pushdownAutomaton.top();
	}
	
	void FiniteStateMachine::add(FiniteState* newState){
		FiniteStateEvent event;
		event.type = FiniteStateEvent::Add;
		event.add.what = newState;
		send(event);
	}
	
	void FiniteStateMachine::pop(int count){
		FiniteStateEvent event;
		event.type = FiniteStateEvent::Pop;
		event.pop.count = count;
		send(event);
	}
	
	void FiniteStateMachine::replace(FiniteState* newState){
		FiniteStateEvent event;
		event.type = FiniteStateEvent::Replace;
		event.replace.what = newState;
		send(event);
	}
	
	void FiniteStateMachine::clear(){
		FiniteStateEvent event;
		event.type = FiniteStateEvent::Clear;
		send(event);
	}
	
	FiniteStateMachine::FiniteStateMachine(){
		Signal<FiniteStateEvent>::add(this);
	}
	
	FiniteStateMachine::~FiniteStateMachine(){
		Signal<FiniteStateEvent>::remove(this);
	}
	
	void FiniteStateMachine::onSignal(const FiniteStateEvent& signal){
		if(signal.type == FiniteStateEvent::Add){
			if(not m_pushdownAutomaton.empty())
				m_pushdownAutomaton.top()->setIsActive(false);
			m_pushdownAutomaton.push(signal.add.what);
			m_pushdownAutomaton.top()->setIsActive(true);
		}
		else if(signal.type == FiniteStateEvent::Pop){
			for(unsigned i = 0; i < signal.pop.count; i++){
				if(m_pushdownAutomaton.empty()){
					Console::send(Message("Cannot pop states: No states in FiniteStateMachine", MessageType::Error));
					return;
				}
				delete m_pushdownAutomaton.top();
				m_pushdownAutomaton.pop();
				if(not m_pushdownAutomaton.empty())
					m_pushdownAutomaton.top()->setIsActive(true);
			}
		}
		else if(signal.type == FiniteStateEvent::Replace){
			if(m_pushdownAutomaton.empty()){
				Console::send(Message("Cannot pop states: No states in FiniteStateMachine", MessageType::Error));
				return;
			}
			delete m_pushdownAutomaton.top();
			m_pushdownAutomaton.pop();
			m_pushdownAutomaton.push(signal.replace.what);
			m_pushdownAutomaton.top()->setIsActive(true);
		}
		else if(signal.type == FiniteStateEvent::Clear){
			while(not m_pushdownAutomaton.empty()){
				delete m_pushdownAutomaton.top();
				m_pushdownAutomaton.pop();
			}
		}
	}
}