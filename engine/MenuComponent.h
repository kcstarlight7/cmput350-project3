#pragma once

#include "SpriteComponent.h"
#include "Entity.h"

namespace ECSEngine {

	class MenuComponent {
	public:
        std::string key;
        int menuLength = 2;
        std::vector<EntityID> buttonEntities; //entities of buttons, [top, bottom]
        std::vector<EntityID> textEntities;
		SpriteID buttons[2]; //button sprites, [unselected, selected]
		std::vector<SpriteID> text; //text sprites, [top, bottom]
        uint8_t lastSelected = 0; // last selected option, 1 index'd (0 represents never selected)
        Point2D startTopLeft;
        int spacingPx;
    };

}