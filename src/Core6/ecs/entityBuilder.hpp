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
#include <Core6/utils/callback.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

namespace c6{
	template<concepts::Config Config>
	class EntityBuilder{
			using This = EntityBuilder<Config>;
			
			using ECS = EntityComponentSystem<Config>;
			using EntityId = typename ECS::EntityId;
			using Handle = typename ECS::Handle;
			
			template<class... Ts>
			using TupleOfPairs = std::tuple<std::pair<bool, Ts>...>;
			
			using DefaultComponentList = typename Config::ComponentList;
			using AdditionallComponentList = MPL::TypeList<std::shared_ptr<sf::Sprite>>;
			using TagsList = typename Config::TagList;
			
			template<class Component>
			using IsDefaultComponent = MPL::Contains<Component, DefaultComponentList>;
			template<class Component>
			using IsAdditionalComponent = MPL::Contains<Component, AdditionallComponentList>;
			template<class Component>
			static inline constexpr bool IsComponent = IsDefaultComponent<Component>::value || IsAdditionalComponent<Component>::value || std::is_same_v<Component, sf::Sprite>;
			template<class Tag>
			static inline constexpr bool IsTag = Config::template isTag<Tag>();
			
			using DefaultComponents = MPL::Rename<TupleOfPairs, DefaultComponentList>;
			using AdditionallComponents = MPL::Rename<TupleOfPairs, AdditionallComponentList>;
			using Tags = MPL::Rename<TupleOfPairs, TagsList>;
		private:
			DefaultComponents defaultComponents;
			AdditionallComponents additionalComponents;
			Tags tags;
			
			template<class Component>
			requires IsComponent<Component>
			bool isUsed(){
				if constexpr(IsDefaultComponent<Component>::value)
					return std::get<std::pair<bool, Component>>(defaultComponents).first;
				else if constexpr(IsAdditionalComponent<Component>::value)
					return std::get<std::pair<bool, Component>>(additionalComponents).first;
			}
			
			template<class Component>
			requires IsComponent<Component>
			bool setUsed(){
				if constexpr(IsDefaultComponent<Component>::value)
					std::get<std::pair<bool, Component>>(defaultComponents).first = true;
				else if constexpr(IsAdditionalComponent<Component>::value)
					std::get<std::pair<bool, Component>>(additionalComponents).first = true;
				return false;
			}
		public:
			Handle spawnWithHandle(ECS& ecs){
				Handle h = ecs.addWithHandle();
				MPL::forTuple([this, &h, &ecs](auto& t){
					ecs.template addComponent<typeof(t.second)>(h, t.second);
				}, defaultComponents);
				MPL::forTuple([this, &h, &ecs](auto& t){
					if(t.first){
						ecs.template addTag<typeof(t.second)>(h);
					}
				}, tags);
				return h;
			}
			
			EntityId spawn(ECS& ecs){
				EntityId e = ecs.add();
				MPL::forTuple([this, &e, &ecs](auto& t){
					if(t.first){
						ecs.template addComponent<typeof(t.second)>(e, t.second);
					}
				}, defaultComponents);
				MPL::forTuple([this, &e, &ecs](auto& t){
					if(t.first){
						ecs.template addTag<typeof(t.second)>(e);
					}
				}, tags);
				return e;
			}
			
			template<class Component>
			requires IsComponent<Component>
			Component& get(){
				if constexpr (std::is_same_v<Component, sf::Sprite>){
					return *(get<std::shared_ptr<sf::Sprite>>().get());
				}
				else if constexpr(IsDefaultComponent<Component>::value)
					return std::get<std::pair<bool, Component>>(defaultComponents).second;
				else if constexpr(IsAdditionalComponent<Component>::value)
					return std::get<std::pair<bool, Component>>(additionalComponents).second;
			}
			
			template<class Tag>
			requires IsTag<Tag>
	        This& addTag(){
				std::get<std::pair<bool, Tag>>(tags).first = true;
				return *this;
			}
			
			template<class Component>
			requires IsComponent<Component>
			This& attach(){
				attach<Component>(Callback<Component>([]{
					return Component();
				}));
				return *this;
			}
			
			template<class Component, class... Args>
			requires (IsComponent<Component> && !std::is_same_v<Component, sf::Sprite>)
			This& attach(const Callback<Component, Args&...>& provider){
				get<Component>() = provider(get<Args>()...);
				setUsed<Component>();
				return *this;
			}
			
			// special treatment of sf::Sprite
			template<class Component, class... Args>
			requires std::is_same_v<Component, sf::Sprite>
			This& attach(const Callback<sf::Sprite, Args&...>& provider){
				get<std::shared_ptr<sf::Sprite>>() = std::make_shared<sf::Sprite>(provider(get<Args>()...));
				attach<c6::component::Drawable>(Callback<c6::component::Drawable>([this]{
					return get<std::shared_ptr<sf::Sprite>>();
				}));
				attach<c6::component::Transformable>(Callback<c6::component::Transformable>([this]{
					return get<std::shared_ptr<sf::Sprite>>();
				}));
				setUsed<std::shared_ptr<sf::Sprite>>();
				return *this;
			}
	};
}

