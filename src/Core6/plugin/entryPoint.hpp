/**
 * Core6
 * Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#include <string>
#include "extensionable.hpp"
#include <Core6/utils/storage.hpp>

namespace c6{
	class EntryPoint{
		private:
			Storage<std::string, Extensionable*> m_defaultTemplates;
			Storage<std::string, Extensionable*> m_templates;
		public:
			void setDefaultTemplate(const std::string& name, Extensionable* extensionable);
			void addTemplate(const std::string& name, Extensionable* extensionable);
			bool tryAddTemplate(const std::string& name, Extensionable* extensionable);
			bool removeTemplate(const std::string& name);
			
			template<class T>
			T* get(const std::string& name){
				if(m_templates.count(name) == 0){
					if(m_defaultTemplates.count(name) == 0)
						return nullptr;
					return dynamic_cast<T*>(m_defaultTemplates[name])->clone();
				}
				return dynamic_cast<T*>(m_templates[name])->clone();
			}
			
			~EntryPoint();
	};
}

#endif //CORE6_ENTRYPOINT_HPP
