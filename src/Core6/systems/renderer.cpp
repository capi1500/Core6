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

#include "renderer.hpp"

namespace c6{
	/*void Renderer::clear(const sf::Color& color){
		m_window->clear(color);
	}
	
	void Renderer::draw(sf::Drawable* drawable){
		m_window->draw(*drawable, m_renderStates);
	}
	
	void Renderer::display(){
		m_window->display();
	}
	
	void Renderer::setView(const sf::View& view){
		m_window->setView(view);
	}
	
	const sf::View& Renderer::getView() const{
		return m_window->getView();
	}
	
	Renderer::Renderer(sf::RenderWindow* window) : m_window(window){
	}
	
	Renderer::Renderer() : m_window(new sf::RenderWindow(sf::VideoMode(500, 500), "Default Renderer")){
	}
	Renderer::Renderer(const sf::VideoMode& mode, const sf::String& title, unsigned int style, const sf::ContextSettings& settings) : RenderWindow(mode, title, style, settings){
	}
	
	Renderer::Renderer(sf::WindowHandle handle, const sf::ContextSettings& settings) : RenderWindow(handle, settings){
	}
	
	Renderer::Renderer() : RenderWindow(sf::VideoMode(500, 500), "default"){
	}*/
	void Renderer::draw(GraphicComponent* graphicComponent){
		get().draw(*graphicComponent);
	}
}