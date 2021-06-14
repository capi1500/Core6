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
#include <listener/listener.hpp>

class ListenerTest : public testing::Test{
	protected:
		struct Event{};
		
		class Override : public c6::Listener<Event>{
			public:
				void onNotify([[maybe_unused]] const Event& event) const noexcept{
				
				}
		};
		
		void SetUp() override{
			c6::SimpleListener<Event> lamdaListener([]([[maybe_unused]] const Event& event){});
			c6::SimpleListener<Event> lamdaListener2([]([[maybe_unused]] const Event event){});
			c6::SimpleListener<Event> lamdaListener3([]([[maybe_unused]] Event event){});
			//c6::SimpleListener<Event> wrongLamdaListener1([]([[maybe_unused]] Event& event){});
			//c6::SimpleListener<Event> wrongLamdaListener2([]([[maybe_unused]] Event&& event){});
			//c6::SimpleListener<Event> wrongLamdaListener3([]([[maybe_unused]] const Event* event){});
			//c6::SimpleListener<Event> wrongLamdaListener4([]([[maybe_unused]] Event* event){});
			//c6::SimpleListener<Event> wrongLamdaListener5([](){});
			//c6::SimpleListener<Event> wrongLamdaListener6([]([[maybe_unused]] const NotEvent& notEvent){});
			Override overrideListener;
		}
		
		void TearDown() override{
		
		}
};

TEST_F(ListenerTest, SimpleTest){
	int x = 0;
	c6::SimpleListener<Event> lamdaListener([&x]([[maybe_unused]] const Event& event){
		x = 1;
	});
	ASSERT_NE(x, 1);
	lamdaListener.onNotify(Event());
	ASSERT_EQ(x, 1);
}
