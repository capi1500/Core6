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

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "animation.hpp"

namespace c6{
	class SpriteAnimation : public Animation{
		public:
			struct Frame{
				const sf::Texture& texture;
				sf::IntRect rect;
				Frame(const sf::Texture& texture);
				Frame(const sf::Texture& texture, sf::IntRect rect);
			};
		private:
			sf::Sprite* sprite = nullptr;
			std::vector<Frame> frames;
			sf::Time frameTime = sf::milliseconds(100);
			std::size_t currentFrame = 0;
			
			void updateCycleDuration() noexcept;
			void setCycleDuration(sf::Time cycleDuration) noexcept;
		protected:
			void sync(const sf::Time& time) override;
		public:
			SpriteAnimation() noexcept;
			explicit SpriteAnimation(sf::Sprite* sprite) noexcept;
			
			void bindSprite(sf::Sprite* sprite) noexcept;
			void addFrame(const sf::Texture& texture) noexcept;
			void addFrame(const sf::Texture& texture, sf::IntRect intRect) noexcept;
			void setFrameTime(const sf::Time& frameTime) noexcept;
			const sf::Time& getFrameTime() const;
			
			std::vector<Frame>& getFrames();
			const std::vector<Frame>& getFrames() const;
	};
}

