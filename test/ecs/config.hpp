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
#include <Core6/ecs/config.hpp>
#include "ecsInit.hpp"

class ConfigTest : public testing::Test{

};

TEST_F(ConfigTest, IsComponent){
	ASSERT_TRUE(Config::isComponent<C1>());
	ASSERT_TRUE(Config::isComponent<C2>());
	ASSERT_TRUE(Config::isComponent<C3>());
	ASSERT_FALSE(Config::isComponent<T1>());
	ASSERT_FALSE(Config::isComponent<T2>());
	ASSERT_FALSE(Config::isComponent<N1>());
	ASSERT_FALSE(Config::isComponent<N2>());
	ASSERT_FALSE(Config::isComponent<ConfigTest>());
	ASSERT_FALSE(Config::isComponent<Config>());
}

TEST_F(ConfigTest, IsTag){
	ASSERT_FALSE(Config::isTag<C1>());
	ASSERT_FALSE(Config::isTag<C2>());
	ASSERT_FALSE(Config::isTag<C3>());
	ASSERT_TRUE(Config::isTag<T1>());
	ASSERT_TRUE(Config::isTag<T2>());
	ASSERT_FALSE(Config::isTag<N1>());
	ASSERT_FALSE(Config::isTag<N2>());
	ASSERT_FALSE(Config::isTag<ConfigTest>());
	ASSERT_FALSE(Config::isTag<Config>());
}

TEST_F(ConfigTest, IsSignature){
	ASSERT_TRUE((Config::isSignature<c6::Signature<C1, T1, T2>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<C1, C2, C3>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<T1, C3, T2>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<C3, T1, T2>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<C1, C2>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<C1>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<T1>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<T2, T1>>()));
	ASSERT_FALSE((Config::isSignature<c6::Signature<T1, N1>>()));
	ASSERT_FALSE((Config::isSignature<c6::Signature<N1>>()));
	ASSERT_FALSE((Config::isSignature<c6::Signature<N2>>()));
	ASSERT_FALSE((Config::isSignature<c6::Signature<T1, T2, N1, C1, C2, C3>>()));
	ASSERT_FALSE((Config::isSignature<c6::Signature<N1, N2>>()));
	ASSERT_TRUE((Config::isSignature<c6::Signature<>>()));
}

TEST_F(ConfigTest, Count){
	ASSERT_EQ(Config::componentCount(), 3ull);
	ASSERT_EQ(Config::tagCount(), 2ull);
}

TEST_F(ConfigTest, Id){
	ASSERT_EQ(Config::componentID<C1>(), 0ull);
	ASSERT_EQ(Config::componentID<C2>(), 1ull);
	ASSERT_EQ(Config::componentID<C3>(), 2ull);
	ASSERT_EQ(Config::tagID<T1>(), 0ull);
	ASSERT_EQ(Config::tagID<T2>(), 1ull);
}

TEST_F(ConfigTest, Bit){
	ASSERT_EQ(Config::componentBit<C1>(), 0ull);
	ASSERT_EQ(Config::componentBit<C2>(), 1ull);
	ASSERT_EQ(Config::componentBit<C3>(), 2ull);
	ASSERT_EQ(Config::tagBit<T1>(), 3ull);
	ASSERT_EQ(Config::tagBit<T2>(), 4ull);
}