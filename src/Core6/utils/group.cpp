//
// Created by Kacper on 08/12/2020.
//

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
				g.reset();
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
			if(g.get() != nullptr and g->isExists() and g->isActive()){
				g->update(time);
			}
		}
	}
	
	void Group::draw(){
		for(auto& g : m_members){
			if(g.get() != nullptr and g->isExists() and g->isVisible())
				g->draw();
		}
	}
	
	size_t Group::indexOf(Gizmo* g){
		for(size_t i = 0; i < m_members.size(); i++){
			if(m_members[i].get() == g)
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
			m_members[i] = std::unique_ptr<Gizmo>(g);
		}
	}
	
	void Group::addToBack(Gizmo* g){
		if(g->getParent() == this)
			return;
		if(g->getParent() != nullptr)
			g->getParent()->remove(g);
		g->setParent(this);
		m_members.push_back(std::unique_ptr<Gizmo>(g));
	}
	
	void Group::erase(Gizmo* g){
		if(g->getParent() != this)
			return;
		size_t i = indexOf(g);
		m_members[i].reset();
		g->setParent(nullptr);
	}
	
	void Group::remove(Gizmo* g){
		size_t i = indexOf(g);
		if(i != m_members.size()){
			if(m_order){
				m_members.erase(m_members.begin() + i);
				m_members[i] = nullptr;
			}
			else{
				std::swap(m_members[i], m_members.back());
				m_members.pop_back();
			}
			g->setParent(nullptr);
		}
	}
	
	void Group::replace(Gizmo* o, Gizmo* n){
		size_t i = indexOf(o);
		if(i != m_members.size()){
			m_members[i].reset(n);
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
	
	Gizmo* Group::getRandom(){
		if(m_members.size() == 0){
			Framework::getMessage()->send(Message("Cannot get random gizmo from group: empty group", MessageType::Error));
			return nullptr;
		}
		return m_members[rand(0ull, m_members.size() - 1)].get();
	}
}