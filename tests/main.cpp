#include <Core6/framework.hpp>
#include <SFML/Graphics.hpp>
#include <Core6/systems/console.hpp>
#include <Core6/scene.hpp>
#include <Core6/signal/core_signal/coreSignal.hpp>
#include <Core6/agent/agent.hpp>
#include <Core6/agent/graphicComponent.hpp>
#include <Core6/agent/inputComponent.hpp>
#include <iostream>
#include <thread>
#include <Core6/utils/commonFunctions.hpp>

// TODO finish commenting code (systems directory and up)

class Graphic : public c6::GraphicComponent{
	private:
		sf::RectangleShape m_rect;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
			states.transform.combine(getTransform());
			target.draw(m_rect, states);
		}
	
	public:
		sf::RectangleShape& getRect(){
			return m_rect;
		}
		
		Graphic(const sf::Vector2f& pos = {0, 0}){
			m_rect.setSize(sf::Vector2f(100, 100));
			m_rect.setFillColor(sf::Color::Red);
			m_rect.setPosition(pos);
		}
};

class Logic : public c6::LogicComponent{
	private:
		Graphic* m_graphic1;
		
		int m_color;
		int m_speed;
	public:
		int getColor() const{
			return m_color;
		}
		
		void setColor(int color){
			m_color = color;
		}
		
		void update(const sf::Time& time) override{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				m_graphic1->move(-m_speed * time.asSeconds(), 0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				m_graphic1->move(0, m_speed * time.asSeconds());
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				m_graphic1->move(m_speed * time.asSeconds(), 0);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				m_graphic1->move(0, -m_speed * time.asSeconds());
			if(m_color != -1){
				if(m_color == 1)
					m_graphic1->getRect().setFillColor(sf::Color::Red);
				else if(m_color == 2)
					m_graphic1->getRect().setFillColor(sf::Color::Green);
				else if(m_color == 3)
					m_graphic1->getRect().setFillColor(sf::Color::Blue);
				m_color = -1;
			}
		}
		
		void registerGraphic(c6::GraphicComponent* graphic) override{
			LogicComponent::registerGraphic(graphic);
			m_graphic1 = dynamic_cast<Graphic*>(graphic);
		}
		
		Logic(){
			m_color = -1;
			m_speed = 500;
		}
};

class Input : public c6::InputComponent{
	private:
		Logic* m_logic1;
	public:
		void onSignal(const sf::Event& signal) override{
			if(signal.type == sf::Event::KeyPressed){
				if(signal.key.code == sf::Keyboard::Num1)
					m_logic1->setColor(1);
				else if(signal.key.code == sf::Keyboard::Num2)
					m_logic1->setColor(2);
				else if(signal.key.code == sf::Keyboard::Num3)
					m_logic1->setColor(3);
			}
		}
		
		void registerLogic(c6::LogicComponent* logic) override{
			InputComponent::registerLogic(logic);
			m_logic1 = dynamic_cast<Logic*>(logic);
		}
		
		Input(){
			c6::Framework::getInput()->add(this);
		}
};

int main(){
	/*auto addTexture [&] (c6::AssetManager* assets, const std::string& path){
		sf::Texture texture;
		if(texture.loadFromFile(filename)){
			assets->texture.add(texture, id);
		}
	}
	
	auto loadTextures = [] (c6::AssetManager* assets, c6::Path path){
		auto texture = [&assets] (const std::string& filename){
			auto id = c6::hash(filename);
			
		};
		path.execute(texture, ".png", true);
		std::cout << "Loaded\n";
	};*/
	c6::Framework::registerRenderer(new c6::Renderer);
	c6::Framework::registerAssetManager(new c6::AssetManager);
	c6::Framework::registerInput(new c6::InputHandler);
	c6::Framework::registerCoreSignal(new c6::Signal<c6::CoreSignal>);
	c6::Framework::registerMesage(new c6::Signal<c6::Message>);
	
	c6::Framework::getRenderer()->lock();
	c6::Framework::getRenderer()->get().create(sf::VideoMode(500, 500), "LoaderTest");
	c6::Framework::getInput()->registerWindow(&c6::Framework::getRenderer()->get());
	c6::Framework::getRenderer()->unlock();
	
	bool active = true;
	
	c6::Framework::getCoreSignal()->add(new c6::Listener<c6::CoreSignal>(
			[&](const c6::CoreSignal& signal){
				if(signal.type == c6::CoreSignal::Close){
					std::cout << "event\n";
					active = false;
				}
			}
	), true);
	
	c6::Framework::getLoader();
	
	c6::Console console;
	console.useMessageType(c6::MessageType::Debug);
	console.useMessageType(c6::MessageType::Error);
	console.useMessageType(c6::MessageType::Info);
	
	c6::Scene scene;
	scene.setIsActive(true);
	
	c6::Factory factory(Graphic({200, 200}), nullptr, Input(), Logic());
	scene.addAgent(factory);
	factory.getGraphic().move(-200, -200);
	scene.addAgent(factory);
	
	sf::Clock clock;
	sf::Time time;
	
	while(active){
		time = clock.restart();
		
		c6::Framework::getInput()->handleInput();
		c6::Framework::getCoreSignal()->processEvents();
		
		scene.update(time);
		
		scene.draw();
	}
}