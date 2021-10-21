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

#include <string>

namespace c6{
	class WidgetAssetPack{
		public:
			class Frame9{
				private:
					std::string textureName[3][3];
				public:
					[[nodiscard]]
					std::string* operator [] (size_t id);
					[[nodiscard]]
					const std::string* operator [] (size_t id) const;
			};
			
			class Button{
				private:
					Frame9 notClicked;
					Frame9 notClickedHover;
					Frame9 afterClicked;
					Frame9 clicked;
					Frame9 clickedHover;
					Frame9 afterUnclicked;
					Frame9 disabled;
					Frame9 disabledHover;
					bool usingNotClickedHover = false;
					bool usingAfterClicked = false;
					bool usingClicked = false;
					bool usingClickedHover = false;
					bool usingAfterNotClicked = false;
					bool usingDisabled = false;
					bool usingDisabledHover = false;
				public:
					void setNotClicked(Frame9 notClicked);
					void setNotClickedHover(Frame9 notClickedHover);
					void setAfterClicked(Frame9 afterClicked);
					void setClicked(Frame9 clicked);
					void setClickedHover(Frame9 clickedHover);
					void setAfterNotClicked(Frame9 afterNotClicked);
					void setDisabled(Frame9 disabled);
					void setDisabledHover(Frame9 disabledHover);
					
					[[nodiscard]]
					const Frame9& getNotClicked() const;
					[[nodiscard]]
					const Frame9& getNotClickedHover() const;
					[[nodiscard]]
					const Frame9& getAfterClicked() const;
					[[nodiscard]]
					const Frame9& getClicked() const;
					[[nodiscard]]
					const Frame9& getClickedHover() const;
					[[nodiscard]]
					const Frame9& getAfterUnlicked() const;
					[[nodiscard]]
					const Frame9& getDisabled() const;
					[[nodiscard]]
					const Frame9& getDisabledHover() const;
				
			};
	};
}

