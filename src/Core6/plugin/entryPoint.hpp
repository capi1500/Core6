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

#ifndef CORE6_ENTRYPOINT_HPP
#define CORE6_ENTRYPOINT_HPP

#include <iostream>
#include <map>
#include <string>
#include <concepts>
#include <Core6/systems/console.hpp>
#include "extensionable.hpp"

namespace c6{
	class EntryPoint{
		private:
			// TODO, change to c6::Storage
			static std::map<std::string, Extensionable*> m_defaultTemplates;
			static std::map<std::string, Extensionable*> m_templates;
			
			static bool hasNonDefaultTemplate(const std::string& name) noexcept{
				return m_templates.count(name) > 0;
			}
			
			template<std::copyable T>
			requires std::is_base_of_v<Extensionable, T>
			static T* copy(Extensionable* element) noexcept{
				return new T(*static_cast<T*>(element));
			}
		public:
			static bool hasTemplate(const std::string& name) noexcept{
				return m_templates.count(name) + m_defaultTemplates.count(name) > 0;
			}
			
			static bool hasDefaultTemplate(const std::string& name) noexcept{
				return m_defaultTemplates.count(name) > 0;
			}
			
			template<std::copyable T>
			requires std::is_base_of_v<Extensionable, T>
			static void addDefaultTemplate(const std::string& name, T* element) noexcept{
				Console::send(Message("EntryPoint: registering default template " + name, MessageType::Debug));
				if(hasDefaultTemplate(name)){
					Console::send(Message("EntryPoint: destroying default template " + name, MessageType::Debug));
					delete m_defaultTemplates[name];
					m_defaultTemplates[name] = nullptr;
				}
				m_defaultTemplates[name] = element;
				Console::send(Message("EntryPoint: added default template " + name, MessageType::Debug));
			}
			
			template<std::copyable T>
			requires std::is_base_of_v<Extensionable, T>
			static void addTemplate(const std::string& name, T* element) noexcept{
				Console::send(Message("EntryPoint: registering template " + name, MessageType::Debug));
				if(hasNonDefaultTemplate(name)){
					Console::send(Message("EntryPoint: destroying template " + name, MessageType::Debug));
					delete m_templates[name];
					m_templates[name] = nullptr;
				}
				m_templates[name] = element;
				Console::send(Message("EntryPoint: added template " + name, MessageType::Debug));
			}
			
			template<std::copyable T>
			requires std::is_base_of_v<Extensionable, T>
			static T* getTemplate(const std::string& name) noexcept{
				if(not hasTemplate(name))
					Console::send(Message("No template of name '" + name + "' in Entry Point", MessageType::Error));
				if(not hasNonDefaultTemplate(name))
					return copy<T>(m_defaultTemplates[name]);
				return copy<T>(m_templates[name]);
			}
			
			static void destroy() noexcept{
				for(auto& t : m_templates){
					Console::send(Message("EntryPoint: destroying template " + t.first, MessageType::Debug));
					delete t.second;
					t.second = nullptr;
				}
				m_templates.clear();
				for(auto& t : m_defaultTemplates){
					Console::send(Message("EntryPoint: destroying default template " + t.first, MessageType::Debug));
					delete t.second;
					t.second = nullptr;
				}
				m_defaultTemplates.clear();
			}
	};
}

#endif //CORE6_ENTRYPOINT_HPP
