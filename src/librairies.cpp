#include "librairies.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Fonction pour un Sprite
// Retourne un Sprite et une   texture
sf::Sprite Librairies::createSprite(const std::string path, int x, int y, float scale, sf::Texture &texture) {
    // Créer une texture
    if (!texture.loadFromFile(path)) {
        std::cerr << "Erreur lors du chargement de l'image " << path << std::endl;
    }

    // Créer un sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);

    return sprite;
}