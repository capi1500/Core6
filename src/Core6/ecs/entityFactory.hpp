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

#include "config.hpp"

namespace c6{
	template<concepts::Config Config>
	class EntityComponentSystem;
	
	template<concepts::Config Config, class... Args>
	class EntityFactory{
			using ECS = EntityComponentSystem<Config>;
		public:
			using EntityId = typename ECS::EntityId;
		private:
			using Function = std::function<void(ECS&, EntityId, Args...)>;
			
			Function function;
		protected:
			void spawn(ECS& entityManager, EntityId id, Args... args) const{
				function(entityManager, id, args...);
			}
			
			friend class EntityComponentSystem<Config>;
		public:
			explicit EntityFactory(const Function& function) : function(function){}
			explicit EntityFactory(Function&& function) : function(std::forward<Function>(function)){}
	};
}

