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

#ifndef CORE6_PLUGIN_HPP
#define CORE6_PLUGIN_HPP

#ifdef WIN32
#include <windows.h>
#endif
#include <string>
#include "package.hpp"

namespace c6{
	class Plugin{
		private:
			#ifdef WIN32
			HINSTANCE m_lib;
			#endif
			Package* m_package;
		public:
			bool load(const std::string& path);
			
			void unload();
			
			template<typename T>
			T getFunction(const std::string& name){
				auto out = (T)GetProcAddress(m_lib, name.c_str());
				if(!out){
					Framework::getMessage()->send(Message("cannot retrieve function address '" + name + "'", MessageType::Error));
					return nullptr;
				}
				return out;
			}
			
			Plugin();
			
			~Plugin();
	};
}

#endif //CORE6_PLUGIN_HPP
