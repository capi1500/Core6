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

#ifndef CORE6_FRAME9_HPP
#define CORE6_FRAME9_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Core6/widgets/widgetAssetPack.hpp>

namespace c6{
	namespace widget{
		class Frame9 : public sf::Drawable{
			private:
				sf::Vector2u m_textureSizes[3];
				sf::Vector2u m_size;
				sf::Sprite m_sprites[3][3];
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			public:
				const sf::Vector2u& getSize() const;
				void setSize(const sf::Vector2u& size);
				
				void applyDef(const WidgetAssetPack::Frame9& def);
				
				Frame9() = default;
				Frame9(const WidgetAssetPack::Frame9& def);
				Frame9(const WidgetAssetPack::Frame9& def, const sf::Vector2u& size);
		};
	}
}

#endif //CORE6_FRAME9_HPP
