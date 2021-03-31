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

#include "label.hpp"

namespace c6{
	namespace widget{
		namespace component{
			void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const{
				Graphic::draw(target, states);
				states.transform.combine(getTransform());
				target.draw(text, states);
			}
			
			void Label::applyFrameDef(const WidgetAssetPack::FrameDef& def){
				regular.applyDef(def.regular);
				highlighted.applyDef(def.highlighted);
				disabled.applyDef(def.disabled);
			}
			
			void Label::applyTextDef(const WidgetAssetPack::TextDef& def){
				text.setStyle(def.style);
				text.setCharacterSize(def.characterSize);
				text.setLineSpacing(def.lineSpacing);
				text.setLetterSpacing(def.letterSpacing);
				text.setOutlineThickness(def.thickness);
				text.setFillColor(def.fillColor);
				text.setOutlineColor(def.outlineColor);
			}
			
			void Label::setSize(const sf::Vector2u& size){
				regular.setSize(size);
				highlighted.setSize(size);
				disabled.setSize(size);
			}
			
			const sf::Vector2u& Label::getSize() const{
				return regular.getSize();
			}
			
			Label::Label(const WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef){
				applyFrameDef(frameDef);
				applyTextDef(textDef);
			}
			
			Label::Label(const WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const sf::Vector2u& size){
				applyFrameDef(frameDef);
				applyTextDef(textDef);
				setSize(size);
			}
			
			Label::Label(const WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const std::string& string){
				applyFrameDef(frameDef);
				applyTextDef(textDef);
				text.setString(string);
			}
			
			Label::Label(const WidgetAssetPack::FrameDef& frameDef, const WidgetAssetPack::TextDef& textDef, const sf::Vector2u& size, const std::string& string){
				applyFrameDef(frameDef);
				applyTextDef(textDef);
				setSize(size);
				text.setString(string);
			}
		}
	}
}
