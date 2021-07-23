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

#include <Core6/widgets/widgetAssetPack.hpp>
#include "widgetScene.hpp"

WidgetScene::WidgetScene(c6::StateMachine& stateMachine) : Scene(stateMachine){
	c6::Framework::getResourceManager()->loadTextures("../assets/textures/rgb/");
	
	c6::WidgetAssetPack::Frame9 frame9assetPack;
	frame9assetPack[0][0] = "../assets/textures/rgb/white.png";
	frame9assetPack[0][1] = "../assets/textures/rgb/green.png";
	frame9assetPack[0][2] = "../assets/textures/rgb/black.png";
	
	frame9assetPack[1][0] = "../assets/textures/rgb/green.png";
	frame9assetPack[1][1] = "../assets/textures/rgb/blue.png";
	frame9assetPack[1][2] = "../assets/textures/rgb/red.png";
	
	frame9assetPack[2][0] = "../assets/textures/rgb/magenta.png";
	frame9assetPack[2][1] = "../assets/textures/rgb/red.png";
	frame9assetPack[2][2] = "../assets/textures/rgb/white.png";
	
	std::shared_ptr<c6::Frame9> frame9 = std::make_shared<c6::Frame9>(frame9assetPack);
	frame9->resize({2, 1});
	frame9->move(300, 300);
	
	auto frame = getECS().add();
	getECS().addComponent<c6::component::Drawable>(frame, frame9);
	getECS().addComponent<c6::component::Transformable>(frame, frame9);
	getECS().refresh();
}
