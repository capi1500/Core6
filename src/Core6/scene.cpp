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

#include <iostream>
#include "scene.hpp"
#include "framework.hpp"

namespace c6{
	void Scene::draw(){
		Framework::getRenderer()->lock();
		Framework::getRenderer()->get().setView(m_camera);
		Framework::getRenderer()->get().clear();
		Group::draw();
		Framework::getRenderer()->get().display();
		Framework::getRenderer()->unlock();
	}
	
	Scene::Scene(FiniteStateMachine& finiteStateMachine) : FiniteState(finiteStateMachine){
		c6::Framework::getInput()->add(this);
	}
	
	Scene::Scene(FiniteStateMachine& finiteStateMachine, const std::function<void(const sf::Event&)>& f) : FiniteState(finiteStateMachine), Listener<sf::Event>(f){
	
	}
	
	void Scene::addAgent(Spawner& factory, unsigned int layer){
		if(layer >= count())
			resize(layer + 1);
		dynamic_cast<Group*>(getGizmo(layer))->addToBack(new Agent(factory));
	}
	
	void Scene::resize(size_t size){
		while(size >= Group::count())
			addToBack(new Group);
	}
}
