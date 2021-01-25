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

#ifndef CORE6_SCENE_HPP
#define CORE6_SCENE_HPP

#include <Core6/state/finiteState.hpp>
#include <Core6/camera.hpp>
#include <Core6/signal/listener.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include "Core6/utils/group.hpp"
#include <Core6/agent/agent.hpp>
#include <Core6/agent/factory.hpp>

namespace c6{
	/**
	 * @brief Class managing storing, updating and drawing Agents
	 */
	class Scene : public Group, public FiniteState, public Listener<sf::Event>, public Listener<CoreSignal>{
		private:
			Camera m_camera;
		public:
			/**
			 * @brief handling sf::Event events
			 * @param signal - sf::Event type signal
			 */
			void onSignal(const sf::Event& signal) override;
			
			/**
			 * @brief handling CoreSignal events
			 * @param signal - CoreSignal type signal
			 */
			void onSignal(const CoreSignal& signal) override;
			
			/**
			 * @brief draw all stored Agents
			 */
			void draw() override;
			
			/**
			 * @brief Add new agent from factory (blueprint)
			 * @tparam Graphic - GraphicComponent type of factory
			 * @tparam Audio - AudioComponent type of factory
			 * @tparam Input - InputComponent type of factory
			 * @tparam Logic - LogicComponent type of factory
			 * @param factory - factory object - new agent's blueprint
			 * @note most of the times template paramteres are deducted automatically
			 */
			template<class Graphic, class Audio, class Input, class Logic>
			void addAgent(Factory<Graphic, Audio, Input, Logic>& factory){
				addToBack(new Agent<Graphic, Audio, Input, Logic>(new Graphic(factory.getGraphic()), new Audio(factory.getAudio()), new Input(factory.getInput()), new Logic(factory.getLogic())));
			}
			
			/**
			 * @brief constructor of scene
			 */
			Scene();
	};
}


#endif //CORE6_SCENE_HPP
