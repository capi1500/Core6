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

#include "resourceManager.hpp"

namespace c6{
	void ResourceManager::addTexture(const std::string& name) noexcept{
		textures.lambda([&name](auto& storage){
			storage[name].loadFromFile(name);
		});
	}
	
	void ResourceManager::removeTexture(const std::string& name) noexcept{
		textures.lambda([&name](auto& storage){
			storage.erase(name);
		});
	}
	
	const sf::Texture& ResourceManager::getTexture(const std::string& name) const noexcept{
		while(true){
			if(textures.lambda([&name](auto& storage){return storage.count(name) != 0;}).get()){
				return textures.lambda([&name](auto& storage) -> const sf::Texture&{
					return storage.at(name);
				}).get();
			}
		}
	}
	
	void ResourceManager::addSound(const std::string& name) noexcept{
		sounds.lambda([&name](auto& storage){
			storage[name].loadFromFile(name);
		});
	}
	
	void ResourceManager::removeSound(const std::string& name) noexcept{
		sounds.lambda([&name](auto& storage){
			storage.erase(name);
		});
	}
	
	const sf::SoundBuffer& ResourceManager::getSound(const std::string& name) const noexcept{
		while(true){
			if(sounds.lambda([&name](auto& storage){return storage.count(name) != 0;}).get()){
				return sounds.lambda([&name](auto& storage) -> const sf::SoundBuffer&{
					return storage.at(name);
				}).get();
			}
		}
	}
	
	void ResourceManager::addShader(const std::string& name, const sf::Shader::Type type) noexcept{
		shaders.lambda([&name, &type](auto& storage){
			storage[name].loadFromFile(name, type);
		});
	}
	
	void ResourceManager::removeShader(const std::string& name) noexcept{
		shaders.lambda([&name](auto& storage){
			storage.erase(name);
		});
	}
	
	const sf::Shader& ResourceManager::getShader(const std::string& name) const noexcept{
		while(true){
			if(shaders.lambda([&name](auto& storage){return storage.count(name) != 0;}).get()){
				return shaders.lambda([&name](auto& storage) -> const sf::Shader&{
					return storage.at(name);
				}).get();
			}
		}
	}
	
	void ResourceManager::addFont(const std::string& name) noexcept{
		fonts.lambda([&name](auto& storage){
			storage[name].loadFromFile(name);
		});
	}
	
	void ResourceManager::removeFont(const std::string& name) noexcept{
		fonts.lambda([&name](auto& storage){
			storage.erase(name);
		});
	}
	
	const sf::Font& ResourceManager::getFont(const std::string& name) const noexcept{
		while(true){
			if(fonts.lambda([&name](auto& storage){return storage.count(name) != 0;}).get()){
				return fonts.lambda([&name](auto& storage) -> const sf::Font&{
					return storage.at(name);
				}).get();
			}
		}
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