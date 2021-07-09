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

#include <type_traits>
#include <mutex>

namespace c6{
	/*template<class T>
	class Concurrent{
			class LockedObject{
				public:
					LockedObject(T& object, Mutex& lock) noexcept : object(*object), m_lock(lock){
					}
					
					inline LockedObject(LockedObject&& move) noexcept : object(std::move(move.object)), lock(std::move(move.lock)){}
					
					inline auto operator ->() noexcept{
						return object;
					}
					
					inline auto operator ->() const noexcept{
						return object;
					}
				
				private:
					T* object;
					std::unique_lock<std::recursive_mutex> lock;
			};
		private:
			mutable std::recursive_mutex mutex;
			T wrapped;
		public:
			template<class... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
			explicit Concurrent(Args&&... args) : mutex(), wrapped{std::forward<Args>(args)...}{}
			
			template<class... Args, typename = std::enable_if_t <std::is_constructible_v<T, Args...>>>
			explicit Concurrent(std::recursive_mutex m, Args&&... args) : mutex(std::move(m)), wrapped{std::forward<Args>(args) ...}{}
			
			explicit Concurrent(Concurrent move) : mutex(std::move(move.mutex)), wrapped(std::move(move.wrapped)){}
			
			virtual ~Concurrent(){
			
			}
			
			// used for several actions
			
			[[nodiscard]] inline LockedObject operator *(){
				return LockedObject(&wrapped, mutex);
			}
			
			[[nodiscard]] inline LockedObject operator *() const{
				return LockedObject(&wrapped, mutex);
			}
			
			// synchronized operations
			
			inline auto operator ->(){
				LockedObject obj(&wrapped, mutex);
				return obj;
			}
			
			inline auto operator ->() const{
				LockedObject obj(&wrapped, mutex);
				return obj;
			}
	};*/
}

