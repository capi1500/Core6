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

#include "nonCopyable.hpp"
#include <type_traits>

namespace c6{
	/**
	 * @brief Implementation of Singleton pattern.<br>
	 * Usage:<br>
	 * @code
	 * class Foo : public c6::Singleton&#60;Foo&#62;{
	 *     ...
	 * };
	 * @endcode
	 * @tparam T - the class that is a Singleton
	 */
	template<class T>
	class Singleton : public NonCopyable{
		protected:
			Singleton() = default;
		public:
			/**
			 * Returns the instance of a singleton
			 * @return instance
			 */
			static T& get(){
				static T instance;
				return instance;
			}
	};
}
