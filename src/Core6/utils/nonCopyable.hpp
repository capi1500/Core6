//
// Created by capi1500 on 3/29/19.
//

#ifndef CORE6_NONCOPYABLE_HPP
#define CORE6_NONCOPYABLE_HPP

namespace c6{
	/**
	 * @brief Inheriting from this class prevents derived class from being copied
	 */
	class NonCopyable{
		public:
			NonCopyable(const NonCopyable&) = delete;
			
			NonCopyable& operator =(const NonCopyable&) = delete;
			
			NonCopyable(){
			}
	};
}

#endif //CORE6_NONCOPYABLE_HPP
