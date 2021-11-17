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
#include <concepts>
namespace c6{
	/**
	 * @brief Function is a function wrapper that can be chained with other functions as well as composed.
	 * @tparam R return type
	 * @tparam Args argument types
	 */
	template<class R, class... Args>
	using Function = std::function<R(Args...)>;
	
	using Runnable = std::function<void()>;
	
	template<class R>
	using Provider = Function<R>;
	
	template<class T>
	using Destroyer = Function<void, T*>;
	
	template<class T>
	using Consumer = Function<void, T>;

	template<class T>
	using Transmuter = Function<void, T&>;
	
	template<class... Args>
	using Predicate = Function<bool, Args...>;
}

template<class F>
inline auto compose(F f){
	return f;
}

template<class F, class... Args>
inline auto compose(F f, Args... args){
	return [f, args...](auto... param){
		return f(compose(args...)(param...));
	};
}

template<class F, class G>
inline auto operator * (F f, G g){
	return compose(f, g);
}

template<class F>
inline auto chain(F f){
	return f;
}

template<class F, class... Args>
inline auto chain(F f, Args... args){
	return [f, args...](auto... param){
		f(param...);
		chain(args...)(param...);
	};
}

template<class F, class G>
inline auto operator | (F f, G g){
	return chain(f, g);
}

template<class T>
requires std::is_same_v<T, bool>
inline bool any(T t){
	return t;
}

template<class F>
requires std::is_invocable_r_v<bool, F>
inline bool any(F f){
	return f();
}

template<class F, class... Args>
requires std::is_invocable_r_v<bool, F>
inline bool any(F f, Args... args);

template<class T, class... Args>
requires std::is_same_v<T, bool>
inline bool any(T t, Args... args){
	return t || any<Args...>(args...);
}

template<class F, class... Args>
requires std::is_invocable_r_v<bool, F>
inline bool any(F f, Args... args){
	return f() || any<Args...>(args...);
}

template<class T>
requires std::is_same_v<T, bool>
inline bool all(T t){
	return t;
}

template<class F>
requires std::is_invocable_r_v<bool, F>
inline bool all(F f){
	return f();
}

template<class F, class... Args>
requires std::is_invocable_r_v<bool, F>
inline bool all(F f, Args... args);

template<class T, class... Args>
requires std::is_same_v<T, bool>
inline bool all(T t, Args... args){
	return t && all<Args...>(args...);
}

template<class F, class... Args>
requires std::is_invocable_r_v<bool, F>
inline bool all(F f, Args... args){
	return f() and all<Args...>(args...);
}

template<class F, class T>
requires std::is_invocable_v<F, T>
void forall(F f, T t){
	f(t);
}

template<class F, class T, class... Args>
requires std::is_invocable_v<F, T>
void forall(F f, T t, Args... args){
	f(t);
	forall(f, args...);
}

void forall(auto f, auto lst){
	for(auto x : lst)
		f(x);
}

template<class F, class T>
requires std::is_invocable_v<F, T>
void foldLeft(F f, T t){
	f(t);
}

template<class F, class T, class... Args>
requires std::is_invocable_v<F, T>
void foldLeft(F f, T t, Args... args){
	f(t);
	forall(f, args...);
}

void foldLeft(auto f, auto lst){
	for(auto x : lst)
		f(x);
}


