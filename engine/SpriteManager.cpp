#include "SpriteManager.h"
#include <SFML/Graphics/Image.hpp>

namespace ECSEngine {

SpriteID SpriteManager::RegisterTexture(const std::string& texturePath, const Rect& sourceRect) {
    // load and copy the sprite into a single internal sprite sheet / texture
    unsigned int max = mTexture.getMaximumSize(); // use maximum size gpu can handle?

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
    if (mTexture.getSize().x == 0) { // if texture doesn't have anything
        mRowMinY = 0;
        mRowMaxY = 0;
        mColMinX = 0;
        mTexture.resize(sf::Vector2u(max, max));
    }
    if (mColMinX + width > max) { // if x would exceed texture bound, go to next "line"
        mColMinX = 0;
        mRowMinY = mRowMaxY;
    }
    if (mRowMinY + height > max) {
        std::exception("Sprite sheet maximum Y reached!");
    }

    // copies target area into image, then updates texture with image
    sf::Image initialImage;
    initialImage.loadFromFile(texturePath);
    sf::IntRect area({x, y}, {width, height});
    sf::Image resultImage(sf::Vector2u(width, height), sf::Color::White);
    resultImage.copy(initialImage, {0, 0}, area);
    mTexture.update(resultImage, sf::Vector2u(mColMinX, mRowMinY));
    sf::Sprite sprite(mTexture);
    sprite.setTextureRect(sf::IntRect({mColMinX, mRowMinY}, {width, height}));
    //std::cout << sprite.getTextureRect().size.y << "\n";
    mSprites.push_back(sprite);

    mColMinX = mColMinX + width;
    mRowMaxY = std::max(mRowMaxY, mRowMaxY + height);

    SpriteID id = mSprites.size() - 1;
    mSpriteMap.insert(std::pair<std::string, SpriteID>(key, id));

    return id;
}

sf::Sprite& SpriteManager::GetSprite(SpriteID id) { return mSprites[id]; }

}  // namespace ECSEngine
