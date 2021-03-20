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

#ifndef CORE6_SOUNDBOARD_HPP
#define CORE6_SOUNDBOARD_HPP

#include <Core6/utils/storage.hpp>
#include <SFML/Audio/Music.hpp>
#include <string>

namespace c6{
	namespace base{
		class Soundboard : public Storage<std::string, sf::Music>{
		
		};
	}
	
	namespace concepts{
		template<class T> concept Soundboard = requires{
			std::is_base_of_v<base::Soundboard, T>;
		};
	}
	
	class Soundboard : public base::Soundboard{
	
	};
}

#endif //CORE6_SOUNDBOARD_HPP
