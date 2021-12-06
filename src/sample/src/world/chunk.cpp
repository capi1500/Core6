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

#include "chunk.hpp"

c6::IsometricGrid const Chunk::grid = {{  0,  0},
									     {-55, 32},
                                         { 55, 32}};
sf::Vector2f const Chunk::shift = {-15 * 55, -15 * 64};

Chunk::Chunk(){
	for(auto& i : renderer)
		i.create(16 * 110, 32 * 64);
}

void Chunk::render(){
	for(auto& i : renderer)
		i.clear();
	for(int y = 0; y < 16; y++){
		for(int z = 0; z < 16; z++){
			for(int x = 0; x < 16; x++){
				if(cube[x][y][z].getType() != Cube::Empty){
					sprite.setTexture(cube[x][y][z].getTexture(), true);
					sprite.setPosition(mapCubeToPoint(x, y, z, Rotation::North));
					renderer[0].draw(sprite);
				}
			}
		}
		for(int z = 15; z >= 0; z--){
			for(int x = 0; x < 16; x++){
				if(cube[x][y][z].getType() != Cube::Empty){
					sprite.setTexture(cube[x][y][z].getTexture(), true);
					sprite.setPosition(mapCubeToPoint(x, y, z, Rotation::East));
					renderer[1].draw(sprite);
				}
			}
		}
		for(int z = 15; z >= 0; z--){
			for(int x = 15; x >= 0; x--){
				if(cube[x][y][z].getType() != Cube::Empty){
					sprite.setTexture(cube[x][y][z].getTexture(), true);
					sprite.setPosition(mapCubeToPoint(x, y, z, Rotation::South));
					renderer[2].draw(sprite);
				}
			}
		}
		for(int z = 0; z < 16; z++){
			for(int x = 15; x >= 0; x--){
				if(cube[x][y][z].getType() != Cube::Empty){
					sprite.setTexture(cube[x][y][z].getTexture(), true);
					sprite.setPosition(mapCubeToPoint(x, y, z, Rotation::West));
					renderer[3].draw(sprite);
				}
			}
		}
	}
	for(auto& i : renderer)
		i.display();
	sprite.setTexture(renderer[rotation].getTexture(), true);
	sprite.setPosition(0, 0);
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite, states);
}

const Cube& Chunk::getCube(int x, int y, int z) const{
	return getCube({x, y, z});
}

const Cube& Chunk::getCube(const sf::Vector3i& coord) const{
	return cube[coord.x][coord.y][coord.z];
}

void Chunk::setCube(const Cube::Type& cube, int x, int y, int z){
	setCube(cube, {x, y, z});
}

void Chunk::setCube(const Cube::Type& cube, const sf::Vector3i& coord){
	this->cube[coord.x][coord.y][coord.z] = Cube(cube);
}

void Chunk::update(){
	render();
}

void Chunk::setRotation(Rotation rotation){
	this->rotation = rotation;
	sprite.setTexture(renderer[rotation].getTexture(), true);
}

sf::Vector2f Chunk::mapCubeToPoint(const sf::Vector3i& coord, const Rotation& rotation){
	return grid.mapCoordinateToPoint(
			{((rotation == Rotation::West || rotation == Rotation::South) ? 15 - coord.x : coord.x) - coord.y,
			            ((rotation == Rotation::East || rotation == Rotation::South) ? 15 - coord.z : coord.z) - coord.y}
			) - shift;
}

sf::Vector2f Chunk::mapCubeToPoint(int x, int y, int z, const Rotation& rotation){
	return mapCubeToPoint({x, y, z}, rotation);
}

sf::Vector3i Chunk::mapPointToCubeAtLayer(const sf::Vector2f& point, int y, const Rotation& rotation){
	sf::Vector2i coord = Chunk::grid.mapPointToCoordinate(point + shift);
	sf::Vector3i cube;
	if(rotation == Rotation::West || rotation == Rotation::South)
		cube.x = 15 - y - coord.x;
	else
		cube.x = coord.x + y;
	cube.y = y;
	if(rotation == Rotation::East || rotation == Rotation::South)
		cube.z = 15 - y - coord.y;
	else
		cube.z = coord.y + y;
	return cube;
}

