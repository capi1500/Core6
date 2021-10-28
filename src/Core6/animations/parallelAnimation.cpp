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

#include "parallelAnimation.hpp"

namespace c6{
	void ParallelAnimation::sync(const sf::Time& time){
		for(std::reference_wrapper<Animation>& animation : animations){
			animation.get().sync(time);
		}
	}
	
	std::vector<std::reference_wrapper<Animation>>& ParallelAnimation::getAnimations() noexcept{
		return animations;
	}
	
	const std::vector<std::reference_wrapper<Animation>>& ParallelAnimation::getAnimations() const noexcept{
		return animations;
	}
	
	void ParallelAnimation::addAnimation(Animation& animation){
		animations.push_back(std::ref(animation));
	}
	
	void ParallelAnimation::setAnimation(std::size_t i, Animation& animation){
		animations[i] = std::ref(animation);
	}
	
	Animation& ParallelAnimation::getAnimation(std::size_t i) const{
		return animations[i].get();
	}
	
	void ParallelAnimation::removeAnimation(std::size_t i){
		animations.erase(animations.begin() + i);
	}
}

