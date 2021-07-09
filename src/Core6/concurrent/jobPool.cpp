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

#include "jobPool.hpp"

namespace c6{
	JobPool::JobPool(std::size_t exponent) : allocatedJobs(0), storage(1 << exponent){
	
	}
	
	Job* JobPool::allocate(){
		if(full())
			return nullptr;
		return &storage[allocatedJobs++];
	}
	
	bool JobPool::full() const{
		return allocatedJobs == storage.size();
	}
	
	void JobPool::clear(){
		allocatedJobs = 0;
	}
	
	Job* JobPool::createJob(Job::Function jobFunction){
		Job* job = allocate();
		if(job == nullptr)
			return nullptr;
		new(job) Job(jobFunction);
		return job;
	}
	
	Job* JobPool::createJob(Job::Function jobFunction, Job* parent){
		return nullptr;
	}
	
	template<class Data>
	Job* JobPool::createJob(Job::Function jobFunction, const Data& data){
		return nullptr;
	}
	
	template<class Data>
	Job* JobPool::createJob(Job::Function jobFunction, const Data& data, Job* parent){
		return nullptr;
	}
	
	template<class Function>
	Job* JobPool::createClosureJob(Function function){
		return nullptr;
	}
	
	template<class Function>
	Job* JobPool::createClosureJob(Function function, Job* parent){
		return nullptr;
	}
}