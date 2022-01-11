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

#include <cmath>
#include <Core6/framework.hpp>
#include "world.hpp"

void World::rotateLeft(){
	rotation = static_cast<Rotation>((rotation + 1) % 4);
	for(auto& c : chunks)
		c.second.setRotation(rotation);
}

void World::rotateRight(){
	rotation = static_cast<Rotation>((rotation + 3) % 4);
	for(auto& c : chunks)
		c.second.setRotation(rotation);
}

void World::addChunk(const sf::Vector2i& coord){
	Chunk& n = chunks[coord];
	for(int x = 0; x < 16; x++){
		for(int z = 0; z < 16; z++){
			for(int y = 0; y < 15 - std::min(x, z); y++)
				n.setCube(Cube::Dirt, x, y, z);
			n.setCube(Cube::Grass, x, 15 - std::min(x, z), z);
			for(int y = 15 - std::min(x, z) + 1; y < 16; y++)
				n.setCube(Cube::Empty, x, y, z);
		}
	}
	n.update();
}

void World::removeChunk(const sf::Vector2i& coord){
	chunks.erase(coord);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for(auto& c : chunks)
		target.draw(c.second, states);
	states.transform.translate(Chunk::mapCubeToPoint(highlighted, rotation));
	for(int i = 0; i < 9; i++){
		if(highlightVisible[i])
			target.draw(highlight[i], 2, sf::Lines, states);
	}
}

void World::onNotify(const sf::Event& event) noexcept{
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::Z)
			rotateLeft();
		else if(event.key.code == sf::Keyboard::X)
			rotateRight();
	}
	else if(event.type == sf::Event::MouseMoved){
		for(bool& i : highlightVisible)
			i = false;
		sf::Vector3i cube = getVisibleCubeAtPoint(c6::Framework::getRenderer()->mapPixelToCoords({event.mouseMove.x - 55, event.mouseMove.y}));
		
		if(hasCube(cube) && getCube(cube).getType() != Cube::Empty){
			for(bool& i : highlightVisible)
				i = true;
			
			sf::Vector3i xShift = sf::Vector3i(1, 0, 0) * (rotation == Rotation::North || rotation == Rotation::East ? 1 : -1);
			sf::Vector3i yShift = sf::Vector3i(0, 1, 0);
			sf::Vector3i zShift = sf::Vector3i(0, 0, 1) * (rotation == Rotation::North || rotation == Rotation::West ? 1 : -1);
			
			bool cubeLeft = cubeVisible(cube + xShift);
			bool cubeAbove = cubeVisible(cube + yShift);
			bool cubeRight = cubeVisible(cube + zShift);
			bool cubeInFront = cubeVisible(cube + xShift + zShift);
			bool cubeLeftAbove = cubeVisible(cube + xShift + yShift);
			bool cubeRightAbove = cubeVisible(cube + zShift + yShift);
			if(cubeLeft)
				highlightVisible[4] = highlightVisible[7] = false;
			if(cubeAbove)
				highlightVisible[0] = highlightVisible[1] = false;
			if(cubeRight)
				highlightVisible[6] = highlightVisible[8] = false;
			if(cubeLeft && cubeRight)
				highlightVisible[5] = false;
			if(cubeLeft && cubeAbove)
				highlightVisible[2] = false;
			if(cubeRight && cubeAbove)
				highlightVisible[3] = false;
			if(cubeInFront)
				highlightVisible[5] = highlightVisible[7] = highlightVisible[8] = false;
			if(cubeLeftAbove)
				highlightVisible[0] = highlightVisible[2] = highlightVisible[4] = false;
			if(cubeRightAbove)
				highlightVisible[1] = highlightVisible[3] = highlightVisible[6] = false;
			highlighted = cube;
		}
	}
}

sf::Vector3i World::getVisibleCubeAtPoint(const sf::Vector2f& point) const{
	sf::Vector3i xShift = sf::Vector3i(1, 0, 0) * (rotation == Rotation::North || rotation == Rotation::East ? 1 : -1);
	sf::Vector3i yShift = sf::Vector3i(0, 1, 0);
	sf::Vector3i zShift = sf::Vector3i(0, 0, 1) * (rotation == Rotation::North || rotation == Rotation::West ? 1 : -1);
	for(int y = 15; y >= 0; y--){
		sf::Vector3i cube = Chunk::mapPointToCubeAtLayer(point, y, rotation);
		if(hasCube(cube + yShift) && getCube(cube + yShift).getType() != Cube::Empty){
			cube += yShift;
			if(hasCube(cube + xShift) && getCube(cube + xShift).getType() != Cube::Empty && point.x <= Chunk::mapCubeToPoint(cube, rotation).x)
				cube += xShift;
			else if(hasCube(cube + zShift) && getCube(cube + zShift).getType() != Cube::Empty && point.x > Chunk::mapCubeToPoint(cube, rotation).x)
				cube += zShift;
		}
		else{
			if(hasCube(cube + xShift + yShift) && getCube(cube + xShift + yShift).getType() != Cube::Empty && point.x <= Chunk::mapCubeToPoint(cube, rotation).x)
				cube += xShift + yShift;
			else if(hasCube(cube + zShift + yShift) && getCube(cube + zShift + yShift).getType() != Cube::Empty && point.x > Chunk::mapCubeToPoint(cube, rotation).x)
				cube += zShift + yShift;
		}
		if(hasCube(cube) && getCube(cube).getType() != Cube::Empty)
			return cube;
	}
	return {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
}

void World::update(const sf::Time& time){

}

bool World::cubeVisible(const sf::Vector3i& cube) const{
	return hasCube(cube) && getCube(cube).getType() != Cube::Empty;
}

bool World::hasChunk(const sf::Vector2i& chunk) const{
	return chunks.contains(chunk);
}

bool World::hasCube(const sf::Vector3i& cube) const{
	return 0 <= cube.y && cube.y < 16 && hasChunk(getCubesChunk(cube));
}

sf::Vector2i World::getCubesChunk(const sf::Vector3i& cube){
	return {static_cast<int>(std::floor(static_cast<float>(cube.x) / 16.f)),
			static_cast<int>(std::floor(static_cast<float>(cube.z) / 16.f))};
}

const Cube& World::getCube(const sf::Vector2i& chunk, const sf::Vector3i& coord) const{
	return chunks.at(chunk).getCube(coord);
}

const Cube& World::getCube(const sf::Vector3i& coord) const{
	return getCube(sf::Vector2i(std::floor(coord.x / 16), std::floor(coord.z / 16)),
				   sf::Vector3i(coord.x % 16, coord.y, coord.z % 16));
}

void World::setCube(const Cube::Type& type, const sf::Vector2i& chunk, const sf::Vector3i& coord){
	chunks[chunk].setCube(type, coord);
}


void World::setCube(const Cube::Type& type, const sf::Vector3i& coord){
	setCube(type,
			sf::Vector2i(std::floor(coord.x / 16), std::floor(coord.z / 16)),
			sf::Vector3i(coord.x % 16, coord.y, coord.z % 16));
}

