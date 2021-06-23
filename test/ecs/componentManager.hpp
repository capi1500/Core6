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
#include "config.hpp"
#include <Core6/ecs/impl/componentManager.hpp>

class ComponentManagerTest : public testing::Test{
	public:
		c6::ComponentManager<Config>* componentManager;
	protected:
		void SetUp() override{
			componentManager = new c6::ComponentManager<Config>();
		}
		
		void TearDown() override{
			delete componentManager;
		}
};

TEST_F(ComponentManagerTest, GeneralTest){
	componentManager->resize(10);
	
	for(c6::DataId i(0); i < 10; i++){
		ASSERT_EQ(typeid(componentManager->getComponent<C1>(c6::DataId(i))), typeid(C1&));
		ASSERT_EQ(typeid(componentManager->getComponent<C2>(c6::DataId(i))), typeid(C2&));
		ASSERT_EQ(typeid(componentManager->getComponent<C3>(c6::DataId(i))), typeid(C3&));
	}
}