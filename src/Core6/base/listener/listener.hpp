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

#include <Core6/utils/functional.hpp>

namespace c6{
	/**
	 * Class that listens to a particular Event and executes a function on that event
	 * @tparam Event
	 */
	template<class Event>
	class Listener{
		public:
			virtual void onNotify(const Event& event) noexcept = 0;
			
			virtual ~Listener() noexcept = default;
	};
	
	/**
	 * Class that listens to a particular Event and executes a function on that event
	 * @tparam Event
	 */
	template<class Event>
	class SimpleListener : public Listener<Event>{
		private:
			const Consumer<const Event&> f_;
		public:
			void onNotify(const Event& event) noexcept final{
				f_(event);
			}
			
			explicit SimpleListener(const Consumer<const Event&>& f) noexcept : f_(f) {}
			explicit SimpleListener(Consumer<const Event&>&& f) noexcept : f_(std::move(f)) {}
	};
}
