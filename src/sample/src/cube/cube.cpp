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
#include "cube.hpp"

Cube::Cube(Cube::Type type) : type(type){
	if(type == Grass)
		texture = &c6::Framework::getResourceManager()->getTexture("../assets/textures/cubes/PNG/Voxel tiles/voxelTile_55.png");
	else if(type == GrassFull)
		texture = &c6::Framework::getResourceManager()->getTexture("../assets/textures/cubes/PNG/Voxel tiles/voxelTile_54.png");
	else if(type == Dirt)
		texture = &c6::Framework::getResourceManager()->getTexture("../assets/textures/cubes/PNG/Voxel tiles/voxelTile_53.png");
}

const sf::Texture& Cube::getTexture() const{
	return *texture;
}

Cube::Type Cube::getType() const{
	return type;
}
