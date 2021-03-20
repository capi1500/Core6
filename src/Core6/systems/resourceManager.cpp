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

#include <Core6/utils/path.hpp>
#include <Core6/framework.hpp>
#include "resourceManager.hpp"
#include "console.hpp"

namespace c6{
	void ResourceManager::addTexture(const std::string& name) noexcept{
		m_texture.lock();
		m_texture.get()[name].loadFromFile(name);
		m_texture.unlock();
	}
	
	void ResourceManager::removeTexture(const std::string& name) noexcept{
		m_texture.lock();
		m_texture.get().erase(name);
		m_texture.unlock();
	}
	
	const sf::Texture& ResourceManager::getTexture(const std::string& name) const noexcept{
		while(true){
			m_texture.lock();
			if(m_texture().count(name) != 0){
				const sf::Texture& out = m_texture().at(name);
				m_texture.unlock();
				return out;
			}
			m_texture.unlock();
		}
	}
	
	void ResourceManager::addSound(const std::string& name) noexcept{
		m_sound.lock();
		m_sound.get()[name].loadFromFile(name);
		m_sound.unlock();
	}
	
	void ResourceManager::removeSound(const std::string& name) noexcept{
		m_sound.lock();
		m_sound.get().erase(name);
		m_sound.unlock();
	}
	
	const sf::SoundBuffer& ResourceManager::getSound(const std::string& name) const noexcept{
		while(true){
			m_sound.lock();
			if(m_sound().count(name) != 0){
				const sf::SoundBuffer& out = m_sound().at(name);
				m_sound.unlock();
				return out;
			}
			m_sound.unlock();
		}
	}
	
	void ResourceManager::addShader(const std::string& name, const sf::Shader::Type type) noexcept{
		m_shader.lock();
		m_shader.get()[name].loadFromFile(name, type);
		m_shader.unlock();
	}
	
	void ResourceManager::removeShader(const std::string& name) noexcept{
		m_shader.lock();
		m_shader.get().erase(name);
		m_shader.unlock();
	}
	
	const sf::Shader& ResourceManager::getShader(const std::string& name) const noexcept{
		while(true){
			m_shader.lock();
			if(m_shader().count(name) != 0){
				const sf::Shader& out = m_shader().at(name);
				m_shader.unlock();
				return out;
			}
			m_shader.unlock();
		}
	}
	
	void ResourceManager::addFont(const std::string& name) noexcept{
		m_fonts.lock();
		m_fonts.get()[name].loadFromFile(name);
		m_fonts.unlock();
	}
	
	void ResourceManager::removeFont(const std::string& name) noexcept{
		m_fonts.lock();
		m_fonts.get().erase(name);
		m_fonts.unlock();
	}
	
	const sf::Font& ResourceManager::getFont(const std::string& name) const noexcept{
		while(true){
			m_fonts.lock();
			if(m_fonts().count(name) != 0){
				const sf::Font& out = m_fonts().at(name);
				m_fonts.unlock();
				return out;
			}
			m_fonts.unlock();
		}
	}
	
	void ResourceManager::texturesFromPath(const Path& path) noexcept{
		Console::send(Message("Loading textures from " + path.getPath(), MessageType::Loading));
		for(auto ext : {"bmp", "png", "tga", "jpg", "gif", "psd", "hdr", "pic"}){
			path.execute([&](const std::string& path){
				Console::send(Message("Loading texture '" + path + "'", MessageType::Loading));
				addTexture(path);
			}, true, std::string(".") + ext);
		}
	}
	
	void ResourceManager::soundsFromPath(const Path& path) noexcept{
		Console::send(Message("Loading sounds from " + path.getPath(), MessageType::Loading));
		for(auto ext : {"wav", "ogg", "flac"}){
			path.execute([&](const std::string& path){
				Console::send(Message("Loading sound '" + path + "'", MessageType::Loading));
				addSound(path);
			}, true, std::string(".") + ext);
		}
	}
	
	void ResourceManager::shadersFromPath(const Path& path) noexcept{
		Console::send(Message("Loading shaders from " + path.getPath(), MessageType::Loading));
		path.execute([&](const std::string& path){
			Console::send(Message("Loading fragment shader '" + path + "'", MessageType::Loading));
			addShader(path, sf::Shader::Fragment);
		}, true, ".frag");
		path.execute([&](const std::string& path){
			Console::send(Message("Loading vertex shader '" + path + "'", MessageType::Loading));
			addShader(path, sf::Shader::Vertex);
		}, true, ".vert");
		path.execute([&](const std::string& path){
			Console::send(Message("Loading geometry shader '" + path + "'", MessageType::Loading));
			addShader(path, sf::Shader::Geometry);
		}, true, ".geom");
	}
	
	void ResourceManager::fontsFromPath(const Path& path) noexcept{
		for(auto ext : {"ttf", "otf", "cff", "pfb", "pfm", "afm", "aat", "sil", "fon", "bdf", "pfr", }){
			path.execute([&](const std::string& path){
				Console::send(Message("Loading sound '" + path + "'", MessageType::Loading));
				addFont(path);
			}, true, std::string(".") + ext);
		}
	}
	
	void ResourceManager::loadTextures(const Path& path) noexcept{
		m_queue.lock();
		m_queue.get().push({path, Texture});
		m_queue.unlock();
	}
	
	void ResourceManager::loadSounds(const Path& path) noexcept{
		m_queue.lock();
		m_queue.get().push({path, Sound});
		m_queue.unlock();
	}
	
	void ResourceManager::loadShaders(const Path& path) noexcept{
		m_queue.lock();
		m_queue.get().push({path, Shader});
		m_queue.unlock();
	}
	
	void ResourceManager::loadFonts(const Path& path) noexcept{
		m_queue.lock();
		m_queue.get().push({path, Font});
		m_queue.unlock();
	}
	
	void ResourceManager::threadFunction() noexcept{
		while(true){
			m_working.lock();
			if(not m_working()){
				m_working.unlock();
				return;
			}
			m_working.unlock();
			
			m_queue.lock();
			if(not m_queue().empty()){
				Path p = m_queue().front().first;
				Type t = m_queue().front().second;
				m_queue().pop();
				m_queue.unlock();
				
				if(t == Texture)
					texturesFromPath(p);
				else if(t == Sound)
					soundsFromPath(p);
				else if(t == Shader)
					shadersFromPath(p);
				else if(t == Font)
					fontsFromPath(p);
			}
			else
				m_queue.unlock();
		}
	}
	
	ResourceManager::ResourceManager() : m_thread([&]{threadFunction();}){
		m_working.lock();
		m_working() = true;
		m_working.unlock();
	}
	
	ResourceManager::~ResourceManager(){
		m_working.lock();
		m_working() = false;
		m_working.unlock();
		m_thread.join();
	}
}