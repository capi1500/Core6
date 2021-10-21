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

#include <functional>

namespace c6{
	/**
	 * Implementation of factory design pattern
	 * @tparam T - created type
	 */
	template<class T>
	class Factory{
		public:
			template<class... TArgs>
			virtual T create(const TArgs&... args) const noexcept = 0;
			
			virtual ~Factory() = default;
	};
	
	template<class T, class... TArgs>
	class SimpleFactory : public Factory<T>{
			using Supplier = std::function<T(TArgs...)>;
		private:
			Supplier supplier;
		public:
			T create(const TArgs&... args) const noexcept final{
				return supplier(args...);
			}
			
			explicit SimpleFactory(const Supplier& supplier) : supplier(supplier) {}
			explicit SimpleFactory(Supplier&& supplier) : supplier(std::forward<>(supplier)) {}
	};
}


