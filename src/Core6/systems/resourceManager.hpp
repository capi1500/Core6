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

#include <concurrent.hpp>
#include <Core6/utils/storage.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Core6/utils/path.hpp>

namespace c6{
	class ResourceManager{
		private:
			concurrent<Storage<std::string, sf::Texture>> textures;
			concurrent<Storage<std::string, sf::SoundBuffer>> sounds;
			concurrent<Storage<std::string, sf::Shader>> shaders;
			concurrent<Storage<std::string, sf::Font>> fonts;
		public:
			void addTexture(const std::string& name) noexcept;
			void removeTexture(const std::string& name) noexcept;
			const sf::Texture& getTexture(const std::string& name) const noexcept;
			void addSound(const std::string& name) noexcept;
			void removeSound(const std::string& name) noexcept;
			const sf::SoundBuffer& getSound(const std::string& name) const noexcept;
			void addShader(const std::string& name, const sf::Shader::Type type) noexcept;
			void removeShader(const std::string& name) noexcept;
			const sf::Shader& getShader(const std::string& name) const noexcept;
			void addFont(const std::string& name) noexcept;
			void removeFont(const std::string& name) noexcept;
			const sf::Font& getFont(const std::string& name) const noexcept;
			
			void loadTextures(const Path& path) noexcept;
			void loadSounds(const Path& path) noexcept;
			void loadShaders(const Path& path) noexcept;
			void loadFonts(const Path& path) noexcept;
	};
}

