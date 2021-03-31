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

#ifndef CORE6_INIT_HPP
#define CORE6_INIT_HPP

#include <Core6/config.hpp>
#include <Core6/agent/components.hpp>
#include <Core6/agent/agent.hpp>
#include <Core6/agent/factory.hpp>
#include <Core6/plugin/entryPoint.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Core6/scene.hpp>

// ECS Config
using Drawable = c6::ecs::component::Drawable;
using Transformable = c6::ecs::component::Transformable;
using Physic = c6::ecs::component::Physic;
using CompList = c6::ecs::component::StdComponents;

struct Rect{};
struct Player{};
using TagList = MPL::Concat<c6::TagList<Rect, Player>, c6::ecs::tag::StdTags>;

using MovableRectSig = c6::Signature<Rect, Transformable>;
using PlayerMoveSig = c6::Signature<Physic, Player>;
using SignatureList = MPL::Concat<c6::SignatureList<MovableRectSig, PlayerMoveSig>, c6::ecs::signature::StdSignatures>;

using SysytemTimeList = MPL::TypeList<MovableRectSig, PlayerMoveSig, c6::ecs::signature::PhysicsTransformableSync>;
using SysytemRenderList = MPL::TypeList<c6::ecs::signature::Draw>;

using ECSConfig = c6::ECSConfig<CompList,
								TagList,
								SignatureList,
								SysytemTimeList,
								SysytemRenderList>;

// Physics Config
using PhysicsConfig = c6::PhysicsConfig;

// Main Config
using Config = c6::Config<ECSConfig,
						  c6::ResourceManager,
						  c6::InputHandler,
						  c6::Renderer,
						  c6::Soundboard>;

// Common types aliases
using Scene = c6::Scene<Config>;
using Agent = c6::Agent<Config>;
template<typename ...TArgs>
using Factory = c6::Factory<Config, TArgs...>;

using Move = c6::System<Config, MovableRectSig, const sf::Time&>;
using MovePlayer = c6::System<Config, PlayerMoveSig, const sf::Time&>;

extern c6::ecs::system::Draw<Config> draw;
extern Move move;
extern MovePlayer playerMove;
extern c6::ecs::system::PhysicsTransformableSync<Config> physics;

#endif //CORE6_INIT_HPP
