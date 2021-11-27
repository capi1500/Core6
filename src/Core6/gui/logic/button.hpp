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

#include "widgetLogic.hpp"

namespace c6::widgets{
	class Button : public WidgetLogic{
		private:
			Runnable onClicked;
			Runnable onReleased;
			Runnable onHoverStart;
			Runnable onHoverEnd;
			
			bool clicked = false;
			
			Consumer<const sf::Event&> callback;
			Consumer<const sf::Time&> updater;
		public:
			Button(WidgetGraphics* graphics, const Runnable& onClicked, const Runnable& onReleased, const Runnable& onHoverStart, const Runnable& onHoverEnd);
			void onNotify(const sf::Event& event) noexcept override;
			void setOnHoverStart(const Runnable& onHoverStart);
			void setOnHoverEnd(const Runnable& onHoverEnd);
			void setOnClicked(const Runnable& onClicked);
			void setOnReleased(const Runnable& onReleased);
			void update(const sf::Time& time) override;
	};
	
	class ButtonBuilder{
		private:
			WidgetGraphics* graphics;
			Runnable onHoverStart;
			Runnable onHoverEnd;
			Runnable onClicked;
			Runnable onReleased;
		public:
			ButtonBuilder& setGraphics(WidgetGraphics* graphics);
			ButtonBuilder& setOnHoverStart(const Runnable& onHoverStart);
			ButtonBuilder& setOnHoverEnd(const Runnable& onHoverEnd);
			ButtonBuilder& setOnClicked(const Runnable& onClicked);
			ButtonBuilder& setOnReleased(const Runnable& onReleased);
			
			Button build();
			Button* buildPointer();
	};
}