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

#include <set>
#include <queue>
#include <memory>
#include "listener.hpp"

namespace c6{
	template<class Event>
	class Emitter{
		private:
			std::set<Listener<Event>*> listeners;
			std::queue<Event> eventQueue;
		public:
			void notify(const Event& event) noexcept requires std::is_copy_constructible_v<Event> {
				eventQueue.push(event);
			}
			
			void notify(Event&& event) noexcept requires std::is_move_constructible_v<Event> {
				eventQueue.emplace(std::forward<Event>(event));
			}
			
			void forceNotify(const Event& event) noexcept{
				for(auto l : listeners){
					l->onNotify(event);
				}
			}
			
			void processEvents() noexcept{
				while(!eventQueue.empty()){
					for(auto l : listeners){
						l->onNotify(eventQueue.front());
					}
					eventQueue.pop();
				}
			}
			
			/**
			 * Adds listener to the emmiter's notify list.<br>
			 * Unless manually erased, the emmiter will clean added listener during it's destruction.
			 * @param listener
			 */
			void addListener(Listener<Event>* listener) noexcept{
				listeners.insert(listener);
			}
			
			void removeListener(Listener<Event>* listener) noexcept{
				listeners.erase(listener);
			}
			
			void removeAllListeners() noexcept{
				listeners.clear();
			}
			
			[[nodiscard]]
			size_t listenerCount() const noexcept{
				return listeners.size();
			}
			
			[[nodiscard]]
			size_t eventCount() const noexcept{
				return eventQueue.size();
			}
			
			virtual ~Emitter(){
				for(Listener<Event>* listener : listeners){
					delete listener;
				}
			}
	};
}