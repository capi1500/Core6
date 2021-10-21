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

//#include <concurrent.hpp>
#include <Core6/utils/storage.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Core6/utils/filepath.hpp>
#include <SFML/Audio/Music.hpp>
#include <Core6/base/loggable.hpp>

namespace c6{
	class ResourceManager : public Loggable{
		private:
			// TODO those concurret doesn't work, need to find sth working
			/*concurrent<Storage<std::string, sf::Texture>> textures;
			concurrent<Storage<std::string, sf::SoundBuffer>> sounds;
			concurrent<Storage<std::string, sf::Shader>> shaders;
			concurrent<Storage<std::string, sf::Font>> fonts;
			concurrent<Storage<std::string, sf::Music>> music;*/
			
			Storage<std::string, sf::Texture> textures;
			Storage<std::string, sf::SoundBuffer> sounds;
			Storage<std::string, sf::Shader> shaders;
			Storage<std::string, sf::Font> fonts;
			Storage<std::string, sf::Music> music;
		public:
			void addTexture(const Filepath& path) noexcept;
			void addTexture(const std::string& name, const Filepath& path) noexcept;
			void removeTexture(const std::string& name) noexcept;
			const sf::Texture& getTexture(const std::string& name) const noexcept;
			bool hasTexture(const std::string& name) const noexcept;
			
			void addSound(const Filepath& path) noexcept;
			void addSound(const std::string& name, const Filepath& path) noexcept;
			void removeSound(const std::string& name) noexcept;
			const sf::SoundBuffer& getSound(const std::string& name) const noexcept;
			bool hasSound(const std::string& name) const noexcept;
			
			void addShader(const Filepath& path, const sf::Shader::Type type) noexcept;
			void addShader(const std::string& name, const Filepath& path, const sf::Shader::Type type) noexcept;
			void removeShader(const std::string& name) noexcept;
			const sf::Shader& getShader(const std::string& name) const noexcept;
			bool hasShader(const std::string& name) const noexcept;
			
			void addFont(const Filepath& path) noexcept;
			void addFont(const std::string& name, const Filepath& path) noexcept;
			void removeFont(const std::string& name) noexcept;
			const sf::Font& getFont(const std::string& name) const noexcept;
			bool hasFont(const std::string& name) const noexcept;
			
			void addMusic(const Filepath& path) noexcept;
			void addMusic(const std::string& name, const Filepath& path) noexcept;
			void removeMusic(const std::string& name) noexcept;
			const sf::Music& getMusic(const std::string& name) const noexcept;
			bool hasMusic(const std::string& name) const noexcept;
			
			void loadTextures(const Filepath& path) noexcept;
			void loadSounds(const Filepath& path) noexcept;
			void loadShaders(const Filepath& path) noexcept;
			void loadFonts(const Filepath& path) noexcept;
			
			void loadMusic(const Filepath& path) noexcept;
	};
}

