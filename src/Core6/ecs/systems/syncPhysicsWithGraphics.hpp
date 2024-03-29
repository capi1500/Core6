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

#include "../config.hpp"
#include "../system.hpp"
#include "../../physicsConfig.hpp"

namespace c6{
	namespace signature{
		using SyncPhysicsWithGraphics = Signature<component::Transformable, component::Physic>;
	}
	namespace system{
		template<concepts::Config Config>
		auto syncPhysicsWithGraphics = System<Config, signature::SyncPhysicsWithGraphics, const PhysicsConfig&>(
				[](component::Transformable& transformable, component::Physic& physic, const PhysicsConfig& physicsConfig){
					transformable->setPosition(physicsConfig.meterToPixel(physic->GetPosition()));
					transformable->setRotation(180 * physic->GetAngle() / b2_pi);
				}
		);
	}
}