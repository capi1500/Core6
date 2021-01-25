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

#ifndef CORE6_SIGNAL_HPP
#define CORE6_SIGNAL_HPP

#include <queue>
#include <map>
#include "listener.hpp"

namespace c6{
	template <class T>
	class Signal{
		private:
			std::map<Listener<T>*, bool> m_listeners;
			std::queue<T> m_eventQueue;
		public:
			void send(const T& signal){
				m_eventQueue.push(signal);
			}
			
			void processEvents(){
				while(not m_eventQueue.empty()){
					T& e = m_eventQueue.front();
					m_eventQueue.pop();
					for(auto l : m_listeners){
						l.first->onSignal(e);
					}
				}
			}
			
			void add(Listener<T>* listener, bool owner = false){
				m_listeners[listener] = owner;
			}
			
			void remove(Listener<T>* listener){
				auto it = m_listeners.find(listener);
				if(it != m_listeners.end()){
					if(it->second){
						delete it->first;
					}
					m_listeners.erase(it);
				}
			}
			
			void removeAll(){
				for(auto it : m_listeners){
					if(it->second)
						delete it->first;
				}
				m_listeners.clear();
			}
			
			const size_t count() const{
				return m_listeners.size();
			}
	};
}

#endif //CORE6_SIGNAL_HPP
