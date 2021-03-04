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

#include "gizmo.hpp"
#include "group.hpp"

namespace c6{
	Gizmo::Gizmo(){
		m_exists = true;
		m_active = true;
		m_alive = true;
		m_visible = true;
		
		m_parent = nullptr;
	}
	
	Gizmo::~Gizmo(){
		destroy();
	}
	
	void Gizmo::destroy(){
		m_parent = nullptr;
	}
	
	void Gizmo::kill(){
		m_alive = false;
		m_exists = false;
	}
	
	void Gizmo::revive(){
		m_alive = true;
		m_exists = true;
	}
	
	void Gizmo::killAndErase(){
		kill();
		if(m_parent != nullptr)
			m_parent->remove(this);
	}
	
	void Gizmo::remove(){
		if(m_parent != nullptr)
			m_parent->remove(this);
	}
	
	void Gizmo::update(const sf::Time& time){
	}
	
	void Gizmo::draw(){
	}
	
	bool Gizmo::isExists() const{
		return m_exists;
	}
	
	bool Gizmo::isAlive() const{
		return m_alive;
	}
	
	bool Gizmo::isActive() const{
		if(m_parent == nullptr)
			return m_active;
		return m_active and m_parent->isActive();
	}
	
	bool Gizmo::isVisible() const{
		if(m_parent == nullptr)
			return m_visible;
		return m_visible and m_parent->isVisible();
	}
	
	Group* Gizmo::getParent() const{
		return m_parent;
	}
	
	void Gizmo::setParent(Group* group){
		m_parent = group;
	}
}