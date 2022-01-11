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

#include <Core6/framework.hpp>
#include <iostream>
#include "dragAndDrop.hpp"

c6::System<ecsConfig, c6::Signature<Draggable, c6::component::Transformable>> drag{
	[](Draggable& draggable, c6::component::Transformable& transformable){
		if(draggable.dragged){
			transformable->setPosition(draggable.position - draggable.relative);
		}
	}};

c6::System<ecsConfig, c6::Signature<c6::component::EntityState, Draggable, c6::component::Transformable>, const sf::Event&> isDragged{
		[](c6::component::EntityState& entityState, Draggable& draggable, c6::component::Transformable& transformable, const sf::Event& event){
			if(entityState.active){
				if(!draggable.anyDragged && draggable.shouldDrag(event)){
					draggable.dragged = true;
					draggable.anyDragged = true;
					auto p = c6::Framework::getRenderer()->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
					draggable.relative = p - transformable->getPosition();
					draggable.position = p;
				}
				else if(draggable.dragged && draggable.shouldEndDrag(event)){
					draggable.dragged = false;
					draggable.anyDragged = false;
				}
				
				if(draggable.dragged && event.type == sf::Event::MouseMoved)
					draggable.position = c6::Framework::getRenderer()->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
			}
		}};
