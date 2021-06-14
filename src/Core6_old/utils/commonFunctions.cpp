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

#include "commonFunctions.hpp"
#include <random>
#include <math.h>

namespace c6{
	std::string keyToString(sf::Keyboard::Key key){
		if(sf::Keyboard::A <= key and key <= sf::Keyboard::Z)
			return std::string(1, static_cast<char>(key + 'A'));
		if(sf::Keyboard::Num0 <= key and key <= sf::Keyboard::Num9)
			return std::to_string(key - sf::Keyboard::Num0);
		if(sf::Keyboard::Numpad0 <= key and key <= sf::Keyboard::Numpad9)
			return "Num" + std::to_string(key - sf::Keyboard::Numpad0);
		if(sf::Keyboard::F1 <= key and key <= sf::Keyboard::F15)
			return "F" + std::to_string(key - sf::Keyboard::F1 + 1);
		if(key == sf::Keyboard::Escape)
			return "Esc";
		if(key == sf::Keyboard::LControl)
			return "CtrlL";
		if(key == sf::Keyboard::LShift)
			return "ShiftL";
		if(key == sf::Keyboard::LAlt)
			return "AltL";
		if(key == sf::Keyboard::LSystem)
			return "WinL";
		if(key == sf::Keyboard::RControl)
			return "CtrlR";
		if(key == sf::Keyboard::RShift)
			return "ShiftR";
		if(key == sf::Keyboard::RAlt)
			return "AltR";
		if(key == sf::Keyboard::RSystem)
			return "WinR";
		if(key == sf::Keyboard::Menu)
			return "Menu";
		if(key == sf::Keyboard::LBracket)
			return "[";
		if(key == sf::Keyboard::RBracket)
			return "]";
		if(key == sf::Keyboard::Semicolon)
			return ";";
		if(key == sf::Keyboard::Comma)
			return ",";
		if(key == sf::Keyboard::Period)
			return ".";
		if(key == sf::Keyboard::Quote)
			return "'";
		if(key == sf::Keyboard::Slash)
			return "/";
		if(key == sf::Keyboard::Backslash)
			return "\\";
		if(key == sf::Keyboard::Tilde)
			return "~";
		if(key == sf::Keyboard::Equal)
			return "=";
		if(key == sf::Keyboard::Hyphen)
			return "-";
		if(key == sf::Keyboard::Space)
			return "Space";
		if(key == sf::Keyboard::Enter)
			return "Enter";
		if(key == sf::Keyboard::Backspace)
			return "Backspace";
		if(key == sf::Keyboard::Tab)
			return "Tab";
		if(key == sf::Keyboard::PageUp)
			return "PgUp";
		if(key == sf::Keyboard::PageDown)
			return "PgDn";
		if(key == sf::Keyboard::End)
			return "End";
		if(key == sf::Keyboard::Home)
			return "Home";
		if(key == sf::Keyboard::Insert)
			return "Ins";
		if(key == sf::Keyboard::Delete)
			return "Del";
		if(key == sf::Keyboard::Add)
			return "+";
		if(key == sf::Keyboard::Subtract)
			return "-";
		if(key == sf::Keyboard::Multiply)
			return "*";
		if(key == sf::Keyboard::Divide)
			return "/";
		if(key == sf::Keyboard::Left)
			return "Left";
		if(key == sf::Keyboard::Right)
			return "Right";
		if(key == sf::Keyboard::Up)
			return "Up";
		if(key == sf::Keyboard::Down)
			return "Down";
		if(key == sf::Keyboard::Pause)
			return "Pause";
		return "Unknown";
	}
	
	std::string buttonToString(sf::Mouse::Button button){
		if(button == sf::Mouse::Left)
			return "LeftMouse";
		if(button == sf::Mouse::Right)
			return "RightMouse";
		if(button == sf::Mouse::Middle)
			return "MiddleMouse";
		if(button == sf::Mouse::XButton1)
			return "Button1Mouse";
		if(button == sf::Mouse::XButton2)
			return "Button2Mouse";
		return "Unknown";
	}
	
	std::string vector2fToString(sf::Vector2f vec){
		return "[" + std::to_string(vec.x) + " " + std::to_string(vec.y) + "]";
	}
	
	Message sfEventToMessage([[maybe_unused]] const sf::Event& event){
		std::string text = "sf::Event";
		if(event.type == sf::Event::KeyPressed){
			text += "::KeyPressed " + keyToString(event.key.code);
		}
		else if(event.type == sf::Event::KeyReleased){
			text += "::KeyReleased " + keyToString(event.key.code);
		}
		else if(event.type == sf::Event::Closed)
			text += "::Closed";
		else if(event.type == sf::Event::GainedFocus)
			text += "::GainedFocus";
		else if(event.type == sf::Event::LostFocus)
			text += "::LostFocus";
		else if(event.type == sf::Event::MouseButtonPressed)
			text += "::MouseButtonPressed " + buttonToString(event.mouseButton.button) + " + at [" + std::to_string(event.mouseButton.x) + ", " + std::to_string(event.mouseButton.y) + "]";
		else if(event.type == sf::Event::MouseButtonReleased)
			text += "::MouseButtonReleased " + buttonToString(event.mouseButton.button) + " + at [" + std::to_string(event.mouseButton.x) + ", " + std::to_string(event.mouseButton.y) + "]";
		else if(event.type == sf::Event::MouseEntered)
			text += "::MouseEntered";
		else if(event.type == sf::Event::MouseLeft)
			text += "::MouseLeft";
		else if(event.type == sf::Event::MouseMoved)
			text += "::MouseMoved to [" + std::to_string(event.mouseMove.x) + ", " + std::to_string(event.mouseMove.y) + "]";
		else if(event.type == sf::Event::MouseWheelMoved)
			text += "::MouseWheelMoved by " + std::to_string(event.mouseWheel.delta) + "[" + std::to_string(event.mouseWheel.x) + ", " + std::to_string(event.mouseWheel.y) + "]";
		else if(event.type == sf::Event::MouseWheelScrolled){
			text += "::MouseWheelScrolled ";
			if(event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
				text += "Horizontal";
			else
				text += "Vertical";
			text += " by " + std::to_string(event.mouseWheelScroll.delta) + "[" + std::to_string(event.mouseWheelScroll.x) + ", " + std::to_string(event.mouseWheelScroll.y) + "]";
		}
		else if(event.type == sf::Event::Resized)
			text += "::Resized";
		else if(event.type == sf::Event::TextEntered)
			text += "::TextEntered";
		return Message("sf::Event", MessageType::Debug);
	}
	
	unsigned long long hash(const std::string& str, unsigned long long pow, unsigned long long mod){
		unsigned long long out = 0;
		for(auto& c : str)
			out = (out * pow + c) % mod;
		return out;
	}
	
	unsigned long long hash(const char str[], unsigned long long pow, unsigned long long mod){
		return hash(std::string(str), pow, mod);
	}
	
	float randPercentage(){
		return rand(0, 10000) / 100.f;
	}
	
	float randAngle(){
		return rand<int>(0, 2 * M_PI * 1000000) / 1000000.f;
	}
}