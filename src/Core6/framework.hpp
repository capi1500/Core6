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

#ifndef CORE6_FRAMEWORK_HPP
#define CORE6_FRAMEWORK_HPP

#include <Core6/utils/singleton.hpp>
#include <Core6/systems/inputHandler.hpp>
#include <Core6/signal/message.hpp>
#include <Core6/systems/renderer.hpp>
#include <Core6/systems/soundBoard.hpp>
#include <Core6/systems/resourceManager.hpp>
#include <Core6/plugin/entryPoint.hpp>

namespace c6{
	/**
	 * @brief Global service provider
	 * <br><br>
	 * Provides Loader, ResourceManager, InputHandler, Renderer, SoundBoard, Signal<CoreSignal> and Signal<Message>. <br>
	 * All services are initialized with nullptr. To prevent accessing uninitialized memory, on first usage, if not initialized before, service is created with default service objects.
	 */
	class Framework : Singleton<Framework>{
		private:
			static ResourceManager* m_resourceManager;
			static InputHandler* m_input;
			static Renderer* m_renderer;
			static SoundBoard* m_audioManager;
			static Signal<Message>* m_message;
			static EntryPoint* m_entryPoint;
		public:
			Framework(token t);
			virtual ~Framework();
			
			/**
			 * @brief Function accessing ResourceManager
			 * <br><br>
			 * If assetManager is not initialized, it is created as default ResourceManager object
			 * @return Pointer to assetManager service
			 */
			static ResourceManager* getResourceManager();
			
			/**
			 * @brief Function accessing InputHandler
			 * <br><br>
			 * If input is not initialized, it is created as default InputHandler object
			 * @return Pointer to input service
			 */
			static InputHandler* getInput();
			
			/**
			 * @brief Function accessing Renderer
			 * <br><br>
			 * If renderer is not initialized, it is created as default Renderer object
			 * @return Pointer to renderer service
			 */
			static Renderer* getRenderer();
			
			/**
			 * @brief Function accessing SoundBoard
			 * <br><br>
			 * If audioManager is not initialized, it is created as default SoundBoard object
			 * @return Pointer to audioManager service
			 */
			static SoundBoard* getAudioManager();
			
			/**
			 * @brief Function accessing Signal<Message>
			 * <br><br>
			 * If message is not initialized, it is created as default Signal<Message> object
			 * @return Pointer to message service
			 */
			static Signal<Message>* getMessage();
			
			/**
			 * @brief Function accessing EntryPoint
			 * <br><br>
			 * If entryPoint is not initialized, it is created as default EntryPoint object
			 * @return Pointer to entryPoint service
			 */
			static EntryPoint* getEntryPoint();
			
			/**
			 * @brief Registers new assetManager service
			 * @param assetManager - new assetManager service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerResourceManager(ResourceManager* assetManager);
			
			/**
			 * @brief Registers new input service
			 * @param input - new input service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerInput(InputHandler* input);
			
			/**
			 * @brief Registers new renderer service
			 * @param renderer - new renderer service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerRenderer(Renderer* renderer);
			
			/**
			 * @brief Registers new audioManager service
			 * @param audioManager - new audioManager service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerAudioManager(SoundBoard* audioManager);
			
			/**
			 * @brief Registers new message service
			 * @param message - new message service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerMessage(Signal<Message>* message);
			
			/**
			 * @brief Registers new EntryPoint service
			 * @param entryPoint - new EntryPoint service
			 * @return
			 * true if previous service was overwritten<br>
			 * false otherwise
			 */
			static bool registerEntryPoint(EntryPoint* entryPoint);
	};
}

#endif //CORE6_FRAMEWORK_HPP
