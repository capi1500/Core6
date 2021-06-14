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

#ifndef CORE6_LABEL_HPP
#define CORE6_LABEL_HPP

#include "graphic.hpp"

namespace c6{
	namespace widget{
		namespace component{
			class Label : public Graphic{
				protected:
					void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				public:
					Frame9 regular;
					Frame9 disabled;
					Frame9 highlighted;
					sf::Text text;
					// TODO Write other widgets too
					// TODO Then write some examples of widgets
					
					void applyFrameDef(WidgetAssetPack::FrameDef& def);
					void applyTextDef(const WidgetAssetPack::TextDef& def);
					void setSize(const sf::Vector2u& size);
					const sf::Vector2u& getSize() const;
					
					Label();
					Label(WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef);
					Label(WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const sf::Vector2u& size);
					Label(WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const std::string& string);
					Label(WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const sf::Vector2u& size, const std::string& string);
			};
		}
		
		
	}
}

#endif //CORE6_LABEL_HPP
