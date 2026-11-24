#pragma once

#include <unordered_map>

#include "MathUtil.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

using SpriteID = size_t;

class SpriteManager {
public:
    SpriteManager() = default;
    ~SpriteManager() = default;
    [[nodiscard]] SpriteID RegisterTexture(const std::string& texturePath, const Rect& sourceRect);
    sf::Sprite& GetSprite(SpriteID id);
    sf::Texture& GetTexture() { return mTexture; }

private:
    int mRowMinY, mRowMaxY, mColMinX;
    sf::Texture mTexture;
    std::unordered_map<std::string, SpriteID> mSpriteMap;
    std::vector<sf::Sprite> mSprites;
};

}  // namespace ECSEngine
