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

#include <Core6/framework.hpp>
#include "plugin.hpp"

namespace c6{
	bool Plugin::load(const std::string& path){
		#ifdef WIN32
		if(m_lib){
			Framework::getMessage()->send(Message("library already loaded", MessageType::Error));
			return false;
		}
		m_lib = LoadLibrary(path.c_str());
		if(!m_lib){
			Framework::getMessage()->send(Message("cannot find library at '" + path + "'", MessageType::Error));
			return false;
		}
		#else
		typedef Package* (*fun)();
		#endif
		typedef Package*(*__stdcall fun)();
		auto create = getFunction<fun>("create");
		if(!create)
			return false;
		m_package = create();
		m_package->onLoad();
		return true;
	}
	
	void Plugin::unload(){
		if(m_package != nullptr){
			m_package->onUnLoad();
			delete m_package;
		}
		#ifdef WIN32
		if(!m_lib){
			Framework::getMessage()->send(Message("library not loaded, nothing to unload", MessageType::Error));
		}
		else
			FreeLibrary(m_lib);
		#else
		#endif
	}
	
	Plugin::Plugin(){
		#ifdef WIN32
		m_lib = nullptr;
		#else
		#endif
		m_package = nullptr;
	}
	
	Plugin::~Plugin(){
		#ifdef WIN32
		if(m_lib)
			unload();
		#else
		#endif
	}
}