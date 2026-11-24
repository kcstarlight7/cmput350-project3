#include "SpriteManager.h"
#include <SFML/Graphics/Image.hpp>

namespace ECSEngine {

SpriteID SpriteManager::RegisterTexture(const std::string& texturePath, const Rect& sourceRect) {
    //TODO: load and copy the sprite into a single internal sprite sheet / texture
    int x = static_cast<int>(sourceRect.topLeft.x);
    int y = static_cast<int>(sourceRect.topLeft.y);
    int width = static_cast<int>(sourceRect.width);
    int height = static_cast<int>(sourceRect.height);
    std::string key = texturePath + "_" + std::to_string(x) + "_" + std::to_string(y) + "_" +
                      std::to_string(width) + "_" + std::to_string(height);
    auto it = mSpriteMap.find(key);
    if (it != mSpriteMap.end()) {
        return it->second;
    }
    if (mTexture.getSize().x == 0) {
        mRowMinY = 0;
        mRowMaxY = 0;
        mColMinX = 0;
    }

    

    return 0;
}

sf::Sprite& SpriteManager::GetSprite(SpriteID id) {
    static sf::Texture dummyTexture;
    static sf::Sprite dummy(dummyTexture);
    return dummy;
}

}  // namespace ECSEngine
