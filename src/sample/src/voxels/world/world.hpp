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

#include <map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <Core6/base/listener/listener.hpp>
#include <Core6/base/updatable.hpp>
#include "sample/src/utils/util.hpp"
#include "sample/src/utils/rotation.hpp"
#include "chunk.hpp"

class World : public sf::Drawable, public c6::Listener<sf::Event>, public c6::Updatable{
	private:
		Rotation rotation;
		
		std::map<sf::Vector2i, Chunk, VectorCmp<int>> chunks;
		
		sf::Vector3i highlighted;
		bool highlightVisible[9] = {false, false, false, false, false, false, false, false, false};
		sf::Vertex highlight[9][2] = {
			{{{55, 0}}, {{0, 32}}},
			{{{55, 0}}, {{110, 32}}},
			{{{0, 32}}, {{55, 64}}},
			{{{110, 32}}, {{55, 64}}},
			{{{0, 32}}, {{0, 96}}},
			{{{55, 64}}, {{55, 128}}},
			{{{110, 32}}, {{110, 96}}},
			{{{0, 96}}, {{55, 128}}},
			{{{110, 96}}, {{55, 128}}}
		};
		
		[[nodiscard]] bool hasChunk(const sf::Vector2i& chunk) const;
		[[nodiscard]] bool hasCube(const sf::Vector3i& cube) const;
		static sf::Vector2i getCubesChunk(const sf::Vector3i& cube);
		
		[[nodiscard]] bool cubeVisible(const sf::Vector3i& cube) const;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		void rotateLeft();
		void rotateRight();
		
		void addChunk(const sf::Vector2i& coord);
		void removeChunk(const sf::Vector2i& coord);
		
		void update(const sf::Time& time) override;
		void onNotify(const sf::Event& event) noexcept override;
		
		sf::Vector3i getVisibleCubeAtPoint(const sf::Vector2f& point) const;
		
		[[nodiscard]] const Cube& getCube(const sf::Vector2i& chunk, const sf::Vector3i& coord) const;
		[[nodiscard]] const Cube& getCube(const sf::Vector3i& coord) const;
		void setCube(const Cube::Type& type, const sf::Vector2i& chunk, const sf::Vector3i& coord);
		void setCube(const Cube::Type& type, const sf::Vector3i& coord);
};
