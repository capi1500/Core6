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
#include <Core6/base/interfaces/provider.hpp>
#include <Core6/base/interfaces/destroyer.hpp>

namespace c6{
	template<class T, class P = ProviderInline<T*>, class D = DestroyerSimple<T>>
	requires (std::is_base_of_v<Provider<T*>, P> && std::is_base_of_v<Destroyer<T>, D>)
	class Lazy{
		private:
			T* obj = nullptr;
			P provider;
			D destroyer;
		public:
			Lazy() noexcept
			requires (std::is_default_constructible_v<T> && std::is_same_v<ProviderInline<T*>, P>)
			        : provider([](){return new T();}), destroyer(){}
			
			explicit Lazy(P provider) noexcept
			requires std::is_default_constructible_v<D>
			        : provider(provider), destroyer(){}
			
			explicit Lazy(D destroyer) noexcept
			requires std::is_default_constructible_v<P>
			        : provider(), destroyer(destroyer){}
			
			Lazy(P provider, D destroyer) : provider(provider), destroyer(destroyer) {}
			
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

