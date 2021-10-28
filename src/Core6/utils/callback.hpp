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
	 * @brief Callback is a function wrapper that can be chained with other callbacks as well as composed.
	 * @tparam R return type
	 * @tparam Args argument types
	 */
	template<class R, class... Args>
	class Callback{
		public:
			using Function = std::function<R(Args...)>;
		private:
			Function function;
		public:
			/**
			 * @brief If R is void then creates a callback that does nothing
			 */
			Callback() noexcept requires std::is_same_v<R, void> : function([](Args... args){}){}
			/**
			 * @brief If R is constructible from Args then creates a callback that creates R from args
			 */
			Callback() noexcept requires std::is_constructible_v<R, Args...> : function([](Args... args){return R(args...);}){}
			/**
			 * @brief Creates a callback from a std::function
			 * @param function function
			 */
			Callback(Function function) noexcept : function(std::move(function)){}
			
			inline R call(Args... args) const{
				return function(args...);
			}
			
			inline R operator () (Args... args) const{
				return call(args...);
			}
			
			template<class R2, class... Args2>
			inline Callback<R2, Args..., Args2...> chain(const Callback<R2, Args2...>& callNext) noexcept{
				return [this, &callNext](Args... args, Args2... args2){
					function(args...);
					return callNext(args2...);
				};
			}
			
			template<class R2, class... Args2>
			inline Callback<R2, Args..., Args2...> operator | (const Callback<R2, Args2...>& callNext) noexcept{
				return chain(callNext);
			}
			
			template<class R2>
			inline Callback<R2, Args...> compose(const Callback<R2, R>& compose) noexcept{
				return [this, &compose](Args... args){
					return compose(function(args...));
				};
			}
			
			template<class R2>
			inline Callback<R2, Args...> operator * (const Callback<R2, R>& compose) noexcept{
				return this->compose(compose);
			}
	};
	
	template<class R>
	using Provider = Callback<R>;
	
	template<class T>
	using Destroyer = Callback<void, T*>;
	
	template<class T>
	using Consumer = Callback<void, T>;

	template<class T>
	using Transmuter = Callback<void, T&>;
}

