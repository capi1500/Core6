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

#ifndef CORE6_FACTORY_HPP
#define CORE6_FACTORY_HPP

#include <Core6/agent/agent.hpp>

namespace c6{
	/**
	 * @brief helper class holding predefined components. Needed to create new agents via Scene
	 */
	template <class Graphic, class Audio, class Input, class Logic>
	class Factory{
		private:
			Graphic m_graphic;
			Audio m_audio;
			Input m_input;
			Logic m_logic;
		public:
			/**
			 * @brief get graphic component
			 * @return graphic component
			 */
			Graphic& getGraphic(){
				return m_graphic;
			}
			
			/**
			 * @brief get audio component
			 * @return audip component
			 */
			Audio& getAudio(){
				return m_audio;
			}
			
			/**
			 * @brief get input component
			 * @return input component
			 */
			Input& getInput(){
				return m_input;
			}
			
			/**
			 * @brief get logic component
			 * @return logic component
			 */
			Logic& getLogic(){
				return m_logic;
			}
			
			/**
			 * @brief Constructs new factory using components
			 * @param graphic - graphic component
			 * @param audio - audio component
			 * @param input - input component
			 * @param logic - logic component
			 */
			Factory(const Graphic& graphic, const Audio& audio, const Input& input, const Logic& logic) : m_graphic(graphic), m_audio(audio), m_input(input), m_logic(logic){
			}
	};
}

#endif //CORE6_FACTORY_HPP
