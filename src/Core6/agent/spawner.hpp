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

#ifndef CORE6_SPAWNER_HPP
#define CORE6_SPAWNER_HPP

#include "graphicComponent.hpp"
#include "audioComponent.hpp"
#include "inputComponent.hpp"

namespace c6{
	/**
	 * @brief helper class holding predefined components. Needed to create new agents via Scene
	 */
	class Spawner{
		private:
			GraphicComponent* m_graphic;
			AudioComponent* m_audio;
			InputComponent* m_input;
			LogicComponent* m_logic;
		public:
			/**
			 * @brief get graphic component
			 * @return graphic component
			 */
			GraphicComponent* getGraphic();
			
			/**
			 * @brief get audio component
			 * @return audip component
			 */
			AudioComponent* getAudio();
			
			/**
			 * @brief get input component
			 * @return input component
			 */
			InputComponent* getInput();
			
			/**
			 * @brief get logic component
			 * @return logic component
			 */
			LogicComponent* getLogic();
			
			/**
			 * @brief Constructs new factory using components
			 * @param graphic - graphic component
			 * @param audio - audio component
			 * @param input - input component
			 * @param logic - logic component
			 */
			Spawner(GraphicComponent* graphic, AudioComponent* audio, InputComponent* input, LogicComponent* logic);
			
			~Spawner();
	};
}

#endif //CORE6_SPAWNER_HPP
