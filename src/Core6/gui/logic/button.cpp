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
#include <Core6/gui/graphics/widgetGraphics.hpp>
#include <iostream>
#include <Core6/framework.hpp>
#include "button.hpp"

namespace c6::widgets{
	void Button::onNotify(const sf::Event& event) noexcept{
		callback(event);
	}
	
	void Button::setOnHoverStart(const Runnable& onHoverStart){
		Button::onHoverStart = onHoverStart;
	}
	
	void Button::setOnHoverEnd(const Runnable& onHoverEnd){
		Button::onHoverEnd = onHoverEnd;
	}
	
	void Button::setOnClicked(const Runnable& onClicked){
		Button::onClicked = onClicked;
	}
	
	void Button::setOnReleased(const Runnable& onReleased){
		Button::onReleased = onReleased;
	}
	
	Button::Button(WidgetGraphics* graphics, const Runnable& onClicked, const Runnable& onReleased, const Runnable& onHoverStart, const Runnable& onHoverEnd) :
			onClicked(onClicked),
			onReleased(onReleased),
			onHoverStart(onHoverStart),
			onHoverEnd(onHoverEnd),
			callback([graphics, this](const sf::Event& event){
				if(this->onClicked && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
					if(graphics->getGlobalBounds().contains(Framework::getRenderer()->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))){
						clicked = true;
						this->onClicked();
					}
				}
				else if(clicked && this->onReleased && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
					if(graphics->getGlobalBounds().contains(Framework::getRenderer()->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))){
						clicked = false;
						this->onReleased();
					}
					else{
						clicked = false;
						if(this->onHoverEnd)
							this->onHoverEnd();
					}
				}
			}),
			updater([graphics, this](const sf::Time& time){
				if(!clicked){
					if(graphics->getGlobalBounds().contains(Framework::getRenderer()->mapPixelToCoords(sf::Mouse::getPosition(*Framework::getRenderer().get())))){
						if(this->onHoverStart)
							this->onHoverStart();
					}
					else{
						if(this->onHoverEnd)
							this->onHoverEnd();
					}
				}
			}){}
	
	void Button::update(const sf::Time& time){
		updater(time);
	}
	
	ButtonBuilder& ButtonBuilder::setGraphics(WidgetGraphics* graphics){
		ButtonBuilder::graphics = graphics;
		return *this;
	}
	
	ButtonBuilder& ButtonBuilder::setOnHoverStart(const Runnable& onHoverStart){
		ButtonBuilder::onHoverStart = onHoverStart;
		return *this;
	}
	
	ButtonBuilder& ButtonBuilder::setOnHoverEnd(const Runnable& onHoverEnd){
		ButtonBuilder::onHoverEnd = onHoverEnd;
		return *this;
	}
	
	ButtonBuilder& ButtonBuilder::setOnClicked(const Runnable& onClicked){
		ButtonBuilder::onClicked = onClicked;
		return *this;
	}
	
	ButtonBuilder& ButtonBuilder::setOnReleased(const Runnable& onReleased){
		ButtonBuilder::onReleased = onReleased;
		return *this;
	}
	
	Button ButtonBuilder::build(){
		return Button(graphics, onClicked, onReleased, onHoverStart, onHoverEnd);
	}
	
	Button* ButtonBuilder::buildPointer(){
		return new Button(graphics, onClicked, onReleased, onHoverStart, onHoverEnd);
	}
}