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

#include <bits/stdc++.h>

class NonMovable{
	public:
		NonMovable(const NonMovable&) = default;
		NonMovable(NonMovable&&) = delete;
		
		NonMovable& operator = (const NonMovable&) = default;
		NonMovable& operator = (NonMovable&&) = delete;
		
		NonMovable() = default;
		
		virtual ~NonMovable() = default;
};

class Derived : public NonMovable{

};

template<class T>
class Foo{
	public:
		void fun(const T& t){
			std::cout << "reference\n";
		}
		
		void fun(T&& t) requires std::is_move_constructible_v<T>{
			std::cout << "move\n";
		}
};

int main(){
	NonMovable nonMovable;
	Foo<NonMovable> fooNonMovable;
	fooNonMovable.fun(nonMovable);
	fooNonMovable.fun(std::move(nonMovable));
	
	Derived derived;
	Foo<Derived> fooDerived;
	fooDerived.fun(derived);
	fooDerived.fun(std::move(derived));
}

/*
#include <gtest/gtest.h>
#include "listener.hpp"
#include "emitter.hpp"

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/