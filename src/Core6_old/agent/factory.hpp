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

#ifndef CORE6_FACTORY_HPP
#define CORE6_FACTORY_HPP

#include <functional>
#include "agent.hpp"

namespace c6{
	template<concepts::Config TConfig, typename ...TArgs>
	class Factory{
			using ECSConfig = typename TConfig::ECSConfig;
			using Agent = Agent<TConfig>;
			using AgentGroup = AgentGroup<TConfig>;
			using FunctionType = std::function<void(Agent&, TArgs...)>;
		private:
			FunctionType init;
		public:
			Factory(const FunctionType& spawn) : init(spawn) {};
			
			friend AgentGroup;
	};
}

#endif //CORE6_FACTORY_HPP