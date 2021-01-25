//
// Created by Kacper on 09/12/2020.
//

#include <iostream>
#include "scene.hpp"
#include "framework.hpp"

namespace c6{
	void Scene::onSignal(const sf::Event& signal){
		if(signal.type == sf::Event::Closed){
			CoreSignal s;
			s.type = CoreSignal::Close;
			Framework::getCoreSignal()->send(s);
		}
	}
	
	void Scene::onSignal(const CoreSignal& signal){
	
	}
	
	void Scene::draw(){
		Framework::getRenderer()->lock();
		Framework::getRenderer()->get().setView(m_camera);
		Framework::getRenderer()->get().clear();
		Group::draw();
		Framework::getRenderer()->get().display();
		Framework::getRenderer()->unlock();
	}
	
	Scene::Scene(){
		c6::Framework::getInput()->add(this);
	}
}
