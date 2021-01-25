//
// Created by Kacper on 08/12/2020.
//

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