/**
* Core6
* Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#ifndef CORE6_ASSETMANAGER_HPP
#define CORE6_ASSETMANAGER_HPP

#include <Core6/utils/storage.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Core6/threading/concurent.hpp>

namespace c6{
	/** @brief class that holds all game resources */
	class ResourceManager{
		public:
			Concurent<Storage<std::string, sf::Texture>> texture;
			Concurent<Storage<std::string, sf::SoundBuffer>> sound;
			Concurent<Storage<std::string, sf::Shader>> shader;
			void addTexture(const std::string& filename);
			void removeTexture(const std::string& filename);
			void addSound(const std::string& filename);
			void removeSound(const std::string& filename);
			void addShader(const std::string& filename, const sf::Shader::Type type);
			void removeShader(const std::string& filename);
	};
}

#endif //CORE6_ASSETMANAGER_HPP
