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

#include "game.hpp"
#include <Core6/agent/ecsConfig.hpp>
#include <Core6/agent/agentGroup.hpp>

/*
namespace tests{
	struct C0{
	};
	struct C1{
		bool x;
		C1() = default;
		C1(bool a) : x(a) {}
	};
	struct C2{
		char x;
		C2() = default;
		C2(char a) : x(a) {}
	};
	struct C3{
		int x;
		C3() = default;
		C3(int a) : x(a) {}
	};
	struct C4{
		double x;
		C4() = default;
		C4(double a) : x(a) {}
	};
	using MyComponentList = c6::ComponentList<C0, C1, C2, C3, C4>;
	
	struct T0{};
	struct T1{};
	struct T2{};
	using MyTagList = c6::TagList<T0, T1, T2>;
	
	using S0 = c6::Signature<>;
	using S1 = c6::Signature<C0, C1, T0>;
	using S2 = c6::Signature<C0, C4, T0>;
	using S3 = c6::Signature<C1, T0, C3, T2>;
	using MySignatureList = c6::SignatureList<S0, S1, S2, S3>;
	
	using MyConfig = c6::ECSConfig<MyComponentList, MyTagList, MySignatureList>;
	using MyManager = c6::AgentGroup<MyConfig>;
	using Agent = c6::Agent<MyConfig>;
	
	using System0 = c6::System<MyConfig, S0>;
	using System1 = c6::System<MyConfig, S1>;
	using System2 = c6::System<MyConfig, S2>;
	using System3 = c6::System<MyConfig, S3>;
	
	void runtimeTests(){
		System0 system0([](){
			std::cout << "hello from 0\n";
		});
		
		System1 system1([](C0 c0, C1 c1){
			std::cout << "hello from 1\n";
			std::cout << "c1.x is = " << c1.x << "\n";
		});
		
		MyManager mgr;
		
		Agent& a = mgr.newAgent();
		a.addTag<T0>();
		a.addComponent<C0>();
		a.addComponent<C1>(true);
		
		Agent& b = mgr.newAgent();
		b.addComponent<C0>();
		b.addComponent<C1>(false);
		
		mgr.executeSystem<S0>(system0);
		mgr.executeSystem<S1>(system1);
		
		mgr.destroy();
	}
}*/

int main(){
	Game game;
	game.init();
	game.run();
	//tests::runtimeTests();
	//std::cout << "Tests passed!" << std::endl;
}

