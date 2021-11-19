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

#include "mainMenu.hpp"
#include <Core6/application.hpp>
#include <Core6/gui/graphics/image.hpp>
#include <Core6/gui/systems/setWidgetParent.hpp>

MainMenu::MainMenu(c6::Application<ecsConfig>& app, c6::StateMachine& stateMachine) : Scene(app, stateMachine){
	c6::Framework::getResourceManager()->loadTextures("../assets/textures/rgb");
	c6::Framework::getResourceManager()->loadFonts("../assets/fonts");
	
	auto* image = new c6::widgets::Image();
	sf::Sprite sprite;
	sprite.setTexture(c6::Framework::getResourceManager()->getTexture("../assets/textures/rgb/red.png"));
	image->setSprite(sprite);
	auto* button = new c6::widgets::Button(image, []{std::cout << "Clicked\n";});
	
	auto h = getECS().addWithHandle();
	auto& builder = c6::EntityBuilder<ecsConfig>(getECS(), h)
	        .attach<c6::Widget<ecsConfig>>(h, image, button)
			.attach<c6::component::Transformable>(std::make_shared<sf::Transformable>());
	
	auto& widget = builder.get<c6::Widget<ecsConfig>>();
	
	getECS().execute<typename c6::EntityComponentSystem<ecsConfig>::Handle&>(h, c6::system::SetWidgetParent<ecsConfig>, getWidgetRoot());
	
	auto& transformable = builder.get<c6::component::Transformable>();
	transformable->move(50, 20);
	
	getECS().refresh();
}

void MainMenu::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	getECS().execute<const sf::Event&>(ecsEventHandler, event);
}
