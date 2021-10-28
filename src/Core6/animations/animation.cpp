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

#include <utility>
#include <iostream>
#include "animation.hpp"

namespace c6{
	void Animation::update(sf::Time time) noexcept{
		if(status == Running){
			elapsedTime += time;
			
			if(!indefinite && elapsedTime >= duration){ // if the animation should end, set variables so code below can correctly calculate state of animation
				time = duration - (elapsedTime - time); // set time to such value that simulates updating frame only to animations duration
				elapsedTime = duration;
			}
			
			if(!currentlyReversed)
				frame += time;
			else
				frame -= time;
			
			while(frame < sf::Time::Zero || cycleDuration < frame){ // check if frame time is beyond cycle duration segment. In while for security (lags)
				cyclesFinished++;
				if(!indefinite && cyclesFinished == cycleCount){
					sync(currentlyReversed ? sf::Time::Zero : cycleDuration);
					stop();
					return;
				}
				if(reverse)
					currentlyReversed = !currentlyReversed;
				sf::Time tmp;
				if(frame < sf::Time::Zero)
					tmp = -frame;
				else
					tmp = frame - cycleDuration;
				frame = (currentlyReversed ? cycleDuration - tmp : tmp);
			}
			sync(frame);
			
			if(!indefinite && elapsedTime == duration){
				stop();
				return;
			}
		}
	}
	
	void Animation::pause() noexcept{
		if(status != Paused){
			status = Paused;
		}
	}
	
	void Animation::play() noexcept{
		if(status != Running){
			status = Running;
		}
	}
	
	void Animation::playFrom(sf::Time time) noexcept{
		if(status != Running){
			jumpTo(time);
			play();
		}
	}
	
	void Animation::jumpTo(sf::Time time) noexcept{
		frame = time;
		sync(time);
	}
	
	void Animation::stop() noexcept{
		if(status != Stopped){
			elapsedTime = sf::Time::Zero;
			jumpTo(sf::Time::Zero);
			cyclesFinished = 0;
			status = Stopped;
		}
	}
	
	void Animation::restart() noexcept{
		stop();
		play();
	}
	
	Animation::Status Animation::getStatus() const noexcept{
		return status;
	}
	
	const sf::Time& Animation::getDuration() const noexcept{
		return duration;
	}
	
	void Animation::setDuration(sf::Time duration) noexcept{
		Animation::duration = std::move(duration);
	}
	
	void Animation::setIndefinite(bool indefinite) noexcept{
		Animation::indefinite = indefinite;
	}
	
	bool Animation::isIndefinite() const noexcept{
		return indefinite;
	}
	
	int Animation::getCycleCount() const noexcept{
		return cycleCount;
	}
	
	void Animation::setCycleCount(int cycleCount) noexcept{
		Animation::cycleCount = cycleCount;
	}
	
	int Animation::getCyclesFinished() const noexcept{
		return cyclesFinished;
	}
	
	bool Animation::isReverse() const noexcept{
		return reverse;
	}
	
	void Animation::setReverse(bool reverse) noexcept{
		Animation::reverse = reverse;
	}
	
	const sf::Time& Animation::getElapsedTime() const noexcept{
		return elapsedTime;
	}
	
	const sf::Time& Animation::getCycleDuration() const noexcept{
		return cycleDuration;
	}
	
	void Animation::setCycleDuration(sf::Time cycleDuration) noexcept{
		Animation::cycleDuration = std::move(cycleDuration);
	}
}