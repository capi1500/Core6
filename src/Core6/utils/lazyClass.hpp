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

#ifndef CORE6_LAZYCLASS_HPP
#define CORE6_LAZYCLASS_HPP

#include <iostream>
#include "commonFunctions.hpp"

namespace c6{
	template<typename T, auto... TDefaultArgs>
	requires concepts::CreatableArgs<T, TDefaultArgs...>
	class LazyClass{
		private:
			T* t;
		public:
			template<class... Args>
			requires concepts::CreatableTypes<T, Args...>
			void create(Args... args){
				if(isCreated())
					destroy();
				t = new T(args...);
			}
			
			void defaultCreate(){
				if(isCreated())
					destroy();
				t = new T(TDefaultArgs...);
			}
			
			void destroy(){
				if(t != nullptr){
					delete t;
					t = nullptr;
				}
			}
			
			bool isCreated(){
				return t != nullptr;
			}
			
			T& operator ()(){
				if(not isCreated())
					defaultCreate();
				return *t;
			}
			
			const T& operator ()() const{
				if(not isCreated())
					defaultCreate();
				return *t;
			}
			
			LazyClass(){
				t = nullptr;
			}
			
			~LazyClass(){
				destroy();
			}
	};
}

#endif //CORE6_LAZYCLASS_HPP
