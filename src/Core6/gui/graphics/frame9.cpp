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

namespace c6::widgets{
	/*
	void Frame9::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		states.transform.combine(getTransform());
		target.draw(sprite, states);
	}
	
	void Frame9::resize(sf::Vector2u rect){
		auto getTexture = [this](size_t i, size_t j) -> const sf::Texture&{
			return Framework::getResourceManager()->getTexture((*assetPack)[i][j]);
		};
		
		sf::RenderTexture renderTexture;
		renderTexture.create(
				getTexture(0, 0).getSize().x + getTexture(0, 1).getSize().x * rect.x + getTexture(0, 2).getSize().x,
				getTexture(0, 0).getSize().y + getTexture(1, 0).getSize().y * rect.y + getTexture(2, 0).getSize().y
		);
		renderTexture.clear(sf::Color::Transparent);
		
		sf::RenderStates renderStates;
		sf::Sprite tmp;
		
		auto drawRow = [&renderStates, &tmp, &rect, &renderTexture, &getTexture, this](int row){
			float deltaX = 0;
			tmp.setTexture(getTexture(row, 0));
			renderTexture.draw(tmp, renderStates);
			deltaX += tmp.getTexture()->getSize().x;
			renderStates.transform.translate(tmp.getTexture()->getSize().x, 0);
			
			tmp.setTexture(getTexture(row, 1));
			for(size_t i = 0; i < rect.x; i++){
				renderTexture.draw(tmp, renderStates);
				deltaX += tmp.getTexture()->getSize().x;
				renderStates.transform.translate(tmp.getTexture()->getSize().x, 0);
			}
			
			tmp.setTexture(getTexture(row, 2));
			renderTexture.draw(tmp, renderStates);
			renderStates.transform.translate(-deltaX, tmp.getTexture()->getSize().y);
		};
		
		drawRow(0);
		for(size_t i = 0; i < rect.y; i++)
			drawRow(1);
		drawRow(2);
		
		renderTexture.display();
		
		texture.create(renderTexture.getSize().x, renderTexture.getSize().y);
		texture.update(renderTexture.getTexture());
		sprite.setTexture(texture, true);
	}
	
	void Frame9::setAssetPack(const AssetPack& newAssetPack){
		assetPack = &newAssetPack;
	}
	
	sf::FloatRect Frame9::getLocalBounds() const{
		return sprite.getLocalBounds();
	}
	
	sf::FloatRect Frame9::getGlobalBounds() const{
		return getTransform().transformRect(sprite.getGlobalBounds());
	}
	
	Frame9::Frame9(const AssetPack& assetPack, const sf::Vector2u& rect) : assetPack(nullptr){
		setAssetPack(assetPack);
		resize(rect);
	}
	
	Frame9::Frame9(const Frame9::AssetPack& assetPack){
		setAssetPack(assetPack);
	}
	
	Frame9::Frame9() : assetPack(nullptr){
	
	}*/
}