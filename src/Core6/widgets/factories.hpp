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

#ifndef CORE6_FACTORIES_HPP
#define CORE6_FACTORIES_HPP

#include "widgetAssetPack.hpp"
#include <Core6/config.hpp>
#include <Core6/agent/factory.hpp>
#include <Core6/framework.hpp>
#include <Core6/widgets/components/label.hpp>
#include <Core6/agent/components.hpp>

namespace c6{
	namespace widget{
		namespace factory{
			template<concepts::Config Config, class... AddArgs>
			using WidgetFactory = Factory<Config,
										 const WidgetAssetPack&,
										 const sf::Vector2f&,
										 const sf::Vector2u&,
										 AddArgs...>;
			
			template<concepts::Config Config>
			auto labelFactory = WidgetFactory<Config, const std::string&>([](Agent<Config>& agent, const WidgetAssetPack& assetPack, const sf::Vector2f& position, const sf::Vector2u& size, const std::string& string){
				component::Label* label = new component::Label();
				label->applyFrameDef(assetPack.frame);
				label->applyTextDef(assetPack.regular);
				label->setSize(size);
				label->setPosition(position);
				label->text.setString(string);
				agent.template addComponent<ecs::component::Drawable>(label);
				agent.template addComponent<ecs::component::Transformable>(label);
			});
		}
	}
}

#endif //CORE6_FACTORIES_HPP
