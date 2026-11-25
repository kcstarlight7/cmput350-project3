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

                    //approach requires sprite origin to be set in center when added
                    SpriteComponent& spriteComp1 =
                        entityManager.GetComponent<SpriteComponent>(menuComp.buttonEntities[0]);
                    SpriteComponent& spriteComp2 =
                        entityManager.GetComponent<SpriteComponent>(menuComp.buttonEntities[1]);
                    LocationComponent& locComp1 =
                        entityManager.GetComponent<LocationComponent>(menuComp.buttonEntities[0]);
                    LocationComponent& locComp2 =
                        entityManager.GetComponent<LocationComponent>(menuComp.buttonEntities[1]);
                    float factor = engine->GetWindowManager().GetWindowBounds().width / 1920;
                    float adjustment = engine->GetWindowManager().GetWindowBounds().height * 0.026;
                    if (menuComp.selected[0]) {
                        //selecting top button
                        spriteComp1.textureID = menuComp.buttons[1];
                        locComp1.loc.y = 477 * factor - adjustment;
                        spriteComp2.textureID = menuComp.buttons[0];
                        locComp2.loc.y = 765 * factor;
                        
                    } else if (menuComp.selected[1]) {
                        spriteComp2.textureID = menuComp.buttons[1];
                        locComp2.loc.y = 765 * factor - adjustment;
                        spriteComp1.textureID = menuComp.buttons[0];
                        locComp1.loc.y = 477 * factor;
                    } else {
                        spriteComp1.textureID = menuComp.buttons[0];
                        spriteComp2.textureID = menuComp.buttons[0];
                    }
                }
            }
            return kContinue;
        }
	};

}