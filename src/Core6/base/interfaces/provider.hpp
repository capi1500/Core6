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
	template<class T>
	class Provider{
		protected:
			virtual T create() const = 0;
		public:
			T operator () (){
				return create();
			}
			virtual ~Provider() = default;
	};
	
	template<class T>
	class ProviderInline : public Provider<T>{
		private:
			std::function<T()> provider;
		protected:
			T create() const override{
				return provider();
			}
		public:
			ProviderInline(std::function<T()> provider) : provider(provider){}
	};
	
	template<class T>
	requires std::is_default_constructible_v<T>
	class ProviderSimple : public Provider<T>{
		protected:
			T create() const override{
				return T();
			}
	};
}

