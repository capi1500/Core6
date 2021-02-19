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

#ifndef CORE6_RESOURCEMANAGER_HPP
#define CORE6_RESOURCEMANAGER_HPP

#include <Core6/utils/storage.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Core6/threading/concurent.hpp>
#include <thread>
#include <condition_variable>
#include <queue>

namespace c6{
	/** @brief class that holds all game resources */
	class ResourceManager{
		private:
			Concurent<Storage<std::string, sf::Texture>> m_texture;
			Concurent<Storage<std::string, sf::SoundBuffer>> m_sound;
			Concurent<Storage<std::string, sf::Shader>> m_shader;
			
			enum Type{
				Texture,
				Sound,
				Shader
			};
			std::thread m_thread;
			Concurent<bool> m_working;
			Concurent<std::queue<std::pair<Path, Type>>> m_queue;
			void threadFunction();
			
			void texturesFromPath(const Path& path);
			void soundsFromPath(const Path& path);
			void shadersFromPath(const Path& path);
		public:
			void addTexture(const std::string& name);
			void removeTexture(const std::string& name);
			const sf::Texture& getTexture(const std::string& name);
			void addSound(const std::string& name);
			void removeSound(const std::string& name);
			const sf::SoundBuffer& getSoundbuffer(const std::string& name);
			void addShader(const std::string& name, const sf::Shader::Type type);
			void removeShader(const std::string& name);
			const sf::Shader& getShader(const std::string& name);
			
			void loadTextures(const Path& path);
			void loadSounds(const Path& path);
			void loadShaders(const Path& path);
			
			ResourceManager();
			virtual ~ResourceManager();
	};
}

#endif //CORE6_RESOURCEMANAGER_HPP
