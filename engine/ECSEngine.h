#pragma once

#include "Scene.h"

namespace ECSEngine {

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
    // ...

private: 
    std::vector<ECSScene> mScenes;
};

template <typename... Components>
ECSEngine<Components...>::ECSEngine(unsigned int width, unsigned int height,
                                    const std::string& name)
    : mWindowManager(width, height, name) {}

template <typename... Components>
ECSEngine<Components...>::~ECSEngine() {}

template <typename... Components>
void ECSEngine<Components...>::Run() {
    //continually runs the top scene When all scenes are complete, it returns.
}

}  // namespace ECSEngine