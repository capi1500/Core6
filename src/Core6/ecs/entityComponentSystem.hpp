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
#include <Core6/ecs/impl/entityState.hpp>
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
			void expandSignatureCall(EntityId entity, const Function& function, Args... args){
				using RequiredComponents = MPL::Filter<IsComponentPredicate, Sig>;
				
				using ExpandedCall = MPL::Rename<ExpandCallHelper, RequiredComponents>;
				
				ExpandedCall::template call<Function, Args...>(*this, entity, ShuffledList::getItem(entity).dataId, function, args...);
			}
			
			template<class... Components>
			struct ExpandCallHelper{
				template<class Function, class... Args>
				static void call(EntityComponentSystem<Config>& entityManager, const EntityId& entity, const DataId& dataId, const Function& function, Args... args){
					function.template call<Components..., Args...>(
							entityManager,
							entity,
							entityManager.componentManager.template getComponent<Components>(dataId)...,
					        args...
	                );
				}
			};
		public:
			void refreshNoShrink() noexcept override{
				ShuffledList::execute([this](const EntityId& i){
					if(hasComponent<EntityState>(i) && !getComponent<EntityState>(i).exists){
						ShuffledList::remove(i);
					}
				});
				ShuffledList::refreshNoShrink();
			}
			
			template<class... Args, concepts::Signature<Config> Signature>
			void execute(const System<Config, Signature, Args...>& system, Args... args){
				using Sys = System<Config, Signature, Args...>;
				ShuffledList::execute([this, &system, &args...](const EntityId& i){
					Entity& entity = ShuffledList::getItem(i);
					if(entity.exists && (Sys::key & entity.underlying) == Sys::key)
						expandSignatureCall<Signature, Sys, Args...>(i, system, args...);
				});
			}
			
			EntityId add(){
				EntityId id = ShuffledList::add();
				addComponent<EntityState>(id);
				return id;
			}
			
			template<class... Args>
			EntityId addFromFactory(const EntityFactory<Config, Args...>& factory, Args&&... args){
				EntityId id = add();
				factory.spawn(*this, id, std::forward<Args>(args)...);
				return id;
			}
			
			template<class... Args>
			[[nodiscard]]
			Handle addWithHandleFromFactory(const EntityFactory<Config, Args...>& factory, Args&&... args){
				Handle handle = this->addWithHandle();
				factory.spawn(*this, ShuffledList::getItemId(handle), std::forward<Args>(args)...);
				return handle;
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(const EntityId& id) const noexcept{
				return ShuffledList::get(id)[Config::template tagBit<T>()];
			}
			
			template<concepts::Tag<Config> T>
			void addTag(const EntityId& id) noexcept{
				ShuffledList::get(id)[Config::template tagBit<T>()] = true;
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(const EntityId& id) noexcept{
				ShuffledList::get(id)[Config::template tagBit<T>()] = false;
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(const EntityId& id) const noexcept{
				return ShuffledList::get(id)[Config::template componentBit<T>()];
			}
			
			template<concepts::Component<Config> T, class... Args>
			requires std::is_constructible_v<T, Args...>
			auto& addComponent(const EntityId& id, const Args&... args) noexcept{
				ShuffledList::get(id)[Config::template componentBit<T>()] = true;
				auto& c = componentManager.template getComponent<T>(ShuffledList::getItem(id).dataId);
				c = T(args...);
				
				return c;
			}
			
			template<concepts::Component<Config> T>
			auto& getComponent(const EntityId& id){
				return componentManager.template getComponent<T>(ShuffledList::getItem(id).dataId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(const EntityId& id) noexcept{
				ShuffledList::get(id)[Config::template componentBit<T>] = false;
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(const Handle& handle) const noexcept{
				return hasTag<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			template<concepts::Tag<Config> T>
			void addTag(const Handle& handle) noexcept{
				addTag<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(const Handle& handle) noexcept{
				deleteTag<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(const Handle& handle) const noexcept{
				return hasComponent<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T, class... Args>
			requires std::is_constructible_v<T, Args...>
			auto& addComponent(const Handle& handle, const Args&... args) noexcept{
				return addComponent<T>(ShuffledList::getHandleData(handle).itemId, args...);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			auto& getComponent(const Handle& handle){
				return getComponent<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(const Handle& handle) noexcept{
				deleteComponent<T>(ShuffledList::getHandleData(handle).itemId);
			}
			
			EntityComponentSystem() : ShuffledList([](Key& key){key.reset();}){}
	};
}

