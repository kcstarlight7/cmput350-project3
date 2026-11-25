#pragma once

#include "SpriteComponent.h"
#include "Entity.h"

namespace ECSEngine {

	class MenuComponent {
	public:
        EntityID buttonEntities[2]; //entities of buttons, [top, bottom]
        EntityID textEntities[2];
		SpriteID buttons[2]; //button sprites, [unselected, selected]
		SpriteID text[2]; //text sprites, [top, bottom]
        uint8_t selected[2] = {0, 0};  // tracking selection state
	};

}