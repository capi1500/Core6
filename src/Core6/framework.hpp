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

#ifndef CORE6_FRAMEWORK_HPP
#define CORE6_FRAMEWORK_HPP

#include <Core6/utils/lazyClass.hpp>
#include <Core6/utils/nonCopyable.hpp>
#include <Core6/config.hpp>

namespace c6{
	/**
	 * @brief Global service provider
	 * <br><br>
	 * Provides Loader, ResourceManager, InputHandler, Renderer, Storage<std::string, sf::Music>, Signal<CoreSignal> and Signal<Message>. <br>
	 * All services are initialized with nullptr. To prevent accessing uninitialized memory, on first usage, if not initialized before, service is created with default service objects.
	 */
	template<concepts::Config TConfig>
	class Framework : NonCopyable{
			using Config = TConfig;
			using ResourceManager = typename Config::ResourceManager;
			using InputHandler = typename Config::InputHandler;
			using Renderer = typename Config::Renderer;
			using Soundboard = typename Config::Soundboard;
		private:
			static LazyClass<ResourceManager> m_resourceManager;
			static LazyClass<InputHandler> m_input;
			static LazyClass<Renderer> m_renderer;
			static LazyClass<Soundboard> m_soundboard;
		public:
			static ResourceManager& getResourceManager() noexcept{
				return m_resourceManager();
			}
			
			static InputHandler& getInputHandler() noexcept{
				return m_input();
			}
			
			static Renderer& getRenderer() noexcept{
				return m_renderer();
			}
			
			static Soundboard& getSoundboard() noexcept{
				return m_soundboard();
			}
			
			static void destroyResourceManager() noexcept{
				m_resourceManager.destroy();
			}
			
			static void destroyInputHandler() noexcept{
				m_input.destroy();
			}
			
			static void destroyRenderer() noexcept{
				m_renderer.destroy();
			}
			
			static void destroySoundboard() noexcept{
				m_soundboard.destroy();
			}
	};
	template<concepts::Config Config> LazyClass<typename Config::ResourceManager> Framework<Config>::m_resourceManager;
	template<concepts::Config Config> LazyClass<typename Config::InputHandler> Framework<Config>::m_input;
	template<concepts::Config Config> LazyClass<typename Config::Renderer> Framework<Config>::m_renderer;
	template<concepts::Config Config> LazyClass<typename Config::Soundboard> Framework<Config>::m_soundboard;
}

#endif //CORE6_FRAMEWORK_HPP
