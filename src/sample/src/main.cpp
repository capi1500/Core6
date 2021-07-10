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

#include <Core6/framework.hpp>
#include <Core6/systems/inputHandler.hpp>
#include <Core6/ecs/entityComponentSystem.hpp>
#include "init.hpp"

int main(){
	c6::Console console = c6::ConsoleBuilder().useMessageType(c6::Message::Info)
	                                          .useMessageType(c6::Message::Error)
	                                          .useMessageType(c6::Message::Debug)
	                                          .useMessageType(c6::Message::Loading)
	                                          .create();
	
	c6::Framework::getRenderer().attachConsole(console);
	c6::Framework::getResourceManager().attachConsole(console);
	c6::Framework::getSoundboard().attachConsole(console);
	
	ECS ecs;
	c6::EntityFactory<ecsConfig, std::string, sf::Vector2f, bool> spriteSpawner(
			[](ECS& ecs, EntityId id, std::string&& path, sf::Vector2f&& pos, bool&& isMovable){
				sf::Sprite& s = ecs.addComponent<sf::Sprite>(id);
				s.setTexture(c6::Framework::getResourceManager().getTexture(path));
				s.setPosition(std::forward<sf::Vector2f>(pos));
				
				if(isMovable)
					ecs.addTag<Movable>(id);
				
				ecs.addComponent<std::string>(id, std::forward<std::string>(path));
			}
	);
	c6::System<ecsConfig, c6::Signature<c6::EntityState, sf::Sprite>, c6::Renderer&> drawSystem(
			[](c6::EntityState& entityState, sf::Sprite& sprite, c6::Renderer& window){
				if(entityState.visible)
					window.draw(sprite);
			}
	);
	c6::System<ecsConfig, c6::Signature<c6::EntityState, sf::Sprite, Movable>, const sf::Time&> updateSystem(
			[](c6::EntityState& entityState, sf::Sprite& sprite, const sf::Time& deltaTime){
				if(entityState.active){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
						sprite.move(0, -deltaTime.asSeconds() * 100);
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
						sprite.move(0, deltaTime.asSeconds() * 100);
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
						sprite.move(-deltaTime.asSeconds() * 100, 0);
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
						sprite.move(deltaTime.asSeconds() * 100, 0);
				}
			}
	);
	c6::System<ecsConfig, c6::Signature<c6::EntityState>> destroySystem(
			[](ECS& ecs, EntityId id, c6::EntityState& state){
				if(!ecs.hasTag<Special>(id)){
					state.exists = false;
				}
				else{
					if(ecs.hasTag<Movable>(id))
						ecs.deleteTag<Movable>(id);
					else
						ecs.addTag<Movable>(id);
				}
			}
	);
	
	c6::Framework::getRenderer().create(sf::VideoMode(500, 500), "test");
	
	c6::InputHandler inputHandler;
	inputHandler.addListener(
			new c6::SimpleListener<sf::Event>([](const sf::Event& event){
				if(event.type == sf::Event::Closed){
					c6::Framework::getRenderer().close();
				}
			})
	);
	
	c6::Framework::getResourceManager().loadTextures("../assets/textures/rgb/");
	
	ecs.addFromFactory(spriteSpawner, std::string("../assets/textures/rgb/blue.png"), sf::Vector2f(100, 100), true);
	ecs.addFromFactory(spriteSpawner, std::string("../assets/textures/rgb/red.png"), sf::Vector2f(150, 100), false);
	ecs.addFromFactory(spriteSpawner, std::string("../assets/textures/rgb/magenta.png"), sf::Vector2f(200, 100), false);
	ecs.addFromFactory(spriteSpawner, std::string("../assets/textures/rgb/yellow.png"), sf::Vector2f(250, 100), true);
	ecs.addFromFactory(spriteSpawner, std::string("../assets/textures/rgb/green.png"), sf::Vector2f(300, 100), false);
	Entity specialEntity = ecs.addWithHandleFromFactory(spriteSpawner, std::string("../assets/textures/rgb/cyan.png"), sf::Vector2f(200, 200), false);
	ecs.addTag<Special>(specialEntity);
	ecs.refresh();
	
	inputHandler.addListener(
			new c6::SimpleListener<sf::Event>([&specialEntity, &ecs](const sf::Event& event){
				if(event.type == sf::Event::MouseButtonPressed){
					if(event.mouseButton.button == sf::Mouse::Left)
						ecs.getComponent<sf::Sprite>(specialEntity).setTexture(c6::Framework::getResourceManager().getTexture("../assets/textures/rgb/white.png"));
					else if(event.mouseButton.button == sf::Mouse::Right)
						ecs.getComponent<sf::Sprite>(specialEntity).setTexture(c6::Framework::getResourceManager().getTexture("../assets/textures/rgb/cyan.png"));
				}
			})
	);
	
	inputHandler.addListener(
			new c6::SimpleListener<sf::Event>([&ecs, &destroySystem](const sf::Event& event){
				if(event.type == sf::Event::LostFocus){
					ecs.execute(destroySystem);
					ecs.refresh();
				}
			})
	);
	
	sf::Clock clock;
	while(c6::Framework::getRenderer().isOpen()){
		inputHandler.handleEvents(&c6::Framework::getRenderer());
		
		ecs.execute<const sf::Time&>(updateSystem, clock.restart());
		
		c6::Framework::getRenderer().clear();
		ecs.execute<c6::Renderer&>(drawSystem, c6::Framework::getRenderer());
		c6::Framework::getRenderer().display();
	}
}