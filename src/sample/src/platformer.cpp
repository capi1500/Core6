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

#include <Core6/gui/graphics/primitive.hpp>
#include <Core6/gui/systems/setWidgetParent.hpp>
#include "platformer.hpp"
#include "scenes/mainMenu.hpp"

void Platformer::init(){
	Application::init();
	c6::Framework::getRenderer()->create(sf::VideoMode(600, 500), "Platformer");
	
	c6::Framework::getResourceManager()->loadTextures("../assets/textures/cubes/PNG/Voxel tiles");
	c6::Framework::getResourceManager()->loadFonts("../assets/fonts");
	
	getScenes().add(new MainMenu(*this, getScenes()));
}

void Platformer::close(){
	Application::close();
	c6::Framework::getRenderer()->close();
}

Platformer::Platformer() : c6::Application<ecsConfig>(c6::ConsoleBuilder()
																	.useMessageType(c6::Message::Loading)
																	.useMessageType(c6::Message::Debug)
																	.useMessageType(c6::Message::Error)
																	.useMessageType(c6::Message::Info)
																	.create()),
						   textButtonFactory([](c6::EntityComponentSystem<ecsConfig>& ecs, c6::EntityComponentSystem<ecsConfig>::Handle& parent, const c6::Runnable& runnable, const std::string& label, const sf::Vector2f& position){
							   auto* text = new c6::widgets::Primitive<sf::Text>();
							   text->get().setFont(c6::Framework::getResourceManager()->getFont("../assets/fonts/Pixeled.ttf"));
							   text->get().setString(label);
							   text->get().setPosition(position.x - text->get().getLocalBounds().width / 2, position.y - text->get().getLocalBounds().height / 2);
							
							   auto* button = c6::widgets::ButtonBuilder()
									   .setGraphics(text)
									   .setOnReleased(runnable)
									   .setOnHoverStart([text]{
										   text->get().setFillColor(sf::Color(255, 127, 127));
									   })
									   .setOnHoverEnd([text]{
										   text->get().setFillColor(sf::Color(255, 255, 255));
									   })
									   .setOnClicked([text]{
										   text->get().setFillColor(sf::Color(127, 127, 127));
									   })
									   .buildPointer();
							
							   auto h = ecs.addWithHandle();
							   auto& builder = c6::EntityBuilder<ecsConfig>(ecs, h)
									   .attach<c6::Widget<ecsConfig>>(h, text, button)
									   .attach<c6::component::Transformable>(std::make_shared<sf::Transformable>());
							
							   ecs.execute<typename c6::EntityComponentSystem<ecsConfig>::Handle&>(h, c6::system::SetWidgetParent<ecsConfig>, parent);
							   return builder;
						   }){
	
}

const c6::Function<c6::EntityBuilder<ecsConfig>, c6::EntityComponentSystem<ecsConfig>&, c6::EntityComponentSystem<ecsConfig>::Handle&, const c6::Runnable&, const std::string&, const sf::Vector2f&>& Platformer::getTextButtonFactory() const{
	return textButtonFactory;
}
