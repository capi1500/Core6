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
 *	you must not claim that you wrote the original software.
 *	If you use this software in a product, an acknowledgment
 *	in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *	and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

#include <concepts>
#include <exception>
#include <Core6/utils/callback.hpp>

namespace c6{
	template<class T>
	class Lazy{
		private:
			T* obj = nullptr;
			Function<T*> provider;
			Function<void, T*> destroyer;
		public:
			Lazy() noexcept
			requires std::is_default_constructible_v<T>
					: provider([](){return new T();}), destroyer([](T* ptr){delete ptr;}){}
			
			explicit Lazy(Function<T*> provider) noexcept
			requires std::is_trivially_destructible_v<T>
					: provider(std::move(provider)), destroyer([](T* ptr){delete ptr;}){}
			
			explicit Lazy(Function<void, T*> destroyer) noexcept
			requires std::is_default_constructible_v<T>
					: provider([](){return new T();}), destroyer(std::move(destroyer)){}
			
			Lazy(Function<T> provider, Function<void, T*> destroyer) : provider(std::move(provider)), destroyer(std::move(destroyer)) {}
			
			~Lazy(){
				destroy();
			}
			
			[[nodiscard]]
			bool isCreated() const noexcept{
				return obj != nullptr;
			}
			
			[[nodiscard]]
			T* operator -> (){
				return get();
			}
			
			[[nodiscard]]
			T* get(){
				if(!isCreated())
					create();
				return obj;
			}
			
			void create(){
				if(isCreated())
					destroy();
				obj = provider();
			}
			
			void destroy(){
				if(isCreated()){
					destroyer(obj);
					obj = nullptr;
				}
			}
	};
}

