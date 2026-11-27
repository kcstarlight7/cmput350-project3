#pragma once

namespace ECSEngine {

	template <typename... Components>
	class MenuSystem : public System<Components...> {
    public:
        const std::string& GetName() const override {
            static std::string name("MenuSystem");
            return name;
        }

        tSystemReturn Run(SceneView<Components...>* engine) override {
            auto& entityManager = engine->GetEntityManager();
            for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend();
                 ++iterator) {
                auto currentID = iterator->GetID();
                if (entityManager.HasComponent<MenuComponent>(currentID)) {
                    //SPRITE/APPEARANCE UPDATE
                    MenuComponent& menuComp = entityManager.GetComponent<MenuComponent>(currentID);
                    float factor = engine->GetWindowManager().GetWindowBounds().width / 1920;
                    float adjustment = engine->GetWindowManager().GetWindowBounds().height * 0.026;

                    //approach requires sprite origin to be set in center when added

                    //SPRITE/APPEARANCE REWRITE
                    
                    for (int i = 0; i < menuComp.menuLength; i++) {
                        SpriteComponent& spriteComp =
                            entityManager.GetComponent<SpriteComponent>(menuComp.buttonEntities[i]);
                        LocationComponent& locComp =
                            entityManager.GetComponent<LocationComponent>(
                                menuComp.buttonEntities[i]);
                        if ((menuComp.lastSelected - 1) == i) {
                            spriteComp.textureID = menuComp.buttons[1];
                            locComp.loc.y =
                                ((menuComp.startTopLeft.y + menuComp.spacingPx * i)) * factor - adjustment; 
                        } else {
                            spriteComp.textureID = menuComp.buttons[0];
                            locComp.loc.y =
                                ((menuComp.startTopLeft.y + menuComp.spacingPx * i)) * factor;
                        }
                    }
                }
            }
            return kContinue;
        }
	};

}