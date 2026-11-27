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

                
                LocationComponent& locComp =
                    entityManager.template GetComponent<LocationComponent>(currentID);

                SpriteComponent& spriteComp =
                    entityManager.template GetComponent<SpriteComponent>(currentID);
                
                for (int i = 0; i < 4; i++) {
                    tlNoteSpawnLoc.push_back(Point2D(locComp.loc.x + (spriteComp.bounds.width / 4 * i), locComp.loc.y));
                }
                
                // spawn notes

                ChartNote nextNote = chartComp.data[chartComp.cur];
                // set sleep frame
                // 60 fps, bpm, division
                chartComp.sleepFrame = (int) ((60.f / (nextNote.bpm / 60.f) * nextNote.subdivision));

                
                for (int i = 0; i < 4; i++) {
                    if (nextNote.lane[i]) {
                        LocationComponent noteLoc;
                        noteLoc.loc = tlNoteSpawnLoc[i];

                        SpriteComponent noteSprite;
                        noteSprite.textureID = chartComp.noteTexID;
                        noteSprite.bounds = Rect(Point2D(0, 0), spriteComp.bounds.width / 4, 10.0f);
                        noteSprite.worldSpace = true;

                        MovementComponent noteMovement;
                        noteMovement.velocity.x = 0;
                        noteMovement.velocity.y = 5.f;

                        CollisionComponent noteCollision;
                        Rect noteBBox(Point2D(0.f, ((noteSprite.bounds.height * 5) / 2) +
                                                     noteSprite.bounds.height / 2),
                                      noteSprite.bounds.width, noteSprite.bounds.height * 5);
                        noteCollision.collisionBox = noteBBox;

                        EntityID note = entityManager.CreateEntity("note" + chartComp.cur);
                        entityManager.template AddComponent<LocationComponent>(note, noteLoc);
                        entityManager.template AddComponent<SpriteComponent>(note, noteSprite);
                        entityManager.template AddComponent<MovementComponent>(note, noteMovement);
                        entityManager.template AddComponent<CollisionComponent>(note, noteCollision);

                        engine->GetSpriteManager().ResizeAndGetColorSprite(
                            chartComp.noteTexID, Point2D(noteSprite.bounds.width, noteSprite.bounds.height));
                    }
                }

                chartComp.cur++;
                return kContinue;
            }
        }

        return kContinue;
    }
};

}  // namespace ECSEngine
