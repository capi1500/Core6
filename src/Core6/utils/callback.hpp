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
	 * @brief Function is a function wrapper that can be chained with other callbacks as well as composed.
	 * @tparam R return type
	 * @tparam Args argument types
	 */
	template<class R, class... Args>
	using Function = std::function<R(Args...)>;
	
	using Callback = std::function<void()>;
	
	template<class R>
	using Provider = Function<R>;
	
	template<class T>
	using Destroyer = Function<void, T*>;
	
	template<class T>
	using Consumer = Function<void, T>;

	template<class T>
	using Transmuter = Function<void, T&>;
	
	template<class R, class... Args, class R2, class... Args2>
	inline auto operator | (const std::function<R(Args...)>& f, const std::function<R2(Args2...)>& g){
		return [&f, &g](Args... args, Args2... args2){
			f(args...);
			if constexpr(!std::is_same_v<R2, void>)
				return g(args2...);
			g(args2...);
			return;
		};
	}
	
	template<class R, class R2, class... Args>
	inline auto operator * (const std::function<R(R2)>& f, const std::function<R2(Args...)>& g){
		return [&f, &g](Args... args){
			if constexpr(!std::is_same_v<R, void>)
				return f(g(args...));
			f(g(args...));
			return;
		};
	}
}

