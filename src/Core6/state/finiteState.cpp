//
// Created by Kacper on 09/12/2020.
//

#include "finiteState.hpp"

namespace c6{
	FiniteState::FiniteState() : Gizmo(){
		m_active = false;
	}
	
	void FiniteState::setIsActive(bool active){
		m_active = active;
	}
}