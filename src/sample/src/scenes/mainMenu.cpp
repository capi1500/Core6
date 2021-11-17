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

MainMenu::MainMenu(c6::Application<ecsConfig>& app, c6::StateMachine& stateMachine) : Scene(app, stateMachine){
	c6::Framework::getResourceManager()->loadTextures("../assets/textures/rgb");
	c6::Framework::getResourceManager()->loadFonts("../assets/fonts");
	
	auto buttonFactory = c6::EntityFactoryInline<ecsConfig, const std::string&, int, c6::Runnable>(
			[](c6::EntityComponentSystem<ecsConfig>& ecs, c6::EntityComponentSystem<ecsConfig>::EntityId id, const std::string& label, int n, const c6::Runnable& callback){
				auto b = c6::EntityBuilder<ecsConfig>(ecs, id)
						.attach<sf::Text>(
								c6::Function<sf::Text>(
										[&label, &n]{
											sf::Text text;
											text.setFont(c6::Framework::getResourceManager()->getFont("../assets/fonts/Pixeled.ttf"));
											text.setCharacterSize(20);
											text.setString(label);
											text.setPosition(
													(c6::Framework::getRenderer()->getSize().x - text.getLocalBounds().width) / 2,
													(c6::Framework::getRenderer()->getSize().y - text.getLocalBounds().height) / 2 + n * 40
											);
											return text;
										}
								)
						);
				
				b.attach<c6::Consumer<const sf::Event&>, sf::Transformable>(
						c6::Function<c6::Consumer<const sf::Event&>, sf::Transformable&>(
							[callback](sf::Transformable& transformable){
								return [callback, &transformable](const sf::Event& event){
									const auto& t = dynamic_cast<const sf::Text&>(transformable);
									if(event.type == sf::Event::MouseButtonPressed){
										if(t.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
											callback();
									}
								};
							}
						)
				);
			}
	);
	
	getECS().addFromFactory<const std::string&, int, c6::Runnable>(buttonFactory, "Press [1] to play", 0, []{
				std::cout << "Play!\n";
			}
	);
	getECS().addFromFactory<const std::string&, int, c6::Runnable>(buttonFactory, "Press [2] to exit", 1, [this]{
				getApplication().close();
			}
	);
	
	getECS().refresh();
}

void MainMenu::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	getECS().execute<const sf::Event&>(ecsEventHandler, event);
}
