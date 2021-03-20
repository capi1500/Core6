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

#ifndef CORE6_PACKAGE_HPP
#define CORE6_PACKAGE_HPP

#ifdef WIN32
#define API __declspec(dllexport) __stdcall
#else
#define API
#endif

#include "entryPoint.hpp"

namespace c6{
	class Package{
		protected:
			template<std::copyable T>
			void registerTemplate(const std::string& name, T* element){
				EntryPoint::addTemplate(name, element);
			}
		public:
			virtual std::string name() = 0;
			virtual void onLoad() = 0;
			virtual void onUnLoad() = 0;
			virtual ~Package() = default;
	};
}

#endif //CORE6_PACKAGE_HPP
