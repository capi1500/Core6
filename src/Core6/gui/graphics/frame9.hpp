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
#include "widgetGraphics.hpp"

namespace c6::widgets{
	class Frame9 : public WidgetGraphics{
		public:
			class AssetPack{
				private:
					std::string textureName[3][3];
				public:
					[[nodiscard]]
					std::string* operator [] (size_t id);
					[[nodiscard]]
					const std::string* operator [] (size_t id) const;
			};
		private:
			sf::Sprite sprite;
			sf::Texture texture;
			const AssetPack* assetPack;
		protected:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		public:
			void resize(sf::Vector2u size);
			void setAssetPack(const AssetPack& newAssetPack);
			
			sf::FloatRect getLocalBounds() const override;
			sf::FloatRect getGlobalBounds() const override;
			
			Frame9(const AssetPack& newAssetPack, const sf::Vector2u& size);
			explicit Frame9(const AssetPack& newAssetPack);
			Frame9();
	};
}

