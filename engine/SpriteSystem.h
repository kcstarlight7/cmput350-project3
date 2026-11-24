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
        EntityManager<Components...>& entityManager = engine->GetEntityManager();
        WindowManager& windowManager = engine->GetWindowManager();
        SpriteManager& spriteManager = engine->GetSpriteManager();
        sf::VertexArray vertices(sf::PrimitiveType::Triangles);
        for (auto iterator = entityManager.cbegin(); iterator != entityManager.cend(); ++iterator) {
            // loops through all entities
            auto currentID = iterator->GetID();
            if (entityManager.template HasComponent<SpriteComponent>(currentID) &&
                entityManager.template HasComponent<LocationComponent>(currentID)) {
                //append to vertex array
                sf::Vertex topLeft;
                sf::Vector2f location(entityManager.GetComponent<LocationComponent>(currentID).loc.x,
                                      entityManager.GetComponent<LocationComponent>(currentID).loc.y);
                //texcoords
                sf::Sprite& sprite = spriteManager
                                         .GetSprite(entityManager.GetComponent<SpriteComponent>(currentID).textureID);
                std::cout << sprite.getTextureRect().position.x << "\n";
                std::cout << sprite.getTextureRect().position.y << "\n";
                std::cout << "\n";
                sf::Vector2f texCoord(sprite.getTextureRect().position);
                sf::Vector2f texSize(sprite.getTextureRect().size);

                sf::Vertex topRight;
                sf::Vertex bottomLeft;
                sf::Vertex bottomRight;

                topLeft.position = location;
                std::cout << location.x << "\n";
                std::cout << location.y << "\n";
                std::cout << "\n";
                topLeft.texCoords = texCoord;
                std::cout << texCoord.x << "\n";
                std::cout << texCoord.y << "\n";
                std::cout << "\n";
                vertices.append(topLeft);
                topRight.position = sf::Vector2f(location.x + texSize.x, location.y);
                topRight.texCoords = sf::Vector2f(texCoord.x + texSize.x, texCoord.y);
                vertices.append(topRight);
                bottomLeft.position = sf::Vector2f(location.x, location.y + texSize.y);
                bottomLeft.texCoords = sf::Vector2f(texCoord.x, texCoord.y + texSize.y);
                vertices.append(bottomLeft);
                bottomRight.position = sf::Vector2f(location.x + texSize.x, location.y + texSize.y);
                bottomRight.texCoords =
                    sf::Vector2f(texCoord.x + texSize.x, texCoord.y + texSize.y);
                vertices.append(bottomRight);
            }
        }
        
        //draw vertex array
        windowManager.GetWindow()->draw(vertices, &spriteManager.GetTexture());
        return kContinue;
    }
};

}  // namespace ECSEngine
