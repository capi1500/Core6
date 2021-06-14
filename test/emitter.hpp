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

#include <gtest/gtest.h>
#include <listener/emitter.hpp>
#include "../../Core6/src/Core6/base/nonCopyable.hpp"
#include "../../Core6/src/Core6/base/nonMovable.hpp"

class EmitterTest : public testing::Test{
	protected:
		static int test;
		
		struct Event{
			int x;
		};
		
		struct NonCopyableEvent : public c6::NonCopyable{
			int x;
		};
		
		struct NonMovableEvent : public c6::NonMovable{
			int x;
			/*NonMovableEvent(const NonMovableEvent&) = default;
			NonMovableEvent(NonMovableEvent&&) = delete;
			
			NonMovableEvent& operator = (const NonMovableEvent&) = default;
			NonMovableEvent& operator = (NonMovableEvent&&) = delete;
			
			NonMovableEvent() = default;*/
		};
		
		template<class Event>
		class OverrideListener : public c6::Listener<Event>{
			public:
				void onNotify(const Event& event) const noexcept override{
					test += event.x;
				}
		};
		
		c6::Emitter<Event> emitter;
		c6::Emitter<NonCopyableEvent> nonCopyableEmitter;
		c6::Emitter<NonMovableEvent> nonMovableEmitter;
		
		c6::SimpleListener<Event> listener1 = c6::SimpleListener<Event>([&](const Event& event){ test += event.x; });
		OverrideListener<Event> listener2;
		
		c6::SimpleListener<NonCopyableEvent> nonCopyableListener1 = c6::SimpleListener<NonCopyableEvent>([&](const NonCopyableEvent& event){ test += event.x; });;
		OverrideListener<NonCopyableEvent> nonCopyableListener2;
		
		c6::SimpleListener<NonMovableEvent> nonMovableListener1 = c6::SimpleListener<NonMovableEvent>([&](const NonMovableEvent& event){ test += event.x; });;
		OverrideListener<NonMovableEvent> nonMovableListener2;
		
		void SetUp() override{
			test = 0;
		}
		
		void TearDown() override{
			emitter.removeAllListeners();
			nonCopyableEmitter.removeAllListeners();
			nonMovableEmitter.removeAllListeners();
		}
};

int EmitterTest::test = 0;

TEST_F(EmitterTest, ForceNotifySimpleTest){
	Event event{};
	event.x = 2;
	ASSERT_EQ(test, 0);
	emitter.forceNotify(event);
	ASSERT_EQ(test, 0);
	emitter.addListener(listener1);
	ASSERT_EQ(test, 0);
	emitter.forceNotify(event);
	ASSERT_EQ(test, 2);
	emitter.addListener(listener2);
	ASSERT_EQ(test, 2);
	emitter.forceNotify(event);
	ASSERT_EQ(test, 6);
}

TEST_F(EmitterTest, ForceNotifyNonCopyableTest){
	NonCopyableEvent event;
	event.x = 2;
	ASSERT_EQ(test, 0);
	nonCopyableEmitter.forceNotify(event);
	ASSERT_EQ(test, 0);
	nonCopyableEmitter.addListener(nonCopyableListener1);
	ASSERT_EQ(test, 0);
	nonCopyableEmitter.forceNotify(event);
	ASSERT_EQ(test, 2);
	nonCopyableEmitter.addListener(nonCopyableListener2);
	ASSERT_EQ(test, 2);
	nonCopyableEmitter.forceNotify(event);
	ASSERT_EQ(test, 6);
}

TEST_F(EmitterTest, ForceNotifyNonMovableTest){
	NonMovableEvent event;
	event.x = 2;
	ASSERT_EQ(test, 0);
	nonMovableEmitter.forceNotify(event);
	ASSERT_EQ(test, 0);
	nonMovableEmitter.addListener(nonMovableListener1);
	ASSERT_EQ(test, 0);
	nonMovableEmitter.forceNotify(event);
	ASSERT_EQ(test, 2);
	nonMovableEmitter.addListener(nonMovableListener2);
	ASSERT_EQ(test, 2);
	nonMovableEmitter.forceNotify(event);
	ASSERT_EQ(test, 6);
}

TEST_F(EmitterTest, NotifySimpleTest){
	Event event;
	event.x = 2;
	Event event2;
	event2.x = 3;
	ASSERT_EQ(test, 0);
	emitter.addListener(listener1);
	emitter.addListener(listener2);
	emitter.notify(event);
	emitter.notify(std::move(event2));
	ASSERT_EQ(test, 0);
	emitter.processEvents();
	ASSERT_EQ(test, 10);
}

TEST_F(EmitterTest, NotifyNonCopyableTest){
	NonCopyableEvent event;
	event.x = 2;
	ASSERT_EQ(test, 0);
	nonCopyableEmitter.addListener(nonCopyableListener1);
	nonCopyableEmitter.addListener(nonCopyableListener2);
	nonCopyableEmitter.notify(std::move(event));
	
	//NonCopyableEvent event2;
	//event2.x = 3;
	//nonCopyableEmitter.notify(event2); // ERROR NonCopyable
	
	ASSERT_EQ(test, 0);
	nonCopyableEmitter.processEvents();
	ASSERT_EQ(test, 4);
}

TEST_F(EmitterTest, NotifyNonMovableTest){
	NonMovableEvent event;
	event.x = 2;
	ASSERT_EQ(test, 0);
	nonMovableEmitter.addListener(nonMovableListener1);
	nonMovableEmitter.addListener(nonMovableListener2);
	nonMovableEmitter.notify(event);
	
	NonMovableEvent event2;
	event2.x = 3;
	nonMovableEmitter.notify(std::move(event2));
	
	ASSERT_EQ(test, 0);
	nonMovableEmitter.processEvents();
	ASSERT_EQ(test, 10);
}