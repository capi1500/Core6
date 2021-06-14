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
#include <Core6/systems/console.hpp>

namespace c6{
	class Plugin{
		private:
			#ifdef WIN32
			HINSTANCE m_lib;
			#endif
			Package* m_package;
		public:
			bool load(const std::string& path){
				Console::send(Message("Plugin: Loading plugin from path '" + path + "'", MessageType::Debug));
				#ifdef WIN32
				if(m_lib){
					Console::send(Message("Plugin: Plugin already loaded", MessageType::Error));
					return false;
				}
				m_lib = LoadLibrary(path.c_str());
				if(!m_lib){
					Console::send(Message("Plugin: Cannot find plugin at '" + path + "'", MessageType::Error));
					return false;
				}
				typedef Package*(*__stdcall fun)();
				#else
				typedef Package* (*fun)();
				#endif
				auto create = getFunction<fun>("create");
				if(!create)
					return false;
				m_package = create();
				m_package->onLoad();
				Console::send(Message("Plugin: Loaded plugin " + m_package->name() + " from path '" + path + "'", MessageType::Debug));
				return true;
			}
			
			void unload(){
				Console::send(Message("Plugin: Unloading plugin", MessageType::Debug));
				if(m_package != nullptr){
					m_package->onUnLoad();
					delete m_package;
					m_package = nullptr;
				}
				#ifdef WIN32
				if(!m_lib){
					Console::send(Message("Plugin: plugin not loaded, nothing to unload", MessageType::Error));
				}
				else{
					FreeLibrary(m_lib);
					m_lib = nullptr;
				}
				#else
				#endif
			}
			
			template<class T>
			requires std::is_invocable_v<T>
			T getFunction(const std::string& name){
				#pragma GCC diagnostic push
				#pragma GCC diagnostic ignored "-Wcast-function-type"
				T out = reinterpret_cast<T>(GetProcAddress(m_lib, name.c_str()));
				#pragma GCC diagnostic pop
				if(!out){
					Console::send(Message("Plugin: Cannot retrieve function address '" + name + "'", MessageType::Error));
					return nullptr;
				}
				return out;
			}
			
			Plugin(){
				#ifdef WIN32
				m_lib = nullptr;
				#else
				#endif
				m_package = nullptr;
			}
			
			~Plugin(){
				Console::send(Message("Plugin: Destroying", MessageType::Debug));
				#ifdef WIN32
				if(m_lib)
					unload();
				#else
				#endif
				Console::send(Message("Plugin: Destroyed", MessageType::Debug));
			}
	};
}

#endif //CORE6_PLUGIN_HPP
