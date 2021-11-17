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

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <Core6/gui/graphics/widgetGraphics.hpp>
#include <Core6/gui/logic/widgetLogic.hpp>
#include <Core6/ecs/entityComponentSystem.hpp>
#include <Core6/gui/graphics/frame.hpp>

namespace c6{
	template<class ecsConfig>
	class Widget{
		private:
			using Handle = typename EntityComponentSystem<ecsConfig>::Handle;
			
			Widget<ecsConfig>* parent; // if nullptr then window
			std::set<std::reference_wrapper<Widget<ecsConfig>>> children;
			Handle handle; // handle for this
			WidgetGraphics* graphics;
			WidgetLogic* logic;
		public:
			// Copy-swap idiom
			Widget() noexcept : parent(nullptr), graphics(nullptr), logic(nullptr) {}
			
			Widget(const Widget<ecsConfig>& other) noexcept{
				parent = other.parent;
				children = other.children;
				handle = other.handle;
				graphics = other.graphics;
				logic = other.logic;
			}
			
			Widget(Widget<ecsConfig>&& other) noexcept : parent(nullptr), graphics(nullptr), logic(nullptr){
				swap(*this, other);
			}
			
			~Widget(){
				if(graphics != nullptr){
					delete graphics;
					graphics = nullptr;
				}
				if(logic != nullptr){
					delete logic;
					logic = nullptr;
				}
			}
			
			friend void swap(Widget<ecsConfig>& first, Widget<ecsConfig>& second) noexcept{
				std::swap(first.parent, second.parent);
				std::swap(first.children, second.children);
				std::swap(first.handle, second.handle);
				std::swap(first.graphics, second.graphics);
				std::swap(first.logic, second.logic);
			}
			
			Widget<ecsConfig>& operator = (Widget<ecsConfig> other){
				swap(*this, other);
				return *this;
			}
			
			// generators
			//static Widget Button(EntityComponentSystem<ecsConfig>& ecs, Handle handle);
			static Widget<ecsConfig>& Frame(EntityComponentSystem<ecsConfig>& ecs, Handle handle, sf::FloatRect rect){
				ecs.template addComponent<component::Transformable>(handle, std::make_shared<sf::Transformable>());
				Widget<ecsConfig>& widget = ecs.template addComponent<Widget<ecsConfig>>(handle);
				widget.handle = handle;
				widget.graphics = new widgets::Frame(rect);
				return widget;
			}
			
			// getters and setters
			void setParent(Widget<ecsConfig>& widget){
				parent = &widget;
			}
			[[nodiscard]]
			const Widget<ecsConfig>& getParent() const{
				return *parent;
			}
			[[nodiscard]]
			bool hasParent() const{
				return parent != nullptr;
			}
			[[nodiscard]]
			const std::set<std::reference_wrapper<Widget<ecsConfig>>>& getChildren() const{
				return children;
			}
			
			[[nodiscard]]
			const Handle& getHandle() const{
				return handle;
			}
			
			[[nodiscard]]
			const WidgetGraphics& getGraphics() const{
				return *graphics;
			}
			[[nodiscard]]
			WidgetGraphics& getGraphics(){
				return *graphics;
			}
			[[nodiscard]]
			bool hasGraphics() const{
				return graphics != nullptr;
			}
			
			[[nodiscard]]
			const WidgetLogic& getLogic() const{
				return *logic;
			}
			[[nodiscard]]
			WidgetLogic& getLogic(){
				return *logic;
			}
			[[nodiscard]]
			bool hasLogic() const{
				return logic != nullptr;
			}
	};
}