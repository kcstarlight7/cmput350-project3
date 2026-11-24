#pragma once


//#include "ECSEngine.h"


namespace ECSEngine {

enum tSceneReturn {
    kSceneContinue, kSceneDone
};

template <typename... Components>
class SceneView {
public:
    virtual EntityManager<Components...>& GetEntityManager() = 0;
    virtual WindowManager& GetWindowManager() = 0;
    virtual SystemManager<Components...>& GetSystemManager() = 0;
    virtual SpriteManager& GetSpriteManager() = 0;
    virtual SoundManager& GetSoundManager() = 0;
    virtual tSceneReturn DoOneFrame(EngineView<Components...>* engine) = 0;
};


template <typename... Components>
class ECSScene : public SceneView<Components...> {
public:
    EntityManager<Components...>& GetEntityManager() override { return mEntityManager; }
    WindowManager& GetWindowManager() override { return mWindowManager; }
    SpriteManager& GetSpriteManager() override { return mSpriteManager; }
    SoundManager& GetSoundManager() override { return mSoundManager; }
    SystemManager<Components...>& GetSystemManager() override { return mSystemManager; }
    [[nodiscard]] tSceneReturn DoOneFrame(EngineView<Components...>* engine) override {
        if (mSystemManager.Run(engine, this) == kExit) return kSceneDone;
        return kSceneContinue;
    }

private:
    template <typename... Components>
    friend class ECSEngine;
    ECSScene(WindowManager& windowManager) : mWindowManager(windowManager) {}
    EntityManager<Components...> mEntityManager;
    SystemManager<Components...> mSystemManager;

    WindowManager mWindowManager;
    SpriteManager mSpriteManager;
    SoundManager mSoundManager;
};

}  // namespace ECSEngine