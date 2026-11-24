#pragma once

#include <vector>
//#include "Scene.h"

namespace ECSEngine {

enum tSystemReturn { kContinue, kExit };

template <typename... Components>
class EngineView;

template <typename... Components>
class SceneView;

template <typename... Components>
class System {
public:
    virtual ~System() = default;
    virtual tSystemReturn Run(SceneView<Components...>* scene) = 0;
    virtual const std::string& GetName() const = 0;
};

template <typename... Components>
class SystemManager {
public:
    tSystemReturn Run(EngineView<Components...>* engine, SceneView<Components...>* scene) {
        for (auto& system : mSystems) {
            if (system->Run(scene) == kExit)  // system wants to exit
            {
                std::cout << system->GetName() << " requested exit from system manager\n";
                return kExit;
            }
        }
        return kContinue;
    }
    void AddSystem(std::unique_ptr<System<Components...>>&& system) {
        mSystems.push_back(std::move(system));
    }
    void ClearSystems() { mSystems.clear(); }

private:
    std::vector<std::unique_ptr<System<Components...>>> mSystems;
};

}  // namespace ECSEngine