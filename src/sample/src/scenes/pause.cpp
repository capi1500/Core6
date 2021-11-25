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

#include "pause.hpp"
#include "mainMenu.hpp"

Pause::Pause(c6::Application<ecsConfig>& application, c6::StateMachine& stateMachine) : Scene(application, stateMachine){

}

void Pause::onNotify(const sf::Event& event) noexcept{
	Scene::onNotify(event);
	if(event.type == sf::Event::KeyReleased){
		std::cout << "Pause onNotify()\n";
		if(event.key.code == sf::Keyboard::Escape)
			getStateMachine().pop();
		if(event.key.code == sf::Keyboard::Num1){
			getStateMachine().pop(2);
			getStateMachine().add(new MainMenu(getApplication(), getStateMachine()));
		}
	}
}
