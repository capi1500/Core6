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

#include <cmath>
#include "spriteAnimation.hpp"

namespace c6{
	
	SpriteAnimation::SpriteAnimation() noexcept{
		setIndefinite(true);
	}
	
	SpriteAnimation::SpriteAnimation(sf::Sprite* sprite) noexcept : SpriteAnimation(){
		bindSprite(sprite);
	}
	
	SpriteAnimation::Frame::Frame(const sf::Texture& texture, sf::IntRect rect) : texture(texture),
	                                                                              rect(rect){}
	
	SpriteAnimation::Frame::Frame(const sf::Texture& texture) : texture(texture),
	                                                            rect(sf::IntRect(0,
	                                                                             0,
	                                                                             texture.getSize().x,
	                                                                             texture.getSize().y)
	                                                            ){}
	
	void SpriteAnimation::sync(const sf::Time& time){
		if(sprite != nullptr){
			std::size_t frame = std::floor(time / frameTime);
			if(frame != currentFrame){
				currentFrame = frame;
				sprite->setTexture(frames[frame].texture);
				sprite->setTextureRect(frames[frame].rect);
			}
		}
	}
	
	void SpriteAnimation::updateCycleDuration() noexcept{
		setCycleDuration(frameTime * (sf::Int64)frames.size());
	}
	
	void SpriteAnimation::bindSprite(sf::Sprite* sprite) noexcept{
		SpriteAnimation::sprite = sprite;
	}
	
	void SpriteAnimation::addFrame(const sf::Texture& texture) noexcept{
		addFrame(texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	}
	
	void SpriteAnimation::addFrame(const sf::Texture& texture, sf::IntRect intRect) noexcept{
		frames.emplace_back(texture, intRect);
		updateCycleDuration();
	}
	
	void SpriteAnimation::setFrameTime(const sf::Time& frameTime) noexcept{
		SpriteAnimation::frameTime = frameTime;
		updateCycleDuration();
	}
	
	std::vector<SpriteAnimation::Frame>& SpriteAnimation::getFrames(){
		return frames;
	}
	
	const std::vector<SpriteAnimation::Frame>& SpriteAnimation::getFrames() const{
		return frames;
	}
	
	const sf::Time& SpriteAnimation::getFrameTime() const{
		return frameTime;
	}
	
	void SpriteAnimation::setCycleDuration(sf::Time cycleDuration) noexcept{
		Animation::setCycleDuration(cycleDuration);
	}
}