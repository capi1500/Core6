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
#include <Core6/ecs/impl/entity.hpp>
#include "config.hpp"
#include "system.hpp"
#include "Core6/ecs/impl/componentManager.hpp"
#include "entityFactory.hpp"

namespace c6{
	template<concepts::Config Config>
	class EntityComponentSystem{
			using Key = typename Config::Key;
			
			template<class T>
			using IsComponentPredicate = std::integral_constant<bool, Config::template isComponent<T>()>;
		private:
			ComponentManager<Config> componentManager;
			std::vector<Entity<Config>> entities;
			std::vector<HandleData> handlesData;
			
			std::size_t capacity = 0, size = 0, sizeNext = 0;
			
			void growTo(size_t newCapacity){
				entities.resize(newCapacity);
				componentManager.resize(newCapacity);
				handlesData.resize(newCapacity);
				
				for(size_t i = capacity; i < newCapacity; i++){
					Entity<Config>& e = entities[i];
					HandleData& h = handlesData[i];
					
					e.dataId = i;
					e.key.reset();
					e.exist = false;
					e.handleDataId = i;
					
					h.counter = 0;
					h.entityId = i;
				}
				
				capacity = newCapacity;
			}
			
			void growIfNeeded(){
				if(capacity > sizeNext)
					return;
				growTo((capacity + 10) * 2);
			}
			
			[[nodiscard]]
			Entity<Config>& getEntity(EntityId id) noexcept{
				return entities[id];
			}
			
			[[nodiscard]]
			const Entity<Config>& getEntity(EntityId id) const noexcept{
				return entities[id];
			}
			
			[[nodiscard]]
			HandleData& getHandleData(HandleDataId id) noexcept{
				return handlesData[id];
			}
			
			[[nodiscard]]
			const HandleData& getHandleData(HandleDataId id) const noexcept{
				return handlesData[id];
			}
			
			[[nodiscard]]
			HandleData& getHandleData(const Handle& handle) noexcept{
				return getHandleData(handle.handleDataId);
			}
			
			[[nodiscard]]
			const HandleData& getHandleData(const Handle& handle) const noexcept{
				return getHandleData(handle.handleDataId);
			}
			
			template<class... Components>
			struct ExpandCallHelper;
			
			template<concepts::Signature<Config> Sig, class Function, class... Args>
			void expandSignatureCall(DataId entity, const Function& function, const Args&... args){
				using RequiredComponents = MPL::Filter<IsComponentPredicate, Sig>;
				
				using ExpandedCall = MPL::Rename<ExpandCallHelper, RequiredComponents>;
				
				ExpandedCall::call(*this, entity, function, args...);
			}
			
			template<class... Components>
			struct ExpandCallHelper{
				template<class Function, class... Args>
				static void call(EntityComponentSystem<Config>& entityManager, DataId entity, const Function& function, const Args&... args){
					function(entityManager,
			                entity,
			                entityManager.componentManager.template
			                        getComponent<Components>(entity)...,
					        args...
	                );
				}
			};
			
			void invalidateHandle(EntityId id) noexcept{
				handlesData[entities[id].handleDataId].counter++;
			}
			
			void refreshHandle(EntityId id) noexcept{
				handlesData[entities[id].handleDataId].entityId = id;
			}
		public:
			template<class Function, class... Args>
			requires std::invocable<Function, EntityId, const Args&...>
			void execute(const Function& function, const Args&... args){
				for(EntityId e(0); e < size; e++)
					function(e, args...);
			}
			
			template<concepts::Signature<Config> Signature, class... Args>
			void execute(const System<Config, Signature, Args...>& system, const Args&... args){
				using Sys = System<Config, Signature, Args...>;
				execute([this, &system, &args...](EntityId e){
					Entity<Config>& entity = getEntity(e);
					if(entity.exist && (Sys::key & entity.key) == Sys::key)
						expandSignatureCall<Signature>(entity.dataId, system, args...);
				});
			}
			
			EntityId createEntity(){
				growIfNeeded();
				EntityId free(sizeNext++);
				
				Entity<Config>& entity = entities[free];
				entity.exist = true;
				entity.key.reset();
				
				return free;
			}
			
			template<class... Args>
			EntityId createEntityFromFactory(const EntityFactory<Config, Args...>& factory, Args... args){
				EntityId id = createEntity();
				factory.spawn(*this, id, args...);
				return id;
			}
			
			[[nodiscard]]
			Handle createEntityWithHandle(){
				EntityId id = createEntity();
				
				Entity<Config>& entity = entities[id];
				HandleData& handleData = handleData[entity.handleDataId];
				handleData.entityId = id;
				
				return Handle(entity.handleDataId, handleData.counter);
			}
			
			template<class... Args>
			[[nodiscard]]
			Handle createEntityWithHandleFromFactory(const EntityFactory<Config, Args...>& factory, Args... args){
				Handle handle = createEntityWithHandle();
				factory.spawn(*this, getEntityId(handle), args...);
				return handle;
			}
			
			void clear() noexcept{
				for(std::size_t i = 0; i < capacity; i++){
					Entity<Config>& entity = entities[i];
					HandleData& handleData = handlesData[i];
					
					entity.dataId = i;
					entity.key.reset();
					entity.exist = false;
					entity.handleDataId = i;
					
					handleData.entityId = i;
					handleData.counter = 0;
				}
				size = sizeNext = 0;
			}
			
			void refresh() noexcept{
				if(sizeNext == 0){
					size = 0;
					return;
				}
				
				EntityId begin(0), end(0);
				
				try{
					while(true){
						while(true){
							if(begin > end)
								throw begin;
							if(!entities[begin].exist)
								break;
							begin++;
						}
						while(true){
							if(entities[end].exist)
								break;
							invalidateHandle(end);
							if(end <= begin)
								throw begin;
						}
						
						std::swap(entities[end], entities[begin]);
						
						refreshHandle(begin);
						
						invalidateHandle(end);
						refreshHandle(end);
						
						begin++;
						end--;
					}
					throw begin;
				} catch (EntityId last){
					size = sizeNext = last;
				}
			}
			
			void destroyEntity(EntityId id){
				entities[id].exist = false;
			}
			
			void destroyEntity(Handle handle){
				destroyEntity(getHandleData(handle).entityId);
			}
			
			[[nodiscard]]
			bool isHandleValid(const Handle& handle) const noexcept{
				return handle.counter == getHandleData(handle).counter;
			}
			
			[[nodiscard]]
			EntityId getEntityId(const Handle& handle) const noexcept{
				return getHandleData(handle).entityId;
			}
			
			[[nodiscard]]
			bool doesExist(EntityId entity) const noexcept{
				return getEntity(entity).exist;
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(EntityId entity) const noexcept{
				return entities[entity].key[Config::template tagBit<T>()];
			}
			
			template<concepts::Tag<Config> T>
			void addTag(EntityId entity) noexcept{
				entities[entity].key[Config::template tagBit<T>] = true;
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(EntityId entity) noexcept{
				entities[entity].key[Config::template tagBit<T>] = false;
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(EntityId entity) const noexcept{
				return entities[entity].key[Config::template componentBit<T>()];
			}
			
			template<concepts::Component<Config> T, class... TArgs>
			auto& addComponent(EntityId entity, TArgs&&... args) noexcept{
				entities[entity].key[Config::template componentBit<T>] = true;
				
				auto& c = componentManager.template getComponent<T>(getEntity(entity).dataId);
				c = T(MPL_FWD(args)...);
				
				return c;
			}
			
			template<concepts::Component<Config> T>
			auto& getComponent(EntityId entity){
				return componentManager.template getComponent<T>(getEntity(entity).dataId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(EntityId entity) noexcept{
				entities[entity].key[Config::template componentBit<T>] = false;
			}
			
			[[nodiscard]]
			bool doesExist(const Handle& handle) const noexcept{
				return doesExist(getHandleData(handle).entityId);
			}
			
			template<concepts::Tag<Config> T>
			[[nodiscard]]
			bool hasTag(const Handle& handle) const noexcept{
				return hasTag<T>(getHandleData(handle).entityId);
			}
			
			template<concepts::Tag<Config> T>
			void addTag(const Handle& handle) noexcept{
				addTag<T>(getHandleData(handle).entityId);
			}
			
			template<concepts::Tag<Config> T>
			void deleteTag(const Handle& handle) noexcept{
				deleteTag<T>(getHandleData(handle).entityId);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			bool hasComponent(const Handle& handle) const noexcept{
				return hasComponent<T>(getHandleData(handle).entityId);
			}
			
			template<concepts::Component<Config> T, class... TArgs>
			auto& addComponent(const Handle& handle, TArgs&&... args) noexcept{
				return addComponent<T>(getHandleData(handle).entityId, MPL_FWD(args)...);
			}
			
			template<concepts::Component<Config> T>
			[[nodiscard]]
			auto& getComponent(const Handle& handle){
				return getComponent<T>(getHandleData(handle).entityId);
			}
			
			template<concepts::Component<Config> T>
			void deleteComponent(const Handle& handle) noexcept{
				deleteComponent<T>(getHandleData(handle).entityId);
			}
	};
}

