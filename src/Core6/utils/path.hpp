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

#include <experimental/filesystem>

namespace c6{
	namespace fs = std::experimental::filesystem;
	
	/**
	 * @brief wrapper around std::filesystem, represents a path to file/directory
	 */
	class Path{
		private:
			fs::path m_path;
			
			std::string toString(fs::path p) const;
		public:
			/**
			 * @brief Check wheter path is a file
			 * @param ext - (optional) checks if a file has extention [ext]
			 * @return returns true if path is a file (with extention [ext])
			 */
			bool isFile(const std::string& ext = "") const;
			
			/**
			 * @brief Checks wheter path is a directory
			 * @return returns true if path is a directory
			 */
			bool isDirectory() const;
			
			/**
			 * @brief Executes function on file(s) with extension [ext]
			 * @tparam F - function type, must provide 'operator ()' that takes one argument (path to file) 'std::string' or 'const std::string&' and return void.
			 * @param f - function to execute on file(s), see template parameter above for more informations
			 * @param recursive - (optional, default = false) when true and if path is directory, execute [f] recursively
			 * @param ext - (optional) executes [f] only on files with [ext] extension
			 */
			template<class F>
			requires std::is_invocable_v<F, std::string>
			void execute(F f, bool recursive = false, const std::string& ext = "") const{
				if(not m_path.empty()){
					if(isDirectory()){
						if(recursive){
							for(auto& p : fs::recursive_directory_iterator(m_path)){
								if(Path(p.path().string()).isFile(ext))
									f(toString(p.path()));
							}
						}
						else{
							for(auto& p : fs::directory_iterator(m_path)){
								if(Path(p.path().string()).isFile(ext))
									f(toString(p.path()));
							}
						}
					}
					if(isFile(ext))
						f(getPath());
				}
			}
			
			/**
			 * @bried get path
			 * @return path as string
			 */
			const std::string getPath() const;
			
			/**
			 * @brief Creates path from string
			 * @param path - path in string
			 */
			Path(const std::string& path);
	};
}
