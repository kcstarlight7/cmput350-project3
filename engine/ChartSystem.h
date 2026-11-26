#pragma once

#include <fstream>

namespace ECSEngine {

template <typename... Components>
class ChartSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("ChartSystem");
        return name;
    }

    tSystemReturn Run(SceneView<Components...>* engine) override {
        /*
        Idea: add ChartComponent to a ChartSpawner object, and ChartSystem will spawn notes relative to the object 
        expect ChartComponent of said spawner to have .data filled out..
        .
        */

        auto& entityManager = engine->GetEntityManager();
        for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend(); ++iterator) {
            // loops through all entities
            auto currentID = iterator->GetID();
            if (entityManager.template HasComponent<ChartComponent>(currentID)) {
                std::vector<Point2D> tlNoteSpawnLoc;
                // reading is done in chart.cpp
                ChartComponent& chartComp =
                    entityManager.template GetComponent<ChartComponent>(currentID);

                if (chartComp.sleepFrame) {
                    chartComp.sleepFrame--;
                    return kContinue;
                }

                if (chartComp.cur == chartComp.data.size()) {
                    return kExit;
                }

                /*
                LocationComponent& locComp =
                    entityManager.template GetComponent<LocationComponent>(currentID);

                SpriteComponent& spriteComp =
                    entityManager.template GetComponent<SpriteComponent>(currentID);
                
                for (int i = 0; i < 4; i++) {
                    tlNoteSpawnLoc.push_back(Point2D(locComp.loc.x + (spriteComp.bounds.width / 4 * i), locComp.loc.y));
                }
                */
                // spawn notes

                ChartNote nextNote = chartComp.data[chartComp.cur++];
                // set sleep frame
                // 60 fps, bpm, division
                chartComp.sleepFrame = (int) ((60.f / (nextNote.bpm / 60.f) * nextNote.subdivision));

                LocationComponent noteLoc;
                //noteLoc.loc = tlNoteSpawnLoc[nextNote.lane];

                SpriteComponent noteSprite;
                for (int i = 0; i < 4; i++) {
                    if (nextNote.lane[i]) {
                        std::cout << i + 1 << '\n';
                    }
                } 
                /*
                if (nextNote.hold) {

                } else {
                    noteSprite.textureID = chartComp.noteTexID;
                    noteSprite.bounds = Rect(Point2D(0, 0), spriteComp.bounds.width / 4, 10.0f);
                    noteSprite.worldSpace = true;

                    std::cout << "spawn\n";


                }*/
                
            }
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
