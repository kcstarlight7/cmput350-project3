#pragma once

#include <cmath>

#include "EntityManager.h"
#include "ScoreComponent.h"
//#include "Scene.h"

namespace ECSEngine {

template <typename... Components>
class CollisionSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("CollisionSystem");
        return name;
    }

    tSystemReturn Run(SceneView<Components...>* engine) override {
        EntityManager<Components...>& entityManager = engine->GetEntityManager();
        WindowManager& windowManager = engine->GetWindowManager();

        for (auto iterator1 = entityManager.cbegin(); iterator1 != entityManager.cend();
             ++iterator1) {
            // loops through all entities
            auto currentID = iterator1->GetID();
            if (entityManager.template HasComponent<CollisionComponent>(currentID) &&
                entityManager.template HasComponent<LocationComponent>(
                    currentID)) {  // able to collide
                CollisionComponent& curIDCollisionComp =
                    entityManager.template GetComponent<CollisionComponent>(currentID);

                if (curIDCollisionComp.staticEntity) {
                    continue;
                }

                LocationComponent& curIDLocationComp =
                    entityManager.template GetComponent<LocationComponent>(currentID);

                Rect curIDCollisionBox = curIDCollisionComp.collisionBox;
                Rect curIDPrevCollisionBox = curIDCollisionComp.previousCollisionBox;
                curIDCollisionBox.topLeft += curIDLocationComp.loc;

                // std::cout << curIDCollisionBox.topLeft << "\n";

                for (auto iterator2 = entityManager.cbegin(); iterator2 != entityManager.cend();
                     ++iterator2) {
                    auto otherID = iterator2->GetID();
                    if (entityManager.template HasComponent<CollisionComponent>(otherID) &&
                        entityManager.template HasComponent<LocationComponent>(otherID) &&
                        currentID != otherID) {  // able to collide and not self
                        // determine if collide on current frame:

                        CollisionComponent& otherIDCollisionComp =
                            entityManager.template GetComponent<CollisionComponent>(otherID);
                        LocationComponent& otherIDLocationComp =
                            entityManager.template GetComponent<LocationComponent>(otherID);

                        Rect otherIDCollisionBox = otherIDCollisionComp.collisionBox;
                        otherIDCollisionBox.topLeft += otherIDLocationComp.loc;

                        bool collide = ComputeCollision(curIDCollisionBox, otherIDCollisionBox);
                        if (collide) {
                            
                        }

                        // draw red rect

                        if (collide) {
                            Point2D curIDDrawLoc =
                                windowManager.WorldToWindow(curIDLocationComp.loc);
                            Point2D otherIDDrawLoc =
                                windowManager.WorldToWindow(otherIDLocationComp.loc);
                            windowManager.DebugFrameRect(
                                Rect(curIDDrawLoc, curIDCollisionComp.collisionBox.width,
                                     curIDCollisionComp.collisionBox.height),
                                255, 0, 0, 255);
                            windowManager.DebugFrameRect(
                                Rect(otherIDDrawLoc, otherIDCollisionComp.collisionBox.width,
                                     otherIDCollisionComp.collisionBox.height),
                                0, 255, 255, 255);
                        }
                    }
                }

                if (entityManager.GetEntityType(currentID) == "player" &&
                    (curIDCollisionComp.onLeftWall || curIDCollisionComp.onRightWall) &&
                    !curIDCollisionComp.onGround) {
                    engine->GetSoundManager().GetSound("error").play();
                }
            }
        }

        return kContinue;
    }

private:
    bool ComputeCollision(const Rect a, const Rect b) {
        return a.topLeft.x < b.topLeft.x + b.width && a.topLeft.x + a.width > b.topLeft.x &&
               a.topLeft.y < b.topLeft.y + b.height && a.topLeft.y + a.height > b.topLeft.y;
    }

    bool ComputeCollision(const Circle a, const Line b) {
        Point2D closestPt = b.ClosestPoint(a.center);

        return closestPt.Distance(a.center) < a.radius;
    }

    bool ComputeCollision(const Rect a, const Circle b) {
        Line a1(a.topLeft, Point2D(a.topLeft.x + a.width, a.topLeft.y));
        Line a2(a.topLeft, Point2D(a.topLeft.x, a.topLeft.y + a.height));
        Line a3(Point2D(a.topLeft.x + a.width, a.topLeft.y),
                Point2D(a.topLeft.x + a.width, a.topLeft.y + a.height));
        Line a4(Point2D(a.topLeft.x, a.topLeft.y + a.height),
                Point2D(a.topLeft.x + a.width, a.topLeft.y + a.height));

        return a.IsInside(b.center) || ComputeCollision(b, a1) || ComputeCollision(b, a2) ||
               ComputeCollision(b, a3) || ComputeCollision(b, a4);
    }

    bool ComputeCollision(const Rect a, const Line b, Point2D* crossPt) {
        Point2D rectCenter(a.topLeft.x + (a.width / 2), a.topLeft.y + (a.height / 2));
        // std::cout << rectCenter << "\n";
        bool res = a.IsInside(b.ClosestPoint(rectCenter));
        if (res) {
            *crossPt = b.ClosestPoint(rectCenter);
        }
        return res;
    }

    bool ComputeCollision(const Circle a, const Circle b) {
        return std::pow(b.center.x - a.center.x, 2) + std::pow(b.center.y - a.center.y, 2) <=
               std::pow(a.radius + b.radius, 2);
    }

    bool ComputeCollision(const Circle a, const Circle b, Point2D* crossPt) {
        crossPt = nullptr;
        return ComputeCollision(a, b);
    }

    bool ComputeCollision(const Circle a, const Line b, Point2D* crossPt) {
        Point2D closestPt = b.ClosestPoint(a.center);
        crossPt->x = closestPt.x;
        crossPt->y = closestPt.y;

        return closestPt.Distance(a.center) < a.radius;
    }

    bool ComputeCollision(const Line a, const Line b, Point2D* crossPt) {
        return a.Crosses(b, *crossPt);
    }

    bool ComputeCollision(const Circle a, const Rect b) { return ComputeCollision(b, a); }

    bool ComputeCollision(const Circle a, const Rect b, Point2D* crossPt) {
        crossPt = nullptr;
        return ComputeCollision(b, a);
    }

    bool ComputeCollision(const Line a, const Rect b, Point2D* crossPt) {
        return ComputeCollision(b, a, crossPt);
    }

    bool ComputeCollision(const Line a, const Circle b, Point2D* crossPt) {
        return ComputeCollision(b, a, crossPt);
    }
};

}  // namespace ECSEngine
