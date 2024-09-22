#include "librairies.h"

sf::Sprite Librairies::addSprite(int x, int y, int sizeX, int sizeY, const std::string& texture) {
    sf::Texture textureObj;
    textureObj.loadFromFile(texture);
    sf::Sprite sprite;
    sprite.setTexture(textureObj);
    sprite.setPosition(x, y);
    sprite.setScale(sizeX, sizeY);
    return sprite;
}