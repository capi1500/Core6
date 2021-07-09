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

#include <vector>
#include <tuple>
#include <MPL/MPL.hpp>
#include <forward_list>
#include <Core6/utils/shuffledList.hpp>
#include <iostream>
#include "config.hpp"
#include "system.hpp"
#include "Core6/ecs/impl/componentManager.hpp"
#include "entityFactory.hpp"

namespace c6{
	template<concepts::Config Config>
	class EntityComponentSystem : public ShuffledList<typename Config::Key>{
			using Key = typename Config::Key;
		public:
			using EntityId = typename ShuffledList<Key>::ItemId;
			using DataId = typename ShuffledList<Key>::DataId;
			using Handle = typename ShuffledList<Key>::Handle;
			using Entity = typename ShuffledList<Key>::Item;
			using ShuffledList = ShuffledList<Key>;
		private:
			template<class T>
			using IsComponentPredicate = std::integral_constant<bool, Config::template isComponent<T>()>;
		
			ComponentManager<Config> componentManager;
			
			void resize(size_t newCapacity) override{
				ShuffledList::resize(newCapacity);
				componentManager.resize(newCapacity);
			}
			
			template<class... Components>
			struct ExpandCallHelper;
			
			template<concepts::Signature<Config> Sig, class Function, class... Args>
			void expandSignatureCall(DataId entity, const Function& function, Args... args){
				using RequiredComponents = MPL::Filter<IsComponentPredicate, Sig>;
				
				using ExpandedCall = MPL::Rename<ExpandCallHelper, RequiredComponents>;
				
				ExpandedCall::template call<Function, Args...>(*this, entity, function, args...);
			}
			
			template<class... Components>
			struct ExpandCallHelper{
				template<class Function, class... Args>
				static void call(EntityComponentSystem<Config>& entityManager, DataId entity, const Function& function, Args... args){
					function.function(/*entityManager,
			                entity,
			                */entityManager.componentManager.template
			                        getComponent<Components>(entity)...,
					        args...
	                );
				}
			};
			
			
			
		public:
			template<concepts::Signature<Config> Signature, class... Args>
			void execute(const System<Config, Signature, Args...>& system, Args... args){
				using Sys = System<Config, Signature, Args...>;
				ShuffledList::execute([this, &system, &args...](EntityId i){
					Entity& entity = ShuffledList::getItem(i);
					if(entity.exists && (Sys::key & entity.underlying) == Sys::key)
						expandSignatureCall<Signature, Sys, Args...>(entity.dataId, system, args...);
				});
			}
			
			template<class... Args>
			EntityId addFromFactory(const EntityFactory<Config, Args...>& factory, Args... args){
				EntityId id = this->add();
				factory.spawn(*this, id, args...);
				return id;
			}
			
			template<class... Args>
			[[nodiscard]]
			Handle addWithHandleFromFactory(const EntityFactory<Config, Args...>& factory, Args... args){
				Handle handle = this->addWithHandle();
				factory.spawn(*this, ShuffledList::getItemId(handle), args...);
				return handle;
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(EntityId id) const noexcept{
				return ShuffledList::get(id)[Config::template tagBit<T>()];
			}
			
			template<concepts::Tag<Config> T>
			void addTag(EntityId id) noexcept{
				ShuffledList::get(id)[Config::template tagBit<T>()] = true;
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(EntityId id) noexcept{
				ShuffledList::get(id)[Config::template tagBit<T>()] = false;
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(EntityId id) const noexcept{
				return ShuffledList::get(id)[Config::template componentBit<T>()];
			}
			
			template<concepts::Component<Config> T, class... Args>
			auto& addComponent(EntityId id, const Args&... args) noexcept{
				ShuffledList::get(id)[Config::template componentBit<T>()] = true;
				auto& c = componentManager.template getComponent<T>(ShuffledList::getItem(id).dataId);
				c = T(args...);
				
				return c;
			}
			
			template<concepts::Component<Config> T>
			auto& getComponent(EntityId id){
				return componentManager.template getComponent<T>(ShuffledList::getItem(id).dataId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(EntityId id) noexcept{
				ShuffledList::get(id)[Config::template componentBit<T>] = false;
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(const Handle& handle) const noexcept{
				return hasTag<T>(getHandleData(handle).itemId);
			}
			
			template<concepts::Tag<Config> T>
			void addTag(const Handle& handle) noexcept{
				addTag<T>(getHandleData(handle).itemId);
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(const Handle& handle) noexcept{
				deleteTag<T>(getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(const Handle& handle) const noexcept{
				return hasComponent<T>(getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T, class... Args>
			auto& addComponent(const Handle& handle, const Args&... args) noexcept{
				return addComponent<T>(getHandleData(handle).itemId, args...);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			auto& getComponent(const Handle& handle){
				return getComponent<T>(getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(const Handle& handle) noexcept{
				deleteComponent<T>(getHandleData(handle).itemId);
			}
			
			EntityComponentSystem() : ShuffledList([](Key& key){key.reset();}){}
	};
}

