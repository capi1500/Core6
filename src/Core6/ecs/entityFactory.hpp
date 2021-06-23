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
		protected:
			virtual void spawn(const EntityComponentSystem<Config>& entityManager, EntityId id, const Args&... args) const;
			
			friend class EntityComponentSystem<Config>;
	};
	
	template<concepts::Config Config, class... Args>
	class SimpleEntityFactory{
		private:
			using Function = std::function<void(const EntityComponentSystem<Config>&, EntityId, const Args&...)>;
			Function function;
		protected:
			void spawn(const EntityComponentSystem<Config>& entityManager, EntityId id, const Args&... args) const final{
				function(entityManager, id, args...);
			}
		public:
			SimpleEntityFactory(const Function& function) : function(function){}
			SimpleEntityFactory(Function&& function) : function(std::forward<Function>(function)){}
	};
}

