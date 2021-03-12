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

#include <Core6/utils/commonFunctions.hpp>
#include "group.hpp"
#include "Core6/framework.hpp"

namespace c6{
	Group::Group(bool order) : Gizmo(), m_order(false){
	}
	
	void Group::destroy(){
		Gizmo::kill();
		for(auto& g : m_members){
			if(g != nullptr){
				g->destroy();
				delete g;
			}
		}
		m_members.clear();
	}
	
	void Group::kill(){
		for(auto& g : m_members){
			if(g != nullptr and g->isExists())
				g->kill();
		}
		Gizmo::kill();
	}
	
	void Group::update(const sf::Time& time){
		for(auto& g : m_members){
			if(g != nullptr and g->isExists() and g->isActive()){
				g->update(time);
			}
		}
	}
	
	void Group::draw(){
		for(auto& g : m_members){
			if(g != nullptr and g->isExists() and g->isVisible())
				g->draw();
		}
	}
	
	size_t Group::indexOf(Gizmo* g){
		for(size_t i = 0; i < m_members.size(); i++){
			if(m_members[i] == g)
				return i;
		}
		return m_members.size();
	}
	
	void Group::add(Gizmo* g){
		if(g->getParent() == this)
			return;
		if(g->getParent() != nullptr)
			g->getParent()->remove(g);
		size_t i = indexOf(nullptr);
		if(i >= m_members.size())
			addToBack(g);
		else{
			g->setParent(this);
			m_members[i] = g;
		}
	}
	
	void Group::addToBack(Gizmo* g){
		if(g->getParent() == this)
			return;
		if(g->getParent() != nullptr)
			g->getParent()->remove(g);
		g->setParent(this);
		m_members.push_back(g);
	}
	
	void Group::erase(Gizmo* g){
		if(g->getParent() != this)
			return;
		size_t i = indexOf(g);
		delete m_members[i];
		m_members[i] = nullptr;
		g->setParent(nullptr);
	}
	
	void Group::remove(Gizmo* g){
		size_t i = indexOf(g);
		if(i != m_members.size()){
			if(m_order){
				m_members.erase(m_members.begin() + i);
			}
			else{
				std::swap(m_members[i], m_members.back());
				delete m_members.back();
				m_members.pop_back();
			}
			g->setParent(nullptr);
		}
	}
	
	void Group::replace(Gizmo* o, Gizmo* n){
		size_t i = indexOf(o);
		if(i != m_members.size()){
			delete m_members[i];
			m_members[i] = nullptr;
			o->setParent(nullptr);
			n->setParent(this);
		}
	}
	
	size_t Group::countLiving(){
		size_t out = 0;
		for(auto& g : m_members){
			if(g != nullptr and g->isExists() and g->isAlive())
				out++;
		}
		return out;
	}
	
	size_t Group::countDead(){
		size_t out = 0;
		for(auto& g : m_members){
			if(g != nullptr and not g->isAlive())
				out++;
		}
		return out;
	}
	
	size_t Group::count(){
		return m_members.size();
	}
	
	Gizmo* Group::getRandom(){
		if(m_members.size() == 0){
			Framework::getMessage()->send(Message("Cannot get random gizmo from group: empty group", MessageType::Error));
			return nullptr;
		}
		return m_members[rand(0ull, m_members.size() - 1)];
	}
	
	Gizmo* Group::getGizmo(size_t at){
		if(m_members.size() <= at){
			Framework::getMessage()->send(Message("Cannot get gizmo from group: index bigger than group's size", MessageType::Error));
			return nullptr;
		}
		return m_members[at];
	}
}