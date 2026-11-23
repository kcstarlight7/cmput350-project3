#pragma once

#include <iostream>
#include <vector>

#include "CameraComponent.h"
#include "CollisionComponent.h"
#include "EntityManager.h"
#include "InputComponent.h"
#include "LocationComponent.h"
#include "MathUtil.h"
#include "ScoreComponent.h"
#include "SoundManager.h"
#include "SpawnComponent.h"
#include "SpriteComponent.h"
#include "SpriteManager.h"
#include "SystemManager.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ECSEngine {

template <typename... Components>
class SceneView {
public:
    virtual SoundManager& GetSoundManager() = 0;
    virtual SpriteManager& GetSpriteManager() = 0;
    virtual EntityManager<Components...>& GetEntityManager() = 0;
    virtual WindowManager& GetWindowManager() = 0;
    virtual SystemManager<Components...>& GetSystemManager() = 0;
    virtual tSceneReturn DoOneFrame(SceneView<Components...>* engine) = 0;
};

template <typename... Components>
class ECSScene : public SceneView<Components...> {
public:
    ECSScene(unsigned int width, unsigned int height, const std::string& name);
    ~ECSScene();

    void Run();

    SoundManager& GetSoundManager() override { return mSoundManager; }

    SpriteManager& GetSpriteManager() override { return mSpriteManager; }

    EntityManager<Components...>& GetEntityManager() override { return mEntityManager; }

    WindowManager& GetWindowManager() override { return mWindowManager; }

    SystemManager<Components...>& GetSystemManager() { return mSystemManager; }

    [[nodiscard]] tSceneReturn DoOneFrame(SceneView<Components...>* engine) override {
        if (mSystemManager.Run(engine, this) == kExit) return kSceneDone;
        return kSceneContinue;
    }

private:
    bool ProcessEvents();
    void DebugDraw();

    EntityManager<Components...> mEntityManager;
    SystemManager<Components...> mSystemManager;
    SpriteManager mSpriteManager;
    SoundManager mSoundManager;
    WindowManager mWindowManager;

    // For debugging - pause and step the engine
    bool running, step;
    int debug;
};

template <typename... Components>
ECSScene<Components...>::ECSScene(unsigned int width, unsigned int height,
                                    const std::string& name)
    : mWindowManager(width, height, name) {}

template <typename... Components>
ECSScene<Components...>::~ECSScene() {}

template <typename... Components>
void ECSScene<Components...>::Run() {
    // repeats main game loop
    // (runs systems from system manager, then draws window)
    running = true;
    while (running) {
        mWindowManager.GetWindow()->clear();
        ProcessEvents();
        if (!mSystemManager.Run(this)) {
            running = false;
        }
        mWindowManager.GetWindow()->display();
    }
}

template <typename... Components>
bool ECSScene<Components...>::ProcessEvents() {
    // process events from sfml and updating input component

    std::bitset<sf::Keyboard::ScancodeCount> keydowns{};
    std::bitset<sf::Keyboard::ScancodeCount> keyups{};

    while (const std::optional event = mWindowManager.GetWindow()->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            running = false;
            mWindowManager.GetWindow()->close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            keydowns.set((int)keyPressed->scancode);
        }

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            keyups.set((int)keyReleased->scancode);
        }
    }

    // std::cout << keydowns << std::endl;

    auto& entityManager = GetEntityManager();
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

template <typename... Components>
void ECSScene<Components...>::DebugDraw() {}

}  // namespace ECSEngine