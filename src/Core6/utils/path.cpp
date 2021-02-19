//
// Created by Kacper on 24/11/2020.
//

#include "path.hpp"

namespace c6{
	bool Path::isFile(const std::string& ext) const{
		if(ext != "" and m_path.extension() != ext)
			return false;
		return fs::is_regular_file(m_path);
	}
	
	bool Path::isDirectory() const{
		return fs::is_directory(m_path);
	}
	
	Path::Path(const std::string& path) : m_path(path){
	}
	
	const std::string Path::getPath() const{
		return m_path.string();
	}
}