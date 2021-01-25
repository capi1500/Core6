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

#ifndef CORE6_GIZMO_HPP
#define CORE6_GIZMO_HPP

#include <SFML/System/Time.hpp>
#include <memory>

namespace c6{
	class Group;
	
	/**
	 * @brief simple base class meant for overriding. Provides set of state flags as well as common functions.
	 * @note flags are: [exists] [alive] [active] [visible]
	 * @note when gizmo is a member of a group it stores pointer to the group in [parent]
	 */
	class Gizmo{
		protected:
			bool m_exists;
			bool m_alive;
			bool m_active;
			bool m_visible;
			
			Group* m_parent;
			
			void setParent(Group* group);
		public:
			/**
			 * @brief create a gizmo with all flags set to true
			 */
			Gizmo();
			
			/**
			 * @brief destroys gizmo
			 * @see Gizmo::destroy()
			 */
			virtual ~Gizmo();
			
			/**
			 * @brief destroys gizmo and sets it's [parent] to nullptr
			 */
			virtual void destroy();
			
			/**
			 * @brief kills gizmo
			 *
			 * sets [alive] and [exists] to false
			 * @note may not be opposite to Gizmo::revive()
			 * @see Gizmo::revive()
			 */
			virtual void kill();
			
			/**
			 * @brief revives gizmo
			 *
			 * sets [alive] and [exists] to true
			 * @note may not be opposite to Gizmo::kill()
			 * @see Gizmo::kill()
			 */
			virtual void revive();
			
			/**
			 * @brief removes gizmo from [parent]
			 */
			virtual void remove();
			
			/**
			 * @brief kills gizmo and removes it
			 */
			void killAndErase();
			
			/**
			 * @brief updates gizmo
			 * @param time - how much time passed for gizmo
			 * @note function is meant to be overloaded
			 */
			virtual void update(const sf::Time& time);
			
			/**
			 * @brief draws gizmo
			 * @note function is meant to be overloaded
			 */
			virtual void draw();
			
			/**
			 * @brief get containing group
			 * @return pointer to [parent]
			 */
			Group* getParent() const;
			
			/**
			 * @brief gets [exists] flag
			 * @return true if gizmo exists
			 */
			bool isExists() const;
			
			/**
			 * @brief gets [exists] flag
			 * @return true if gizmo exists
			 */
			bool isAlive() const;
			
			/**
			 * @brief gets [active] flag
			 * @return true if gizmo is active
			 */
			bool isActive() const;
			
			/**
			 * @brief gets [visible] flag
			 * @return true if gizmo is visible
			 */
			bool isVisible() const;
			
			friend class Group;
	};
}

#endif //CORE6_GIZMO_HPP
