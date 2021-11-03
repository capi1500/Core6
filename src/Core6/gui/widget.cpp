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

#include "widget.hpp"

namespace c6{
	// TODO: rework of this function
	// got to take into account all transformations possible
	// (scale, rotation, shift) and think how those change the positioning
	void Widget::recalculatePosition() noexcept{
		sf::FloatRect localBounds = getLocalBounds();
		sf::FloatRect frameBounds = parent->getLocalBounds();
		float scale;
		switch(adjustment){
			case FitToWidth:
				scale = frameBounds.width / localBounds.width;
				if(keepRatio)
					setScale(scale, scale);
				else
					setScale(scale, 1);
				break;
			case FitToHeight:
				scale = frameBounds.height / localBounds.height;
				if(keepRatio)
					setScale(scale, scale);
				else
					setScale(1, scale);
				break;
			case FitToSize:
				if(keepRatio){
					scale = std::min(frameBounds.width / localBounds.width, frameBounds.height / localBounds.height);
					setScale(scale, scale);
				}
				else
					setScale(frameBounds.width / localBounds.width, frameBounds.height / localBounds.height);
				break;
			default: break;
		}
	}
	
	void Widget::adjust(Widget::Adjustment adjustment, bool keepRatio) noexcept{
		Widget::adjustment = adjustment;
		Widget::keepRatio = keepRatio;
		recalculatePosition();
	}
	
	void Widget::align() noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(const sf::Vector2i& shift) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(const sf::Vector2f& factorShift) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(Widget::Alignment alignment) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(Widget::Alignment alignment, const sf::Vector2i& shift) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(Widget::Alignment alignment, const sf::Vector2f& factorShift) noexcept{
		align(alignment, shift, factorShift);
	}
	
	void Widget::align(Widget::Alignment alignment, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept{
		Widget::alignment = alignment;
		Widget::shift = shift;
		Widget::factorShift = factorShift;
		recalculatePosition();
	}
	
	void Widget::align(const Widget* widget) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, const sf::Vector2i& shift) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, const sf::Vector2f& factorShift) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, Widget::Alignment alignment) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, Widget::Alignment alignment, const sf::Vector2i& shift) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, Widget::Alignment alignment, const sf::Vector2f& factorShift) noexcept{
		align(widget, alignment, shift, factorShift);
	}
	
	void Widget::align(const Widget* widget, Widget::Alignment alignment, const sf::Vector2i& shift, const sf::Vector2f& factorShift) noexcept{
		parent = widget;
		align(alignment, shift, factorShift);
	}
	
	void Widget::setCropToFrame(bool cropToFrame){
		Widget::cropToFrame = cropToFrame;
	}
}