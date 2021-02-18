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

#include "entryPoint.hpp"

namespace c6{
	void EntryPoint::setDefaultTemplate(const std::string& name, Extensionable* extensionable){
		m_defaultTemplates[name] = extensionable;
	}
	
	void EntryPoint::addTemplate(const std::string& name, Extensionable* extensionable){
		m_templates[name] = extensionable;
	}
	
	bool EntryPoint::tryAddTemplate(const std::string& name, Extensionable* extensionable){
		if(m_templates.count(name) != 0)
			return false;
		addTemplate(name, extensionable);
		return true;
	}
	
	bool EntryPoint::removeTemplate(const std::string& name){
		if(m_templates.count(name) == 0)
			return false;
		delete m_templates[name];
		m_templates[name] = nullptr;
		m_templates.erase(name);
		return true;
	}
	
	EntryPoint::~EntryPoint(){
		for(auto& t : m_templates){
			delete t.second;
			t.second = nullptr;
		}
		for(auto& t : m_defaultTemplates){
			delete t.second;
			t.second = nullptr;
		}
		m_templates.clear();
		m_defaultTemplates.clear();
	}
}