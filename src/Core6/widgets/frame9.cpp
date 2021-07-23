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

#include <SFML/Graphics/RenderTexture.hpp>
#include <Core6/framework.hpp>
#include "frame9.hpp"

namespace c6{
	void Frame9::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		states.transform.combine(getTransform());
		target.draw(sprite, states);
	}
	
	void Frame9::resize(sf::Vector2u size){
		auto getTexture = [this](size_t i, size_t j) -> const sf::Texture&{
			return Framework::getResourceManager()->getTexture((*assetPack)[i][j]);
		};
		
		sf::RenderTexture renderTexture;
		renderTexture.create(
				getTexture(0, 0).getSize().x + getTexture(0, 1).getSize().x * size.x + getTexture(0, 2).getSize().x,
				getTexture(0, 0).getSize().y + getTexture(1, 0).getSize().y * size.y + getTexture(2, 0).getSize().y
		);
		renderTexture.clear(sf::Color::Transparent);
		
		sf::RenderStates renderStates;
		sf::Sprite tmp;
		
		auto drawRow = [&renderStates, &tmp, &size, &renderTexture, &getTexture, this](int row){
			float deltaX = 0;
			tmp.setTexture(getTexture(row, 0));
			renderTexture.draw(tmp, renderStates);
			deltaX += tmp.getTexture()->getSize().x;
			renderStates.transform.translate(tmp.getTexture()->getSize().x, 0);
			
			tmp.setTexture(getTexture(row, 1));
			for(size_t i = 0; i < size.x; i++){
				renderTexture.draw(tmp, renderStates);
				deltaX += tmp.getTexture()->getSize().x;
				renderStates.transform.translate(tmp.getTexture()->getSize().x, 0);
			}
			
			tmp.setTexture(getTexture(row, 2));
			renderTexture.draw(tmp, renderStates);
			renderStates.transform.translate(-deltaX, tmp.getTexture()->getSize().y);
		};
		
		drawRow(0);
		for(size_t i = 0; i < size.y; i++)
			drawRow(1);
		drawRow(2);
		
		renderTexture.display();
		
		texture.create(renderTexture.getSize().x, renderTexture.getSize().y);
		texture.update(renderTexture.getTexture());
		sprite.setTexture(texture, true);
	}
	
	void Frame9::setAssetPack(const WidgetAssetPack::Frame9& newAssetPack){
		assetPack = &newAssetPack;
	}
	
	void Frame9::setAssetPack(const WidgetAssetPack::Frame9& newAssetPack, const sf::Vector2u& size){
		setAssetPack(newAssetPack);
		resize(size);
	}
	
	Frame9::Frame9(const c6::WidgetAssetPack::Frame9& assetPack, const sf::Vector2u& size) : assetPack(nullptr){
		setAssetPack(assetPack, size);
	}
	
	Frame9::Frame9(const WidgetAssetPack::Frame9& assetPack) : assetPack(nullptr){
		setAssetPack(assetPack, {0, 0});
	}
	
	Frame9::Frame9() : assetPack(nullptr){
	
	}
}