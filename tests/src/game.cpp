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

#include <src/objects/rectComponent.hpp>
#include "game.hpp"
#include <box2d/b2_common.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <Core6/widgets/factories.hpp>

void Game::run(){
	Scene* scene;
	sf::Time time;
	
	while(m_active){
		time = m_clock.restart();
		scene = getScene();
		
		Framework::getInputHandler().handleInput();
		
		scene->update(time);
		
		scene->draw();
	}
}

c6::Scene<Config>* Game::scene1(){
	c6::Scene<Config>* scene = new c6::Scene<Config>(m_finiteStateMachine, [&](const sf::Event& event){
		if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Num2){
			m_finiteStateMachine.add(scene2());
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Backspace){
			m_finiteStateMachine.pop();
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Numpad2){
			m_finiteStateMachine.replace(scene2());
		}
	});
	scene->addTimeSystem(move);
	scene->addRenderSystem(draw);
	
	Factory<int, int, sf::Color> f([](Agent& a, int x, int y, sf::Color color){
		RectComponent* r = c6::EntryPoint::getTemplate<RectComponent>("rect");
		r->r.setFillColor(color);
		r->setPosition(x, y);
		a.addComponent<Drawable>(r);
		a.addComponent<Transformable>(r);
		a.addTag<Rect>();
	});
	
	scene->newAgent(f, 100, 100, sf::Color::Red);
	scene->newAgent(f, 0, 0, sf::Color::Green);
	
	assetPack.font = Framework::getResourceManager().getFont("../assets/fonts/Pixeled.ttf");
	
	assetPack.frame.regular.part[0][0] =
	assetPack.frame.highlighted.part[0][0] =
	assetPack.frame.disabled.part[0][0] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/blue.png");
	assetPack.frame.regular.part[0][1] =
	assetPack.frame.highlighted.part[0][1] =
	assetPack.frame.disabled.part[0][1] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/cyan.png");
	assetPack.frame.regular.part[0][2] =
	assetPack.frame.highlighted.part[0][2] =
	assetPack.frame.disabled.part[0][2] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/red.png");
	assetPack.frame.regular.part[1][0] =
	assetPack.frame.highlighted.part[1][0] =
	assetPack.frame.disabled.part[1][0] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/white.png");
	assetPack.frame.regular.part[1][1] =
	assetPack.frame.highlighted.part[1][1] =
	assetPack.frame.disabled.part[1][1] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/green.png");
	assetPack.frame.regular.part[1][2] =
	assetPack.frame.highlighted.part[1][2] =
	assetPack.frame.disabled.part[1][2] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/red.png");
	assetPack.frame.regular.part[2][0] =
	assetPack.frame.highlighted.part[2][0] =
	assetPack.frame.disabled.part[2][0] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/blue.png");
	assetPack.frame.regular.part[2][1] =
	assetPack.frame.highlighted.part[2][1] =
	assetPack.frame.disabled.part[2][1] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/magenta.png");
	assetPack.frame.regular.part[2][2] =
	assetPack.frame.highlighted.part[2][2] =
	assetPack.frame.disabled.part[2][2] =
			Framework::getResourceManager().getTexture("../assets/textures/rgb/white.png");
	
	scene->newAgent<const c6::WidgetAssetPack&, const sf::Vector2f&, const sf::Vector2u&, const std::string&>
	        (c6::widget::factory::labelFactory<Config>, assetPack, sf::Vector2f(300, 300), sf::Vector2u(9, 5), "tekst");
	
	return scene;
}

Scene* Game::scene2(){
	Scene* scene = new Scene(m_finiteStateMachine, [&](const sf::Event& event){
		if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Num1){
			m_finiteStateMachine.add(scene1());
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Backspace){
			m_finiteStateMachine.pop();
		} else if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Numpad1){
			m_finiteStateMachine.replace(scene1());
		}
	});
	
	Factory<sf::Vector2f, sf::Vector2f> ground([this, scene](Agent& agent, sf::Vector2f pos, sf::Vector2f size){
		RectComponent* r = new RectComponent;
		r->r.setSize(size);
		r->r.setFillColor(sf::Color::Green);
		r->setOrigin(size.x / 2, size.y / 2);
		
		agent.addComponent<Drawable>(r);
		agent.addComponent<Transformable>(r);
		
		b2BodyDef groundBodyDef;
		groundBodyDef.position = PhysicsConfig::pixelToMeter(pos);
		
		b2PolygonShape groundBox;
		b2Vec2 s = PhysicsConfig::pixelToMeter({size.x / 2, size.y / 2});
		groundBox.SetAsBox(s.x, s.y);
		
		Physic p = scene->getWorld().CreateBody(&groundBodyDef);
		p->CreateFixture(&groundBox, 0.f);
		
		agent.addTag<c6::ecs::tag::PhysicallyMoving>();
		agent.addComponent<Physic>(p);
	});
	
	Factory<sf::Vector2f, sf::Vector2f, float> box([this, scene](Agent& agent, sf::Vector2f pos, sf::Vector2f size, float angle){
		RectComponent* r = new RectComponent;
		r->r.setSize(size);
		r->r.setFillColor(sf::Color::Blue);
		r->setOrigin(size.x / 2, size.y / 2);
		
		agent.addComponent<Drawable>(r);
		agent.addComponent<Transformable>(r);
		
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = PhysicsConfig::pixelToMeter(pos);
		
		b2PolygonShape box;
		b2Vec2 s = PhysicsConfig::pixelToMeter({size.x / 2, size.y / 2});
		box.SetAsBox(s.x, s.y);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.3f;
		
		bodyDef.angle = angle;
		
		Physic p = scene->getWorld().CreateBody(&bodyDef);
		p->CreateFixture(&fixtureDef);
		
		agent.addTag<c6::ecs::tag::PhysicallyMoving>();
		agent.addComponent<Physic>(p);
	});
	
	Factory<sf::Vector2f, sf::Vector2f, float> player([this, scene](Agent& agent, sf::Vector2f pos, sf::Vector2f size, float angle){
		RectComponent* r = new RectComponent;
		r->r.setSize(size);
		r->r.setFillColor(sf::Color::Red);
		r->setOrigin(size.x / 2, size.y / 2);
		
		agent.addComponent<Drawable>(r);
		agent.addComponent<Transformable>(r);
		
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = PhysicsConfig::pixelToMeter(pos);
		bodyDef.allowSleep = true;
		bodyDef.awake = false;
		bodyDef.fixedRotation = true;
		
		b2PolygonShape box;
		b2Vec2 s = PhysicsConfig::pixelToMeter({size.x / 2, size.y / 2});
		box.SetAsBox(s.x, s.y);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.3f;
		
		bodyDef.angle = angle;
		
		Physic p = scene->getWorld().CreateBody(&bodyDef);
		p->CreateFixture(&fixtureDef);
		
		agent.addComponent<Physic>(p);
		
		agent.addTag<c6::ecs::tag::PhysicallyMoving>();
		agent.addTag<Player>();
	});
	
	scene->addTimeSystem(playerMove);
	scene->addTimeSystem(physics);
	scene->addRenderSystem(draw);
	
	scene->newAgent(ground, {500, 500}, {500, 50});
	
	for(int i = 0; i < 15; i++)
		scene->newAgent(box, {50 + i * 50.f, 0}, {50, 50}, 0.f);
	for(int i = 0; i < 10; i++)
		scene->newAgent(box, {50 + i * 60.f + 25, 100}, {50, 50}, b2_pi / (i + 1));
	scene->newAgent(player, {500, 250}, {50, 50}, 0.f);
	
	return scene;
}

void Game::init(){
	Framework::getRenderer().lock();
	Framework::getRenderer().get().create(sf::VideoMode(500, 500), "Plugins test");
	Framework::getInputHandler().registerWindow(&Framework::getRenderer().get());
	Framework::getRenderer().unlock();
	
	Framework::getResourceManager().loadFonts(std::string("../assets/fonts"));
	Framework::getResourceManager().loadTextures(std::string("../assets/textures"));
	Framework::getResourceManager().loadSounds(std::string("../assets/sounds"));
	
	c6::Console::useMessageType(c6::MessageType::Debug);
	c6::Console::useMessageType(c6::MessageType::Error);
	c6::Console::useMessageType(c6::MessageType::Info);
	c6::Console::useMessageType(c6::MessageType::Loading);
	
	RectComponent* r = new RectComponent;
	r->r.setSize({100, 100});
	c6::EntryPoint::addDefaultTemplate("rect", r);
	
	//loadPlugins(std::string("../mods/"));
	
	m_finiteStateMachine.add(scene1());
	Application::init();
}

Game::~Game(){
	Framework::destroyResourceManager();
	Framework::destroyInputHandler();
	Framework::destroySoundboard();
	Framework::getRenderer().lock();
	if(Framework::getRenderer().get().isOpen()){
		Framework::getRenderer().get().close();
	}
	Framework::getRenderer().unlock();
	Framework::destroyRenderer();
}
