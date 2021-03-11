/**
* Core6
* Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
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

#ifndef CORE6_GROUP_HPP
#define CORE6_GROUP_HPP

#include <vector>
#include <SFML/System/Time.hpp>
#include "gizmo.hpp"

namespace c6{
	/**
	 * @brief Group is a Gizmo that holds other gizmos
	 * @note holds additional variable [order]. If true, group guarantees gizmos will be always in the same relative order.
	 */
	class Group : virtual public Gizmo{
		protected:
			bool m_order;
			std::vector<Gizmo*> m_members;
		public:
			/**
			 * @brief Create new group
			 * @param order - (optional, default = false) if [true] gizmos inside group will always be in the same order
			 */
			Group(bool order = false);

			/**
			 * @brief destroys all gizmos and then itself
			 */
			void destroy() override;
			
			/**
			 * @brief kills all gizmos and then itself
			 */
			void kill() override;

			/**
			 * @brief updates each gizmo (that exists and is active)
			 * @param time - how much time passed for group
			 */
			void update(const sf::Time& time) override;
			
			/**
			 * @brief draws each gizmo (that exists and is visible)
			 */
			void draw() override;
			
			/**
			 * @brief executes function [f] on each gizmo (that exists and is active)
			 * @tparam F - function type, must take gizmo pointer 'Gizmo*' as parameter and return void
			 * @param f - function to execute on gizmos (that exist and are active), see template parameter F for more informations
			 */
			template<class F>
			void execute(F&& f){
				for(auto g : m_members){
					if(g != nullptr and g->isExists() and g->isActive())
						f(g);
				}
			}
			
			/**
			 * @brief returns index of gizmo [g] in groups array
			 * @param g - pointer to gizmo
			 * @return index of [g] in array, or array's size if doesn't exist
			 */
			size_t indexOf(Gizmo* g);
			
			/**
			 * @brief adds gizmo [g] to group
			 * @param g - pointer to gizmo
			 * @note if [g] already was in different group, it removes it from there
			 * @note if [g] was in the same group, nothing happens
			 * @note adds [g] in first free place (linear complexity)
			 * @see Group::addToBack(Gizmo* g)
			 */
			void add(Gizmo* g);
			
			/**
			 * @brief adds gizmo [g] at the end of the group
			 * @param g - pointer to gizmo
			 * @note if [g] already was in different group, it removes it from there
			 * @note if [g] was in the same group, nothing happens
			 */
			void addToBack(Gizmo* g);
			
			/**
			 * @brief deletes [g] and erases it from group
			 * @param g - pointer to gizmo
			 * @note if [g] doesn't belong to the group, nothing happens
			 * @note leaves nullptr in it's place
			 * @see Group::remove(Gizmo* g)
			 */
			void erase(Gizmo* g);
			
			/**
			 * @brief deletes [g] and removes it from group
			 * @param g - pointer to gizmo
			 * @note if [g] does not belong to the group, nothing happens
			 * @note if [order] = false, gizmo from back is swaped with [g] and then [g] is poped from back
			 * @see Group::remove(Gizmo* g)
			 */
			void remove(Gizmo* g);
			
			/**
			 * @brief replaces gizmo [o] with gizmo [n]
			 * @param o - pointer to (old) gizmo in group
			 * @param n - pointer to (new) gizmo
			 * @note destroys [o]
			 */
			void replace(Gizmo* o, Gizmo* n);
			
			/**
			 * @brief get number of living gizmos
			 * @return number of gizmos that exist and are alive
			 */
			size_t countLiving();
			
			/**
			 * @brief get number of dead gizmos
			 * @return number of gizmos and are not alive
			 */
			size_t countDead();
			
			/**
			 * @brief get number of gizmos
			 * @return total number of gizmos
			 */
			size_t count();
			
			/**
			 * @brief get random gizmo
			 * @return a random gizmo from group
			 */
			Gizmo* getRandom();
			
			/**
			 * @brief get gimzo using index
			 * @param at - index
			 * @return gizmo from index [at]
			 */
			Gizmo* getGizmo(size_t at);
	};
}

#endif //CORE6_GROUP_HPP
