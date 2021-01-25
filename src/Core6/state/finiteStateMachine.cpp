//
// Created by Kacper on 09/12/2020.
//

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