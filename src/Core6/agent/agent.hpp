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

#ifndef CORE6_AGENT_HPP
#define CORE6_AGENT_HPP

#include <type_traits>
#include <Core6/framework.hpp>
#include "inputComponent.hpp"
#include "logicComponent.hpp"
#include "audioComponent.hpp"
#include "graphicComponent.hpp"
#include "Core6/utils/gizmo.hpp"

namespace c6{
	template <class T>
	constexpr bool GraphicConcept = std::is_base_of<GraphicComponent, T>::value or std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool AudioConcept = std::is_base_of<AudioComponent, T>::value or std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool LogicConcept = std::is_base_of<LogicComponent, T>::value or std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool InputConcept = std::is_base_of<InputComponent, T>::value or std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool UsesGraphicConcept = GraphicConcept<T> and not std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool UsesAudioConcept = AudioConcept<T> and not std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool UsesLogicConcept = LogicConcept<T> and not std::is_null_pointer_v<T>;
	
	template <class T>
	constexpr bool UsesInputConcept = InputConcept<T> and not std::is_null_pointer_v<T>;
	
	template <class Graphic, class Audio, class Input, class Logic>
	class Agent : public Gizmo{
		private:
			Graphic* m_graphic;
			Audio* m_audio;
			Input* m_input;
			Logic* m_logic;
			
			/**
			 * @brief Private constructor, only Scene can construct new agents
			 * @param graphic - graphic component
			 * @param audio - audio component
			 * @param input - input component
			 * @param logic - logic component
			 */
			Agent(Graphic* graphic, Audio* audio, Input* input, Logic* logic){
				if constexpr (not (GraphicConcept<Graphic> and AudioConcept<Audio> and LogicConcept<Logic> and InputConcept<Input>)){
					Framework::getMessage()->send(Message("Cannot create new Agent: components not valid (did you forget about inheriting from xyzComponent?)", MessageType::Error));
				}
				m_graphic = graphic;
				m_audio = audio;
				m_input = input;
				m_logic = logic;
				
				if constexpr (UsesLogicConcept<Logic>){
					if constexpr (UsesGraphicConcept<Graphic>)
						m_logic->registerGraphic(m_graphic);
					if constexpr (UsesAudioConcept<Audio>)
						m_logic->registerAudio(m_audio);
				}
				if constexpr (UsesInputConcept<Input>){
					if constexpr (UsesLogicConcept<Logic>)
						m_input->registerLogic(m_logic);
				}
			}
		public:
			void update(const sf::Time& time) override{
				if constexpr (UsesLogicConcept<Logic>){
					m_logic->update(time);
				}
			}
			
			void draw() override{
				if constexpr (UsesGraphicConcept<Graphic>){
					Framework::getRenderer()->get().draw(*m_graphic);
				}
			}
			
			~Agent(){
				kill();
				delete m_graphic;
				delete m_audio;
				delete m_input;
				delete m_logic;
			}
			
			friend class Scene;
	};
}

#endif //CORE6_AGENT_HPP
