/**
 * Core6
 * Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#ifndef CORE6_GAME_HPP
#define CORE6_GAME_HPP

#include <Core6/application.hpp>
#include <Core6/agent/ecsConfig.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Core6/agent/agentGroup.hpp>

using Rect = sf::RectangleShape;
using CompList = c6::ComponentList<Rect>;

struct Movable{};
using TagList = c6::TagList<Movable>;

using RectSig = c6::Signature<Rect>;
using MovableRectSig = c6::Signature<Rect, Movable>;
using SignatureList = c6::SignatureList<RectSig, MovableRectSig>;

using Config = c6::ECSConfig<CompList, TagList, SignatureList>;
using Manager = c6::AgentGroup<Config>;
using Agent = c6::Agent<Config>;

using Draw = c6::System<Config, RectSig>;
using Move = c6::System<Config, MovableRectSig>;

class Game : public c6::Application{
	private:
		c6::Scene* scene1();
		c6::Scene* scene2();
		Manager mgr;
		Draw draw;
		Move move;
	public:
		void run() override;
		void init() override;
		
		Game();
};

#endif //CORE6_GAME_HPP
