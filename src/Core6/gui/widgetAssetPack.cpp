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

#include "widgetAssetPack.hpp"

namespace c6{
	std::string* WidgetAssetPack::Frame9::operator [](size_t id){
		return textureName[id];
	}
	
	const std::string* WidgetAssetPack::Frame9::operator [](size_t id) const{
		return textureName[id];
	}
	
	void WidgetAssetPack::Button::setNotClicked(WidgetAssetPack::Frame9 notClicked){
		Button::notClicked = std::move(notClicked);
	}
	
	void WidgetAssetPack::Button::setNotClickedHover(WidgetAssetPack::Frame9 notClickedHover){
		Button::notClickedHover = std::move(notClickedHover);
		usingNotClickedHover = true;
	}
	
	void WidgetAssetPack::Button::setAfterClicked(WidgetAssetPack::Frame9 afterClicked){
		Button::afterClicked = std::move(afterClicked);
		usingAfterClicked = true;
	}
	
	void WidgetAssetPack::Button::setClicked(WidgetAssetPack::Frame9 clicked){
		Button::clicked = std::move(clicked);
		usingClicked = true;
	}
	
	void WidgetAssetPack::Button::setClickedHover(WidgetAssetPack::Frame9 clickedHover){
		Button::clickedHover = std::move(clickedHover);
		usingClickedHover = true;
	}
	
	void WidgetAssetPack::Button::setAfterNotClicked(WidgetAssetPack::Frame9 afterNotClicked){
		Button::afterUnclicked = std::move(afterNotClicked);
		usingAfterNotClicked = true;
	}
	
	void WidgetAssetPack::Button::setDisabled(WidgetAssetPack::Frame9 disabled){
		Button::disabled = std::move(disabled);
		usingDisabled = true;
	}
	
	void WidgetAssetPack::Button::setDisabledHover(WidgetAssetPack::Frame9 disabledHover){
		Button::disabledHover = std::move(disabledHover);
		usingDisabledHover = true;
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getNotClicked() const{
		return notClicked;
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getNotClickedHover() const{
		if(usingNotClickedHover)
			return notClickedHover;
		return getNotClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getAfterClicked() const{
		if(usingAfterClicked)
			return afterClicked;
		return getClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getClicked() const{
		if(usingClicked)
			return clicked;
		return getNotClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getClickedHover() const{
		if(usingClickedHover)
			return clickedHover;
		return getClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getAfterUnlicked() const{
		if(usingAfterNotClicked)
			return afterUnclicked;
		return getNotClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getDisabled() const{
		if(usingDisabled)
			return disabled;
		return getNotClicked();
	}
	
	const WidgetAssetPack::Frame9& WidgetAssetPack::Button::getDisabledHover() const{
		if(usingDisabledHover)
			return disabledHover;
		return getDisabled();
	}
}