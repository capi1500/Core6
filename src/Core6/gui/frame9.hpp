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

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "widgetAssetPack.hpp"

namespace c6{
	class Frame9 : public sf::Drawable, public sf::Transformable{
		private:
			sf::Sprite sprite;
			sf::Texture texture;
			const WidgetAssetPack::Frame9* assetPack;
		protected:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		public:
			void resize(sf::Vector2u size);
			void setAssetPack(const WidgetAssetPack::Frame9& newAssetPack);
			void setAssetPack(const WidgetAssetPack::Frame9& newAssetPack, const sf::Vector2u& size);
			
			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;
			
			Frame9(const WidgetAssetPack::Frame9& newAssetPack, const sf::Vector2u& size);
			explicit Frame9(const WidgetAssetPack::Frame9& newAssetPack);
			Frame9();
	};
}

