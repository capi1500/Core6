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

#include <new>
#include <functional>
#include <atomic>
#include <cstring>

namespace c6{
	class Job{
		public:
			using Function = void(Job&);
		private:
			Function* function;
			Job* parent;
			std::atomic_size_t unfinishedJobs;
			
			static constexpr std::size_t jobPayloadSize = sizeof(function) + sizeof(parent) + sizeof(unfinishedJobs);
			static constexpr std::size_t jobMaxPaddingSize = /*std::hardware_destructive_interference_size*/64;
			static constexpr std::size_t jobPaddingSize = jobMaxPaddingSize - jobPayloadSize;
			std::array<unsigned char, jobPaddingSize> padding;
			
			void finish();
		public:
			Job() = default;
			explicit Job(Function* function, Job* parent = nullptr);
			template<class Data>
			Job(Function* function, const Data& data, Job* parent = nullptr) : function(function), parent(parent){
				setData(data);
			}
			
			void run();
			[[nodiscard]] bool finished() const;
			
			template<class Data>
			std::enable_if_t<std::is_pod_v<Data> && (sizeof(Data) <= jobPaddingSize)> setData(const Data& data){
	        	std::memcpy(padding.data(), &data, sizeof(Data));
	        }
			
			template<class Data>
			const Data& getData() const{
				return *reinterpret_cast<const Data*>(padding.data());
			}
			
			template<class T, class... Args>
			void constructData(Args&&... args){
				new(padding.data())T(std::forward<Args>(args)...);
			}
	};
}

