#pragma once

#include "Keyboard.h"
#include "MenuComponent.h"

namespace ECSEngine {

template <typename... Components>
class InputSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("InputSystem");
        return name;
    }

    tSystemReturn Run(SceneView<Components...>* engine) override {
        auto& entityManager = engine->GetEntityManager();
        for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend(); ++iterator) {
            // loops through all entities
            auto currentID = iterator->GetID();
            if (entityManager.template HasComponent<InputComponent>(currentID)) {
                // if entity has input component
                //std::cout << "has input" << "\n";
                InputComponent& inputComp =
                    entityManager.template GetComponent<InputComponent>(currentID);
                if (inputComp.sleepFrame > 0 && !inputComp.keydown.none()) {
                    // progress sleep timer if key is still being held down
                    inputComp.sleepFrame--;
                    return kContinue;
                } else if (inputComp.keydown.none()) {
                    // reset sleep timer to 0 if key is no longer being held
                    inputComp.sleepFrame = 0;
                }
                
                
                // std::cout << inputComp.keydown.any() << "\n";
                if (inputComp.keydown[Key::Up]) {
                    //std::cout << "up" << "\n";
                    if (entityManager.template HasComponent<MenuComponent>(currentID)) {
                        MenuComponent& menuComp = entityManager.template GetComponent<MenuComponent>(currentID);
                        //std::cout << +menuComp.lastSelected << std::endl;

                        if (menuComp.lastSelected == 0) {
                            menuComp.lastSelected = 1;
                        }
                        if (menuComp.lastSelected != 1) {
                            menuComp.lastSelected -= 1;
                        }
                    }
                    
                } 
                
                if (inputComp.keydown[Key::Down]) {
                    //std::cout << "down" << "\n";
                    if (entityManager.template HasComponent<MenuComponent>(currentID)) {
                        MenuComponent& menuComp = entityManager.template GetComponent<MenuComponent>(currentID);
                        //std::cout << +menuComp.lastSelected << std::endl;

                        if (menuComp.lastSelected == 0) {
                            menuComp.lastSelected = menuComp.menuLength;
                        }
                        if (menuComp.lastSelected != menuComp.menuLength) {
                            menuComp.lastSelected += 1;
                        }
                    }
                }

                if (!inputComp.keydown.none()) {
                    inputComp.sleepFrame = inputComp.delay;
                }
            }
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
