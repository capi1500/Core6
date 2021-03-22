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

#ifndef CORE6_CONFIG_HPP
#define CORE6_CONFIG_HPP

#include <type_traits>
#include <Core6/systems/resourceManager.hpp>
#include <Core6/systems/renderer.hpp>
#include <Core6/systems/inputHandler.hpp>
#include <Core6/systems/soundboard.hpp>
#include <Core6/agent/ecsConfig.hpp>
#include "physicsConfig.hpp"

namespace c6{
	template<concepts::ECSConfig TECSConfig,
	         concepts::ResourceManager TResourceManager,
			 concepts::InputHandler TInputHandler,
			 concepts::Renderer TRenderer,
			 concepts::Soundboard TSoundboard>
	struct Config{
		using ECSConfig = TECSConfig;
		using PhysicsConfig = PhysicsConfig;
		using ResourceManager = TResourceManager;
		using InputHandler = TInputHandler;
		using Renderer = TRenderer;
		using Soundboard = TSoundboard;
	};
	
	namespace concepts{
		template<class T> concept Config = requires{
			concepts::ECSConfig<typename T::ECSConfig>;
			concepts::PhysicsConfig<typename T::PhysicsConfig>;
			concepts::ResourceManager<typename T::ResourceManager>;
			concepts::InputHandler<typename T::InputHandler>;
			concepts::Renderer<typename T::Renderer>;
			concepts::Soundboard<typename T::Soundboard>;
		};
	}
}

#endif //CORE6_CONFIG_HPP
