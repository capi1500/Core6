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
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector3.hpp>
#include <Core6/grid/ortographicGrid.hpp>
#include <src/utils/rotation.hpp>
#include <sample/src/voxels/cube/cube.hpp>

class Chunk : public sf::Drawable{
	public:
		static const c6::OrtographicGrid grid;
		static const sf::Vector2f shift;
		static sf::Vector2f mapCubeToPoint(const sf::Vector3i& coord, const Rotation& rotation);
		static sf::Vector2f mapCubeToPoint(int x, int y, int z, const Rotation& rotation);
		static sf::Vector3i mapPointToCubeAtLayer(const sf::Vector2f& point, int y, const Rotation& rotation);
	private:
		sf::RenderTexture renderer[4];
		sf::Sprite sprite;
		
		Rotation rotation = North;
		
		Cube cube[16][16][16];
		void render();
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Chunk();
		
		const Cube& getCube(int x, int y, int z) const;
		const Cube& getCube(const sf::Vector3i& coord) const;
		void setCube(const Cube::Type& cube, int x, int y, int z);
		void setCube(const Cube::Type& cube, const sf::Vector3i& coord);
		
		void setRotation(Rotation rotation);
		
		void update();
};
