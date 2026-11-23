#pragma once

#include "Scene.h"

namespace ECSEngine {

template <typename... Components>
class ECSEngine : public EngineView<Components...> {
public:
    // ...
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

}  // namespace ECSEngine