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

#include <SFML/System/Time.hpp>

namespace c6{
	/**
	 * @brief Represents an object that changes in time.
	 */
	class Animation{
		public:
			/**
			 * @brief Status of animation
			 */
			enum Status{
				Paused,
				Running,
				Stopped
			};
		private:
			Status status;
			sf::Time duration = sf::Time::Zero; /// Duration of whole animation
			
			sf::Time cycleDuration = sf::Time::Zero; /// Duration of one animation cycle, if animation plays only one cicle, equal to duration
			sf::Time frame = sf::Time::Zero; /// Timepoint at which animation currently is
			sf::Time elapsedTime = sf::Time::Zero; /// Summaric time when animation is playing. Resets when stopped, but not when paused.

			int cyclesFinished = 0; /// How many cycles are finished
			bool currentlyReversed = false; /// If current cycle of animation should update backwards
			
			int cycleCount = 1; /// How many cycles should animation play
			bool indefinite = false; /// If animation should stop when elapsedTime >= duration

			bool reverse = false; /// If animation should reverse, or jump to begining, when one cycle passes
		protected:
			/**
			 * @brief Sets specific timepoint in animation
			 * @param time
			 */
			virtual void sync(const sf::Time& time) = 0;
			
			friend class SequentialAnimation;
			friend class ParallelAnimation;
		public:
			/**
			 * @brief Updates animation by certain ammount of time
			 * @param time
			 */
			void update(sf::Time time) noexcept;
			
			void pause() noexcept; /// Pauses the animation, if resumed, continues from the same time. Does nothing if alredy playing
			void play() noexcept; /// Plays animation from start or resumes if it was paused. Does nothing if already playing.
			void playFrom(sf::Time time) noexcept; /// Plays animation from certain time
			void jumpTo(sf::Time time) noexcept; /// Jumps to certain time
			void stop() noexcept; /// Stops the animation, if played again, starts from the begining
			void restart() noexcept; /// Restarts the animation from the beginning
			/**
			 * @brief Returns status of the animation
			 * @return Paused, Running or Stopped
			 */
			Status getStatus() const noexcept;
			
			const sf::Time& getDuration() const noexcept; /// Get duration of animation
			void setDuration(sf::Time duration) noexcept; /// Set duration of animation
			void setCycleDuration(sf::Time cycleDuration) noexcept; /// Set duration of one cycle of animation
			const sf::Time& getCycleDuration() const noexcept; /// Get duration of one cycle of animation
			const sf::Time& getElapsedTime() const noexcept; /// Get how long the animation is playing
			
			void setCycleCount(int cycleCount) noexcept; /// Set how many cycles should animation play
			int getCycleCount() const noexcept; /// Get how many cycles should animation play
			int getCyclesFinished() const noexcept; /// Get how many cycles animation already finished
			void setIndefinite(bool indefinite) noexcept; /// Set if animation should play indefinite ammount of time
			bool isIndefinite() const noexcept; /// Check if animation should play indefinite ammount of time
			void setReverse(bool reverse) noexcept; /// Set if animation should reverse after each cycle
			bool isReverse() const noexcept; /// Check if animation should reverse after each cycle
			
			virtual ~Animation() noexcept = default;
	};
}

