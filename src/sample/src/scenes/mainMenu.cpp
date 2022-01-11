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
#include "sample/src/voxels/IsometricVoxels.hpp"
#include "dragAndDropTest.hpp"
#include <Core6/application.hpp>
#include <src/platformer.hpp>

MainMenu::MainMenu(c6::Application<ecsConfig>& app, c6::StateMachine& stateMachine) : Scene(app, stateMachine){
	dynamic_cast<Platformer&>(getApplication()).getTextButtonFactory()(
			getECS(),
			getWidgetRoot(),
			[&stateMachine, &app]{
				stateMachine.replace(new IsometricVoxels(app, stateMachine));
			},
			"Isometric Voxels",
			sf::Vector2f(0, 0)
	);
	dynamic_cast<Platformer&>(getApplication()).getTextButtonFactory()(
			getECS(),
			getWidgetRoot(),
			[&stateMachine, &app]{
				stateMachine.replace(new DragAndDropTest(app, stateMachine));
			},
			"Drag and Drop",
			sf::Vector2f(0, 50)
	);
	dynamic_cast<Platformer&>(getApplication()).getTextButtonFactory()(
			getECS(),
			getWidgetRoot(),
			[&app]{
				app.close();
			},
			"Exit",
			sf::Vector2f(0, 100)
	);
	
	getECS().refresh();
}