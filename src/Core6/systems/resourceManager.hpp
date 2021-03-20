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
#include <Core6/utils/path.hpp>
#include <SFML/Graphics/Font.hpp>

namespace c6{
	namespace base{
		class ResourceManager{
			public:
				virtual void addTexture(const std::string& name) noexcept = 0;
				virtual void removeTexture(const std::string& name) noexcept = 0;
				virtual const sf::Texture& getTexture(const std::string& name) const noexcept = 0;
				virtual void addSound(const std::string& name) noexcept = 0;
				virtual void removeSound(const std::string& name) noexcept = 0;
				virtual const sf::SoundBuffer& getSound(const std::string& name) const noexcept = 0;
				virtual void addShader(const std::string& name, const sf::Shader::Type type) noexcept = 0;
				virtual void removeShader(const std::string& name) noexcept = 0;
				virtual const sf::Shader& getShader(const std::string& name) const noexcept = 0;
				virtual void addFont(const std::string& name) noexcept = 0;
				virtual void removeFont(const std::string& name) noexcept = 0;
				virtual const sf::Font& getFont(const std::string& name) const noexcept = 0;
				
				virtual void loadTextures(const Path& path) noexcept = 0;
				virtual void loadSounds(const Path& path) noexcept = 0;
				virtual void loadShaders(const Path& path) noexcept = 0;
				virtual void loadFonts(const Path& path) noexcept = 0;
				
				ResourceManager() = default;
				virtual ~ResourceManager() = default;
		};
	}
	
	namespace concepts{
		template<class T> concept ResourceManager = requires{
			std::is_base_of_v<base::ResourceManager, T>;
		};
	}
	
	/** @brief class that holds all game resources */
	class ResourceManager : public base::ResourceManager{
		private:
			Concurent<Storage<std::string, sf::Texture>> m_texture;
			Concurent<Storage<std::string, sf::SoundBuffer>> m_sound;
			Concurent<Storage<std::string, sf::Shader>> m_shader;
			Concurent<Storage<std::string, sf::Font>> m_fonts;
			
			enum Type{
				Texture,
				Sound,
				Shader,
				Font
			};
			std::thread m_thread;
			Concurent<bool> m_working;
			Concurent<std::queue<std::pair<Path, Type>>> m_queue;
			void threadFunction() noexcept;
			
			void texturesFromPath(const Path& path) noexcept;
			void soundsFromPath(const Path& path) noexcept;
			void shadersFromPath(const Path& path) noexcept;
			void fontsFromPath(const Path& path) noexcept;
		public:
			void addTexture(const std::string& name) noexcept override;
			void removeTexture(const std::string& name) noexcept override;
			const sf::Texture& getTexture(const std::string& name) const noexcept override;
			void addSound(const std::string& name) noexcept override;
			void removeSound(const std::string& name) noexcept override;
			const sf::SoundBuffer& getSound(const std::string& name) const noexcept override;
			void addShader(const std::string& name, const sf::Shader::Type type) noexcept override;
			void removeShader(const std::string& name) noexcept override;
			const sf::Shader& getShader(const std::string& name) const noexcept override;
			void addFont(const std::string& name) noexcept override;
			void removeFont(const std::string& name) noexcept override;
			const sf::Font& getFont(const std::string& name) const noexcept override;
			
			void loadTextures(const Path& path) noexcept override;
			void loadSounds(const Path& path) noexcept override;
			void loadShaders(const Path& path) noexcept override;
			void loadFonts(const Path& path) noexcept override;
			
			ResourceManager();
			virtual ~ResourceManager();
	};
}

#endif //CORE6_RESOURCEMANAGER_HPP
