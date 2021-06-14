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

#include "frame9.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <Core6/systems/console.hpp>

namespace c6{
	namespace widget{
		void Frame9::draw(sf::RenderTarget& target, sf::RenderStates states) const{
			auto drawRow = [&target, &states, this](unsigned i){
				target.draw(*m_sprites[i][0], states);
				states.transform.translate(m_textureSizes[0].x, 0);
				for(unsigned j = 0; j < m_size.x; j++){
					target.draw(*m_sprites[i][1], states);
					states.transform.translate(m_textureSizes[1].x, 0);
				}
				target.draw(*m_sprites[i][2], states);
				states.transform.translate(-static_cast<int>(m_textureSizes[1].x * m_size.x) - static_cast<int>(m_textureSizes[0].x), m_textureSizes[i].y);
			};
			
			drawRow(0);
			for(unsigned i = 0; i < m_size.y; i++)
				drawRow(1);
			drawRow(2);
		}
		
		void Frame9::applyDef(WidgetAssetPack::Frame9& def){
			for(unsigned i = 0; i < 3; i++){
				for(unsigned j = 0; j < 3; j++){
					m_sprites[i][j] = &def.part[i][j];
				}
			}
			for(unsigned i = 0; i < 3; i++){
				m_textureSizes[i].x = def.part[0][i].getTexture()->getSize().x;
				m_textureSizes[i].y = def.part[i][0].getTexture()->getSize().y;
			}
		}
		
		Frame9::Frame9(WidgetAssetPack::Frame9& def){
			applyDef(def);
		}
		
		Frame9::Frame9(WidgetAssetPack::Frame9& def, const sf::Vector2u& size){
			m_size = size;
			applyDef(def);
		}
		
		const sf::Vector2u& Frame9::getSize() const{
			return m_size;
		}
		
		void Frame9::setSize(const sf::Vector2u& size){
			m_size = size;
		}
	}
}
