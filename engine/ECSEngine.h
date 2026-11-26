#pragma once

//#include "Scene.h"
#include "InputComponent.h"

namespace ECSEngine {

template <typename... Components>
class EngineView {
public:
    virtual std::shared_ptr<SceneView<Components...>> GetScene() = 0;
    virtual std::shared_ptr<SceneView<Components...>> MakeScene() = 0;
    virtual void AddScene(std::shared_ptr<SceneView<Components...>> scene) = 0;
    virtual void PopScene() = 0;
};

template <typename... Components>
class ECSEngine : public EngineView<Components...> {
public:
    // responsible for the final display call on the window.

    ECSEngine(unsigned int width, unsigned int height, const std::string& name);
    ~ECSEngine();
    void Run();

    std::shared_ptr<SceneView<Components...>> GetScene() override { return mScenes.back(); }

    std::shared_ptr<SceneView<Components...>> MakeScene() override {
        auto ptr = new ECSScene<Components...>(mWindowManager);
        return std::shared_ptr<ECSScene<Components...>>(ptr);
    }

    void AddScene(std::shared_ptr<SceneView<Components...>> scene) override {
        mScenes.push_back(scene);
    }

    void PopScene() { mScenes.pop_back(); }
    

private: 
    bool ProcessEvents(SceneView<Components...>& scene);
    std::vector<std::shared_ptr<SceneView<Components...>>> mScenes;
    WindowManager mWindowManager;
};

template <typename... Components>
ECSEngine<Components...>::ECSEngine(unsigned int width, unsigned int height,
                                    const std::string& name)
    : mWindowManager(width, height, name) {}

template <typename... Components>
ECSEngine<Components...>::~ECSEngine() {}

template <typename... Components>
void ECSEngine<Components...>::Run() {
    while (true) {
        mWindowManager.GetWindow()->clear();
        // continually runs the top scene When all scenes are complete, it returns.
        std::shared_ptr<SceneView<Components...>> scene = GetScene();
        if (!scene) {
            return;
        }
        if (!ProcessEvents(*scene)) {
            return;
        }
        tSceneReturn status = scene->DoOneFrame(this);
        mWindowManager.GetWindow()->display();
        if (status == kSceneContinue) {
            continue;
        } else {
            PopScene();
            break;
        }
    }
    
}

template <typename... Components>
bool ECSEngine<Components...>::ProcessEvents(SceneView<Components...>& scene) {
    // process events from sfml and updating input component

    std::bitset<sf::Keyboard::ScancodeCount> keydowns{};
    std::bitset<sf::Keyboard::ScancodeCount> keyups{};

    while (const std::optional event = mWindowManager.GetWindow()->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            return false;
            mWindowManager.GetWindow()->close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            keydowns.set((int)keyPressed->scancode);
        }

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            keyups.set((int)keyReleased->scancode);
        }
    }

    auto& entityManager = scene.GetEntityManager();
    for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend(); ++iterator) {
        // loops through all entities
        auto currentID = iterator->GetID();
        if (entityManager.template HasComponent<InputComponent>(currentID)) {
            InputComponent& inpComp =
                entityManager.template GetComponent<InputComponent>(currentID);

            inpComp.lastKeydown = inpComp.keydown;
            inpComp.keydown |= keydowns;
            for (unsigned int i = 0; i < sf::Keyboard::ScancodeCount; i++) {
                if (inpComp.keydown.test(i) == keyups.test(i)) {
                    inpComp.keydown.reset(i);
                }
            }
        }
    }

    return true;
}

}  // namespace ECSEngine