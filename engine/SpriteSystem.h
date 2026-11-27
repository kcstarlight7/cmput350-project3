#pragma once

#include <bitset>
#include <unordered_map>

#include "CameraComponent.h"
#include "EntityManager.h"
#include "MathUtil.h"
#include "SpriteManager.h"
//#include "SystemManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

template <typename... Components>
class SpriteSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("SpriteSystem");
        return name;
    }

    tSystemReturn Run(SceneView<Components...>* engine) override { 
        uint8_t layers = 16;
        // 16 layers?
        // 0 furthest, 15 closest
        // midpoint = 7

        EntityManager<Components...>& entityManager = engine->GetEntityManager();
        WindowManager& windowManager = engine->GetWindowManager();
        SpriteManager& spriteManager = engine->GetSpriteManager();

        std::vector<std::vector<EntityID>> spriteInLayers(layers);
        std::vector<uint8_t> layerCounts(layers, 0);
        
        for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend(); ++iterator) {
            // loops through all entities
            auto currentID = iterator->GetID();
            if (entityManager.template HasComponent<SpriteComponent>(currentID) &&
                entityManager.template HasComponent<LocationComponent>(currentID)) {

                SpriteComponent& spriteComp = entityManager.GetComponent<SpriteComponent>(currentID);
                //iterate through all sprites and sort into layers
                // iterate through layers and draw sprites
                spriteInLayers[spriteComp.layer].push_back(currentID);
                layerCounts[spriteComp.layer]++;
            }
        }

        for (int i = 0; i < layerCounts.size(); i++) {
            for (uint8_t j = 0; j < layerCounts[i]; j++) {
                EntityID drawingID = spriteInLayers[i][j];
                // DRAWING
                sf::VertexArray vertices(sf::PrimitiveType::Triangles);

                SpriteComponent& drawingSpriteComp =
                    entityManager.GetComponent<SpriteComponent>(drawingID);
                sf::Sprite& drawingSprite = spriteManager.GetSprite(drawingSpriteComp.textureID);

                // append to vertex array
                sf::Vertex topLeft;
                sf::Vector2f location(
                    entityManager.GetComponent<LocationComponent>(drawingID).loc.x,
                    entityManager.GetComponent<LocationComponent>(drawingID).loc.y);
                // texcoords

                sf::Vector2f texCoord(drawingSprite.getTextureRect().position);
                sf::Vector2f texSize(drawingSprite.getTextureRect().size);
                sf::Vector2f scaledSize(drawingSprite.getGlobalBounds().size);

                sf::Vertex topRight;
                sf::Vertex bottomLeft;
                sf::Vertex bottomRight;

                topLeft.position = location;
                topLeft.texCoords = texCoord;

                vertices.append(topLeft);
                topRight.position = sf::Vector2f(location.x + scaledSize.x, location.y);
                topRight.texCoords = sf::Vector2f(texCoord.x + texSize.x, texCoord.y);
                vertices.append(topRight);
                bottomLeft.position = sf::Vector2f(location.x, location.y + scaledSize.y);
                bottomLeft.texCoords = sf::Vector2f(texCoord.x, texCoord.y + texSize.y);
                vertices.append(bottomLeft);
                vertices.append(topRight);
                bottomRight.position =
                    sf::Vector2f(location.x + scaledSize.x, location.y + scaledSize.y);
                bottomRight.texCoords =
                    sf::Vector2f(texCoord.x + texSize.x, texCoord.y + texSize.y);
                vertices.append(bottomRight);
                vertices.append(bottomLeft);

                windowManager.GetWindow()->draw(vertices, &spriteManager.GetTexture());
            }
        }
        
        //draw vertex array
        
        return kContinue;
    }
};

}  // namespace ECSEngine
