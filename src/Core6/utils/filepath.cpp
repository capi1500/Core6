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

#include "filepath.hpp"

namespace c6{
	bool Filepath::isFile(const std::string& ext) const noexcept{
		if(!ext.empty() and path.extension() != ext)
			return false;
		return fs::is_regular_file(path);
	}
	
	bool Filepath::isDirectory() const noexcept{
		return fs::is_directory(path);
	}
	
	Filepath::Filepath(const std::string& path) noexcept : path(path){}
	
	Filepath::Filepath(const char* path) noexcept : path(path){}
	
	std::string Filepath::toString(fs::path p) noexcept{
		std::string out = p.string();
		std::replace(out.begin(), out.end(), '\\', '/');
		return out;
	}
	
	const std::string Filepath::getPath() const noexcept{
		return toString(path);
	}
}