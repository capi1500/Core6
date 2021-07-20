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

#include <iostream>
#include "resourceManager.hpp"

namespace c6{
	void ResourceManager::addTexture(const Path& path) noexcept{
		message("Loading texture " + path.getPath() + " from path: " + path.getPath(), Message::Loading);
		if(textures[path.getPath()].loadFromFile(path.getPath()))
			message("Loaded texture " + path.getPath() + " from path: " + path.getPath(), Message::Loading);
		else
			message("Cannot load texture " + path.getPath() + " from path: " + path.getPath(), Message::Error);
	}
	
	void ResourceManager::addTexture(const std::string& name, const Path& path) noexcept{
		message("Loading texture " + name + " from path: " + path.getPath(), Message::Loading);
		if(textures[name].loadFromFile(path.getPath()))
			message("Loaded texture " + name + " from path: " + path.getPath(), Message::Loading);
		else
			message("Cannot load texture " + name + " from path: " + path.getPath(), Message::Error);
	}
	
	void ResourceManager::removeTexture(const std::string& name) noexcept{
		textures.erase(name);
	}
	
	const sf::Texture& ResourceManager::getTexture(const std::string& name) const noexcept{
		return textures.at(name);
	}
	
	bool ResourceManager::hasTexture(const std::string& name) const noexcept{
		return textures.contains(name);
	}
	
	void ResourceManager::addSound(const Path& path) noexcept{
		sounds[path.getPath()].loadFromFile(path.getPath());
	}
	
	void ResourceManager::addSound(const std::string& name, const Path& path) noexcept{
		sounds[name].loadFromFile(path.getPath());
	}
	
	void ResourceManager::removeSound(const std::string& name) noexcept{
		sounds.erase(name);
	}
	
	const sf::SoundBuffer& ResourceManager::getSound(const std::string& name) const noexcept{
		return sounds.at(name);
	}
	
	bool ResourceManager::hasSound(const std::string& name) const noexcept{
		return sounds.contains(name);
	}
	
	void ResourceManager::addShader(const Path& path, sf::Shader::Type type) noexcept{
		shaders[path.getPath()].loadFromFile(path.getPath(), type);
	}
	
	void ResourceManager::addShader(const std::string& name, const Path& path, const sf::Shader::Type type) noexcept{
		shaders[name].loadFromFile(path.getPath(), type);
	}
	
	void ResourceManager::removeShader(const std::string& name) noexcept{
		shaders.erase(name);
	}
	
	const sf::Shader& ResourceManager::getShader(const std::string& name) const noexcept{
		return shaders.at(name);
	}
	
	bool ResourceManager::hasShader(const std::string& name) const noexcept{
		return shaders.contains(name);
	}
	
	void ResourceManager::addFont(const Path& path) noexcept{
		fonts[path.getPath()].loadFromFile(path.getPath());
	}
	
	void ResourceManager::addFont(const std::string& name, const Path& path) noexcept{
		fonts[name].loadFromFile(path.getPath());
	}
	
	void ResourceManager::removeFont(const std::string& name) noexcept{
		fonts.erase(name);
	}
	
	const sf::Font& ResourceManager::getFont(const std::string& name) const noexcept{
		return fonts.at(name);
	}
	
	bool ResourceManager::hasFont(const std::string& name) const noexcept{
		return fonts.contains(name);
	}
	
	void ResourceManager::addMusic(const Path& path) noexcept{
		music[path.getPath()].openFromFile(path.getPath());
	}
	
	void ResourceManager::addMusic(const std::string& name, const Path& path) noexcept{
		music[name].openFromFile(path.getPath());
	}
	
	void ResourceManager::removeMusic(const std::string& name) noexcept{
		music[name].stop();
		music.erase(name);
	}
	
	const sf::Music& ResourceManager::getMusic(const std::string& name) const noexcept{
		return music.at(name);
	}
	
	bool ResourceManager::hasMusic(const std::string& name) const noexcept{
		return music.contains(name);
	}
	
	void ResourceManager::loadTextures(const Path& path) noexcept{
		for(auto ext : {"bmp", "png", "tga", "jpg", "gif", "psd", "hdr", "pic"}){
			path.execute([&](const std::string& path){
				addTexture(path);
			}, true, std::string(".") + ext);
		}
	}
	
	void ResourceManager::loadSounds(const Path& path) noexcept{
		for(auto ext : {"wav", "ogg", "flac"}){
			path.execute([&](const std::string& path){
				addSound(path);
			}, true, std::string(".") + ext);
		}
	}
	
	void ResourceManager::loadShaders(const Path& path) noexcept{
		path.execute([&](const std::string& path){
			addShader(path, sf::Shader::Fragment);
		}, true, ".frag");
		path.execute([&](const std::string& path){
			addShader(path, sf::Shader::Vertex);
		}, true, ".vert");
		path.execute([&](const std::string& path){
			addShader(path, sf::Shader::Geometry);
		}, true, ".geom");
	}
	
	void ResourceManager::loadFonts(const Path& path) noexcept{
		for(auto ext : {"ttf", "otf", "cff", "pfb", "pfm", "afm", "aat", "sil", "fon", "bdf", "pfr", }){
			path.execute([&](const std::string& path){
				addFont(path);
			}, true, std::string(".") + ext);
		}
	}
}