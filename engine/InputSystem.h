#pragma once

#include "Keyboard.h"
#include "MenuComponent.h"

namespace ECSEngine {

const float kMaxRunVelocity = 15;
const float kDashVelocity = 30;
const float kJumpVelocity = 1.5;
const float kGroundRunAcceleration = 5;
const float kAirRunAcceleration = 4;
const float kDashInterval = 25;
// currently just setting disabled timer to frame rate to handle dash interval
// pending movement system implementation to update?

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
                if (inputComp.sleepFrame > 0) {
                    inputComp.sleepFrame--;
                    return kContinue;
                }
                
                if (!inputComp.keydown.none()) {
                    inputComp.sleepFrame = inputComp.delay;
                }
                
                // std::cout << inputComp.keydown.any() << "\n";
                if (inputComp.keydown[Key::Up]) {
                    //inputComp.sleepFrame = inputComp.delay;

                    /*
                    if ((inputComp.delay != -1) && (inputComp.sleepFrame < inputComp.delay)) {
                        inputComp.sleepFrame++;
                        continue;
                    }*/
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
                    //inputComp.sleepFrame = inputComp.delay;

                    /*
                    if ((inputComp.delay != -1) && (inputComp.sleepFrame < inputComp.delay)) {
                        inputComp.sleepFrame++;
                        continue;
                    }*/
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
                    /*
                    if (inputComp.delay != -1) {
                        inputComp.sleepFrame = 0;
                    }*/
                }

                
            }
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
