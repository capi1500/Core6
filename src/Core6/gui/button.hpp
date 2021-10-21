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

#include <Core6/utils/callback.hpp>
#include <Core6/base/listener/listener.hpp>
#include <Core6/ecs/entityComponentSystem.hpp>
#include <SFML/Window/Event.hpp>
#include "frame9.hpp"

namespace c6{
	/*class Button : public Listener<sf::Event>{
		private:
			enum ButtonState{
				Default,
				DefaultHover,
				AfterClicked,
				Clicked,
				ClickedHover,
				AfterUnclicked,
				Disabled,
				DisabledHover
			};
			
			ButtonState state;
			//WidgetAssetPack::Button assetPack;
			
			enum ClickBehavior{
				Instant,
				Timed,
				AfterClickEnds,
				AfterHoverEnds,
				UntilClickedAgain
			};
			
			ClickBehavior clickBehavior;
			sf::Time deltaTime;
			
			Callback<bool, sf::Vector2i> isHover;
			
			Callback<void> switchToDefault;
			Callback<void, sf::Vector2i> switchToDefaultHover;
			Callback<void, sf::Vector2i> switchToAfterClicked;
			Callback<void> switchToClicked;
			Callback<void, sf::Vector2i> switchToClickedHover;
			Callback<void, sf::Vector2i> switchToAfterUnclicked;
			Callback<void> switchToDisabled;
			Callback<void, sf::Vector2i> switchToDisabledHover;
			
			Callback<void> switchFromDefault;
			Callback<void> switchFromDefaultHover;
			Callback<void> switchFromAfterClicked;
			Callback<void> switchFromClicked;
			Callback<void> switchFromClickedHover;
			Callback<void> switchFromAfterUnclicked;
			Callback<void> switchFromDisabled;
			Callback<void> switchFromDisabledHover;
		public:
			Button();
			
			
			
			void onNotify(const sf::Event& event) noexcept override;
	};*/
}

