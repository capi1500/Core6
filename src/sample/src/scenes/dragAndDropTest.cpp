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

#include <src/drag_and_drop/dragAndDrop.hpp>
#include <Core6/gui/graphics/primitive.hpp>
#include <Core6/gui/systems/setWidgetParent.hpp>
#include "dragAndDropTest.hpp"

void DragAndDropTest::update(const sf::Time& time){
	Scene::update(time);
	getECS().execute(drag);
}

void DragAndDropTest::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	getECS().execute<const sf::Event&>(isDragged, event);
}

DragAndDropTest::DragAndDropTest(c6::Application<ecsConfig>& application, c6::StateMachine& stateMachine) : Scene(application, stateMachine){
	auto spawnDragAndDropButton = [this](const sf::Vector2f& position){
		auto h = getECS().addWithHandle();
		
		auto* rect = new c6::widgets::Primitive<sf::RectangleShape>();
		rect->get().setSize({50, 50});
		rect->get().setFillColor(sf::Color::Red);
		
		auto* button = c6::widgets::ButtonBuilder()
				.setGraphics(rect)
				.setOnReleased([]{
				
				})
				.setOnHoverStart([rect]{
					rect->get().setFillColor(sf::Color(255, 127, 127));
				})
				.setOnHoverEnd([rect]{
					rect->get().setFillColor(sf::Color::Red);
				})
				.setOnClicked([rect]{
					rect->get().setFillColor(sf::Color(127, 0, 0));
				})
				.buildPointer();
		
		auto& e = c6::EntityBuilder(getECS(), h)
				.attach<Draggable>()
		        .attach<c6::Widget<ecsConfig>>(h, rect, button)
				.attach<c6::component::Transformable>(std::make_shared<sf::Transformable>());
		
		auto& t = e.get<c6::component::Transformable>();
		t->setPosition(position);
		e.get<Draggable>().shouldDrag = [rect, t](const sf::Event& event){
			return event.type == sf::Event::MouseButtonPressed &&
				   event.mouseButton.button == sf::Mouse::Left &&
				  rect->getGlobalBounds().contains(c6::Framework::getRenderer()->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}));
		};
		e.get<Draggable>().shouldEndDrag = [](const sf::Event& event){
			return event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left;
		};
		
		getECS().execute<typename c6::EntityComponentSystem<ecsConfig>::Handle&>(h, c6::system::SetWidgetParent<ecsConfig>, getWidgetRoot());
	};
	
	spawnDragAndDropButton({50, 50});
	spawnDragAndDropButton({500, 200});
	spawnDragAndDropButton({300, 150});
	spawnDragAndDropButton({350, 100});
	getECS().refresh();
}
