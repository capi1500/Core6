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
#include "Core6/framework.hpp"

namespace c6{
	void FiniteStateMachine::update(){
		while((not m_pushdownAutomaton.empty()) and m_pushdownAutomaton.top()->isExists() == false){
			m_pushdownAutomaton.top().reset();
			m_pushdownAutomaton.pop();
		}
	}
	
	FiniteState* FiniteStateMachine::getCurrentState(){
		update();
		if(m_pushdownAutomaton.empty()){
			Framework::getMessage()->send(Message("No active FiniteStates in FiniteStateMachine", MessageType::Error));
			return nullptr;
		}
		m_pushdownAutomaton.top()->setIsActive(true);
		return m_pushdownAutomaton.top().get();
	}
	
	void FiniteStateMachine::addState(FiniteState* state){
		if(not m_pushdownAutomaton.empty())
			getCurrentState()->setIsActive(false);
		state->setIsActive(true);
		m_pushdownAutomaton.push(std::unique_ptr<FiniteState>(state));
	}
}