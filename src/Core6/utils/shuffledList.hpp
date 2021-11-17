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

#include <MPL/MPL.hpp>
#include <vector>
#include <functional>

namespace c6{
	template<class T>
	class ShuffledList{
		public:
			MPL_STRONG_TYPEDEF(std::size_t, ItemId);
		protected:
			MPL_STRONG_TYPEDEF(std::size_t, DataId);
			MPL_STRONG_TYPEDEF(std::size_t, HandleDataId);
			MPL_STRONG_TYPEDEF(int, HandleCounter);
			
			struct Item{
				T underlying;
				DataId dataId;
				HandleDataId handleDataId;
				bool exists;
			};
			
			struct HandleData{
				ItemId itemId;
				HandleCounter counter;
			};
		public:
			struct Handle{
				HandleDataId handleDataId;
				HandleCounter counter;
			};
			
			using TInit = std::function<void(T&)>;
		private:
			TInit onTInit;
			
			std::vector<Item> items;
			std::vector<HandleData> handlesData;
			
			std::size_t capacity = 0, size = 0, sizeNext = 0;
		protected:
			virtual void resize(size_t newCapacity){
				items.resize(newCapacity);
				handlesData.resize(newCapacity);
				
				for(ItemId i(capacity); i < newCapacity; i++){
					Item& it = items[i];
					HandleData& h = handlesData[i];
					
					reset(it, i);
					
					h.counter = 0;
					h.itemId = i;
				}
				
				capacity = newCapacity;
			}
			
			void growIfNeeded(){
				if(capacity > sizeNext)
					return;
				resize((capacity + 10) * 2);
			}
			
			[[nodiscard]]
			Item& getItem(ItemId id) noexcept{
				return items[id];
			}
			
			[[nodiscard]]
			const Item& getItem(ItemId id) const noexcept{
				return items[id];
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
		
			void reset(Item& item, ItemId id) noexcept{
				item.handleDataId = id;
				item.dataId = id;
				item.exists = false;
				onTInit(item.underlying);
			}
			
			void invalidateHandle(ItemId id) noexcept{
				handlesData[items[id].handleDataId].counter++;
			}
			
			void refreshHandle(ItemId id) noexcept{
				handlesData[items[id].handleDataId].itemId = id;
			}
		public:
			template<class Function, class... Args>
			requires std::invocable<Function, ItemId, const Args&...>
			void execute(const Function& function, const Args&... args){
				for(ItemId i(0); i < size; i++)
					function(i, args...);
			}
			
			virtual ItemId add(){
				ItemId free(sizeNext++);
				growIfNeeded();
				Item& item = items[free];
				item.exists = true;
				onTInit(item.underlying);
				
				return free;
			}
			
			Handle addWithHandle(){
				ItemId id = add();
				
				Item& item = items[id];
				HandleData& handleData = handlesData[item.handleDataId];
				handleData.itemId = id;
				
				return Handle{item.handleDataId, handleData.counter};
			}
			
			void remove(ItemId id){
				items[id].exists = false;
			}
			
			void remove(Handle handle){
				remove(getHandleData(handle).itemId);
			}
			
			[[nodiscard]]
			bool isHandleValid(const Handle& handle) const noexcept{
				return handle.counter == getHandleData(handle).counter;
			}
			
			[[nodiscard]]
			ItemId getItemId(const Handle& handle) const noexcept{
				return getHandleData(handle).itemId;
			}
			
			[[nodiscard]]
			bool doesExist(ItemId id) const noexcept{
				return getItem(id).exists;
			}
			
			[[nodiscard]]
			T& get(ItemId id) noexcept{
				return getItem(id).underlying;
			}
			
			[[nodiscard]]
			const T& get(ItemId id) const noexcept{
				return getItem(id).underlying;
			}
			
			void clear() noexcept{
				for(std::size_t i = 0; i < capacity; i++){
					Item& item = items[i];
					HandleData& handleData = handlesData[i];
					
					reset(item, i);
					
					handleData.itemId = i;
					handleData.counter = 0;
				}
				size = sizeNext = 0;
			}
			
			void refresh(){
				refreshNoShrink();
				resize(size);
			}
			
			virtual void refreshNoShrink() noexcept{
				if(sizeNext == 0){
					size = 0;
					return;
				}
				
				ItemId begin(0), end(sizeNext - 1);
				
				try{
					while(true){
						while(true){
							if(begin > end)
								throw ItemId(begin);
							if(!items[begin].exists)
								break;
							begin++;
						}
						while(true){
							if(items[end].exists)
								break;
							invalidateHandle(end);
							if(end <= begin)
								throw ItemId(begin);
							end--;
						}
						
						std::swap(items[end], items[begin]);
						
						refreshHandle(begin);
						
						invalidateHandle(end);
						refreshHandle(end);
						
						begin++;
						end--;
						if(begin > end)
							break;
					}
					throw ItemId(begin);
				} catch (const ItemId& last){
					size = sizeNext = last;
				}
			}
			
			explicit ShuffledList(const TInit& onTInit = []([[maybe_unused]]T& t){}) : onTInit(onTInit) {};
			virtual ~ShuffledList() = default;
	};
}

