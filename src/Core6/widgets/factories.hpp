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
#include "widgets.hpp"
#include <Core6/config.hpp>
#include <Core6/agent/factory.hpp>
#include <Core6/framework.hpp>

namespace c6{
	namespace widget{
		namespace factory{
			namespace helper{
				auto createTextComponent(WidgetAssetPack::TextDef def){
					component::Text text;
					text.setStyle(def.style);
					text.setCharacterSize(def.characterSize);
					text.setLineSpacing(def.lineSpacing);
					text.setLetterSpacing(def.letterSpacing);
					text.setOutlineThickness(def.thickness);
					text.setFillColor(def.fillColor);
					text.setOutlineColor(def.outlineColor);
					return text;
				}
				
				auto createFrame9Component(WidgetAssetPack::FrameDef def, std::function<const sf::Texture&(const std::string&)> get){
					component::Frame9Component f9;
					for(int i = 0; i < 3; i++){
						for(int j = 0; j < 3; j++){
							f9.regular[i][j].setTexture(get(def.regular.part[i][j]));
							f9.disabled[i][j].setTexture(get(def.disabled.part[i][j]));
							f9.highlighted[i][j].setTexture(get(def.highlighted.part[i][j]));
						}
					}
					return f9;
				}
			}
			
			template<concepts::Config Config, class... AddArgs>
			using WidgetFactory = Factory<Config,
										 const WidgetAssetPack&,
										 const sf::Vector2f&,
										 const sf::Vector2f&,
										 AddArgs...>;
			
			template<concepts::Config Config>
			auto labelFactory = WidgetFactory<Config, const std::string&>([](Agent<Config>& agent, const WidgetAssetPack& assetPack, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& label){
				typename Config::ResourceManager& assets = Framework<Config>::getResourceManager();
				
				agent.template addComponent<component::Frame9Component>(helper::createFrame9Component(assetPack.frame, [&assets](const std::string& name){return assets.getTexture(name);}));
				
				auto text = helper::createTextComponent(assetPack.regular);
				text.setFont(assets.getFont(assetPack.font));
				text.setString(label);
				
				agent.template addComponent<component::Text>(text);
			});
		}
	}
}

#endif //CORE6_FACTORIES_HPP
