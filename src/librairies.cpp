#include "librairies.h"

sf::Sprite Librairies::addSprite(int x, int y, int sizeX, int sizeY, const std::string& texture) {
    sf::Texture textureObj;
    textureObj.loadFromFile(texture);
    
    // Vérification de la texture
    if (!textureObj.loadFromFile(texture)) {
        std::cerr << "Erreur lors du chargement de la texture" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(textureObj);
    sprite.setPosition(x, y);
    sprite.setScale(sizeX, sizeY);
    return sprite;
}