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

#include "job.hpp"

namespace c6{
	class JobPool{
		private:
			std::size_t allocatedJobs;
			std::vector<Job> storage;
		public:
			/**
			 * Allocates (2^exponent) jobs
			 * @param exponent
			 */
			JobPool(std::size_t exponent);
			
			Job* allocate();
			bool full() const;
			void clear();
			
			Job* createJob(Job::Function jobFunction);
			Job* createJob(Job::Function jobFunction, Job* parent);
			template<class Data>
			Job* createJob(Job::Function jobFunction, const Data& data);
			template<class Data>
			Job* createJob(Job::Function jobFunction, const Data& data, Job* parent);
			template<class Function>
			Job* createClosureJob(Function function);
			template<class Function>
			Job* createClosureJob(Function function, Job* parent);
	};
}

