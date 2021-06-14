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

#ifndef CORE6_WIDGETASSETPACK_HPP
#define CORE6_WIDGETASSETPACK_HPP

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace c6{
	struct WidgetAssetPack{
		struct TextDef{
			sf::Text::Style style;
			unsigned characterSize;
			float lineSpacing;
			float letterSpacing;
			float thickness;
			sf::Color fillColor;
			sf::Color outlineColor;
			TextDef(){
				style = sf::Text::Regular;
				characterSize = 12;
				lineSpacing = 1;
				letterSpacing = 1;
				thickness = 0;
				fillColor = sf::Color::White;
				outlineColor = sf::Color::Black;
			}
		};
		
		struct Frame9{
			sf::Sprite part[3][3];
		};
		
		struct FrameDef{
			Frame9 regular;
			Frame9 disabled;
			Frame9 highlighted;
		};
		
		struct ButtonDef : public FrameDef{
			Frame9 clicked;
		};
		
		struct ToggleDef{
			ButtonDef active;
			ButtonDef inactive;
		};
		
		sf::Font font;
		TextDef regular;
		TextDef highlighted;
		TextDef link;
		TextDef h1;
		TextDef h2;
		TextDef h3;
		TextDef h4;
		TextDef h5;
		TextDef h6;
		
		FrameDef frame;
		ButtonDef button;
		ToggleDef toggleButton;
		ToggleDef radioboxButton;
		ToggleDef checkboxButton;
	};
}

#endif //CORE6_WIDGETASSETPACK_HPP
