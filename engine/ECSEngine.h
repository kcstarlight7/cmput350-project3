#pragma once

//#include "Scene.h"

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
    //continually runs the top scene When all scenes are complete, it returns.
}

}  // namespace ECSEngine