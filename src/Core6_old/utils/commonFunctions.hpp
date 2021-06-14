/**
* Core6
* Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#ifndef CORE6_COMMONFUNCTIONS_HPP
#define CORE6_COMMONFUNCTIONS_HPP

#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <SFML/Window/Mouse.hpp>
#include <Core6/signal/message.hpp>
#include <SFML/Window/Event.hpp>

namespace c6{
	namespace concepts{
		namespace helper{
			class Obj{};
		}
		
		template<typename T> concept Integral = requires{
			std::is_integral_v<T>;
		};
		
		template<class T, auto... Args> concept CreatableArgs = requires{
			T(Args...);
		};
		
		template<class T, class... Args> concept CreatableTypes = requires(Args... args){
			T(args...);
		};
		
		template<typename T> concept Hashable = requires(T a) {
			{ std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
		};
	}
	
	/**
	 * @brief transforms sf::Keyboard::Key to std::string
	 * @param key - a key
	 * @return key in std::string format
	 */
	std::string keyToString(sf::Keyboard::Key key);
	
	/**
	 * @brief transforms sf::Mouse::Button to std::string
	 * @param button - a button
	 * @return button in std::string format
	 */
	std::string buttonToString(sf::Mouse::Button button);
	
	/**
	 * @brief transforms sf::Event to std::string
	 * @param event - an event
	 * @return event in std::string format
	 * TODO not finished
	 */
	Message sfEventToMessage(const sf::Event& event);
	
	namespace Hash{
		const unsigned long long MOD = 1000000007;
		
		const unsigned long long p = 313;
	}
	
	/**
	 * @brief hash functions for strings
	 * @param str - string as std::string or char*
	 * @param pow - (optional, default = 313) power used in hash function, should be a prime number
	 * @param mod - (optional, default = 1000000007) modulo used in hash function, shoulf be a big prime number
	 * @return hash-id of [str] using [pow] and [mod]
	 */
	unsigned long long hash(const std::string& str, unsigned long long pow = Hash::p, unsigned long long mod = Hash::MOD);
	unsigned long long hash(const char str[], unsigned long long pow = Hash::p, unsigned long long mod = Hash::MOD);
	
	/**
	 * @brief get random value between from and to
	 * @tparam T - integral type
	 * @param from - first element of interval
	 * @param to - last element of interval
	 * @return random value between from and to
	 */
	template<concepts::Integral T>
	T rand(T from, T to){
		return std::rand() % (to - from + 1) + from;
	}
	
	/**
	 * @brief get random percentage
	 * @return random floating point number from 0 to 100
	 */
	float randPercentage();
	
	/**
	 * @brief get random angle in radians
	 * @return random floating point angle in radians (from 0 to 2PI)
	 */
	float randAngle();
	
	/**
	 * @brief identity function
	 * @tparam F function type
	 * @param f - function
	 * @return returns [f]
	 */
	template<class F>
	inline auto identity(F f){
		return f;
	}
	
	/**
	 * @brief composes functions [f] and [g]
	 * @tparam F - function type, must take exact same type as G returns
	 * @tparam G - function type, must return exact same type as F takes
	 * @param f - function f
	 * @param g - function g
	 * @return f(g(params)), a lambda campturing parameters of [g]
	 * @see inline auto operator *(F f, G g)
	 */
	template<class F, class G>
	inline auto compose(F f, G g){
		return [f, g](auto... param){
			return f(g(param...));
		};
	}
	
	/**
	 * @brief operator overload of function composing [f] and [g]
	 * @tparam F - function type, must take exact same type as G returns
	 * @tparam G - function type, must return exact same type as F takes
	 * @param f - function f
	 * @param g - function g
	 * @return f(g(params)), a lambda campturing parameters of [g]
	 * @see inline auto compose(F f, G g)
	 */
	template<class F, class G>
	inline auto operator *(F f, G g){
		return compose(f, g);
	}
	
	namespace FunctionH{
		template<unsigned i, class F>
		struct Multi{
			static auto chain(F f){
				return compose(f, Multi<i - 1, F>::chain(f));
			};
		};
		
		template<class F>
		struct Multi<1, F>{
			static auto chain(F f){
				return f;
			};
		};
	}
	
	/**
	 * @brief composes [f] with itself [i] times
	 * @tparam i - number of times to compose [f]
	 * @tparam F - function type, must return the exact same type as it takes
	 * @param f - function f
	 * @return f(f(...f(params)...)), a lambda capturing parameters of [f]
	 * @see inline auto operator ^(F f, unsigned i)
	 */
	template<unsigned i, class F>
	auto compose(F f){
		return FunctionH::Multi<i, F>::chain(f);
	}
	
	/**
	 * @brief operator overload for composing [f] with itself [i] times
	 * @tparam F - function type, must return the exact same type as it takes
	 * @param f - function f
	 * @param i - number of times to compose [f]
	 * @return f(f(...f(params)...)), a lambda capturing parameters of [f]
	 * @see auto compose<unsigned i, class F>(F f)
	 */
	template<class F>
	inline auto operator ^(F f, unsigned i){
		return compose<i>(f);
	}
}

#endif //CORE6_COMMONFUNCTIONS_HPP
