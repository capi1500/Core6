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

#include "config.hpp"
#include "entityComponentSystem.hpp"
#include <Core6/utils/functional.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

namespace c6{
	template<concepts::Config Config>
	class EntityBuilder{
			using This = EntityBuilder<Config>;
			
			using ECS = EntityComponentSystem<Config>;
			using EntityId = typename ECS::EntityId;
			using Handle = typename ECS::Handle;
		private:
			ECS& ecs;
			bool isHandle;
			union{
				Handle handle;
				EntityId id;
			};
		public:
			EntityBuilder(ECS& ecs, EntityId id) noexcept : ecs(ecs), isHandle(false), id(std::move(id)) {}
			EntityBuilder(ECS& ecs, Handle handle) noexcept : ecs(ecs), isHandle(true), handle(std::move(handle)) {}
			explicit EntityBuilder(ECS& ecs) noexcept : EntityBuilder(ecs, ecs.addWithHandle()) {}
			
			// getters and setters
			
			template<class Component>
			requires concepts::Component<Component, Config>
			Component& get(){
				if(isHandle)
					return ecs.template getComponent<Component>(handle);
				return ecs.template getComponent<Component>(id);
			}
			
			template<class Component>
			requires concepts::Component<std::shared_ptr<Component>, Config>
			Component& get(){
				return *(get<std::shared_ptr<Component>>().get());
			}
			
			template<class Component>
			requires concepts::Component<Component, Config>
			[[nodiscard]]
			bool has() const {
				if(isHandle)
					return ecs.template hasComponent<Component>(handle);
				return ecs.template hasComponent<Component>(id);
			}
			
			template<class Component>
			requires concepts::Component<std::shared_ptr<Component>, Config>
			[[nodiscard]]
			bool has() const{
				return has<std::shared_ptr<Component>>();
			}
			
			template<class Tag>
			requires concepts::Tag<Tag, Config>
			[[nodiscard]]
			bool has() const {
				if(isHandle)
					return ecs.template hasTag<Tag>(handle);
				return ecs.template hasTag<Tag>(id);
			}
			
			// attaching components and tags
			
			template<class Tag>
			requires concepts::Tag<Tag, Config>
			This& attach(){
				if(isHandle)
					ecs.template addTag<Tag>(handle);
				ecs.template addTag<Tag>(id);
				return *this;
			}
			
			template<class Component, class... Args>
			requires concepts::Component<Component, Config>
			This& attach(Args... args){
				if(isHandle)
					ecs.template addComponent<Component>(handle, args...);
				else
					ecs.template addComponent<Component>(id, args...);
				return *this;
			}
			
			template<class Component, class... Args>
			requires concepts::Component<std::shared_ptr<Component>, Config>
			This& attach(Args... args){
				return attach<std::shared_ptr<Component>>(std::make_shared<Component>(args...));
			}
			
			template<class Component, class Provided, class... Args>
			requires (concepts::Component<std::shared_ptr<Component>, Config> && std::is_base_of_v<Component, Provided> && !std::is_same_v<Component, Provided>)
			This& attach(Args... args){
				return attach<std::shared_ptr<Component>>(std::make_shared<Provided>(args...));
			}
			
			template<class Component, class... Args>
			requires concepts::Component<Component, Config>
			This& attach(const Function<Component, Args&...>& provider){
				return attach<Component>(std::move(provider(get<Args>()...)));
			}
			
			template<class Component, class... Args>
			requires concepts::Component<std::shared_ptr<Component>, Config>
			This& attach(const Function<Component, Args&...>& provider){
				return attach<std::shared_ptr<Component>>(std::make_shared<Component>(provider(get<Args>()...)));
			}
			
			template<class Component, class Provided, class... Args>
			requires (concepts::Component<std::shared_ptr<Component>, Config> && std::is_base_of_v<Component, Provided> && !std::is_same_v<Component, Provided>)
			This& attach(const Function<Provided, Args&...>& provider){
				return attach<std::shared_ptr<Component>>(std::make_shared<Provided>(provider(get<Args>()...)));
			}
			
			// detaching components and tags
			
			template<class Tag>
			requires concepts::Tag<Tag, Config>
			This& detach(){
				if(isHandle)
					ecs.template deleteTag<Tag>(handle);
				ecs.template deleteTag<Tag>(id);
				return *this;
			}
			
			template<class Component>
			requires concepts::Component<Component, Config>
			This& detach(){
				if(isHandle)
					ecs.template deleteComponent<Component>(handle);
				else
					ecs.template deleteComponent<Component>(id);
				return *this;
			}
			
			template<class Component>
			requires concepts::Component<std::shared_ptr<Component>, Config>
			This& detach(){
				return detach<std::shared_ptr<Component>>();
			}
			
			// special treatment of derivatives from sf::Drawable
			
			template<class Component>
			requires std::is_base_of_v<sf::Drawable, Component>
			This& attach(std::shared_ptr<Component> ptr){
				attach<std::shared_ptr<sf::Drawable>>(ptr);
				if constexpr(std::is_base_of_v<sf::Transformable, Component>){
					attach<std::shared_ptr<sf::Transformable>>(ptr);
				}
				return *this;
			}
			
			template<class Component>
			requires std::is_base_of_v<sf::Drawable, Component>
			This& attach(Component component){
				return attach<Component>(std::make_shared<Component>(component));
			}
			
			template<class Component, class... Args>
			requires std::is_base_of_v<sf::Drawable, Component>
			This& attach(const Function<Component, Args&...>& provider){
				return attach<Component>(std::make_shared<Component>(provider(get<Args>()...)));
			}
			
			template<class Component, class... Args>
			requires std::is_base_of_v<sf::Drawable, Component>
			This& attach(const Function<std::shared_ptr<Component>, Args&...>& provider){
				return attach<Component>(provider(get<Args>()...));
			}
	};
}