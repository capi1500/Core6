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

#include "stateEvent.hpp"

namespace c6{
	StateEvent::StateEvent(StateEvent::Type type, std::optional<State*> newState, std::optional<unsigned int> removeCount) noexcept : type(type), newState(newState), removeCount(removeCount){
	
	}
	
	StateEvent StateEvent::add(State* state) noexcept{
		return StateEvent(StateEvent::Add, std::optional(state), std::nullopt);
	}
	
	StateEvent StateEvent::pop(unsigned int removeCount) noexcept{
		return StateEvent(StateEvent::Pop, std::nullopt, std::optional(removeCount));
	}
	
	StateEvent StateEvent::replace(State* state) noexcept{
		return StateEvent(StateEvent::Replace, std::optional(state), std::nullopt);
	}
	
	StateEvent StateEvent::clear() noexcept{
		return StateEvent(StateEvent::Clear, std::nullopt, std::nullopt);
	}
	
	StateEvent::Type StateEvent::getType() const noexcept{
		return type;
	}
	
	State* StateEvent::getNewState() const{
		return newState.value();
	}
	
	unsigned int StateEvent::getRemoveCount() const{
		return removeCount.value();
	}
}