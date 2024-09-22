#include "librairies.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Fonction pour un Sprite
sf::Sprite Librairies::createSprite(const std::string path, int x, int y, float scale, sf::Texture &texture) {
    // Créer une texture
    if (!texture.loadFromFile(path)) {
        std::cerr << "Erreur lors du chargement de l'image " << path << std::endl;
    }

    // Créer un sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    // Recalculer la position pour centrer le sprite
    x -= texture.getSize().x * scale / 2;
    y -= texture.getSize().y * scale / 2;
    
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);

    return sprite;
}

// Fonction pour un Texte
sf::Text Librairies::createText(const std::string text, int x, int y, int size, sf::Font &font) {
    // Créer une font
    if (!font.loadFromFile("../assets/fonts/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police arial.ttf" << std::endl;
    }

    // Créer un texte
    sf::Text texte;
    texte.setFont(font);
    texte.setString(text);
    texte.setCharacterSize(size);
    texte.setPosition(x, y);

    return texte;
}

// Fonction pour créer une Surface Cliquable
sf::RectangleShape Librairies::createClickableSurface(int x, int y, int width, int height) {
    // Créer une surface cliquable
    sf::RectangleShape clickableSurface;
    clickableSurface.setPosition(x, y);
    clickableSurface.setSize(sf::Vector2f(width, height));

    return clickableSurface;
}

// Fonction pour vérifier si la souris est sur la surface cliquable
bool Librairies::isMouseOnSurface(sf::RectangleShape clickableSurface, sf::RenderWindow &window) {
    // Récupérer la position de la souris
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Vérifier si la souris est sur la surface cliquable
    if (clickableSurface.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        return true;
    }

    return false;
}

// Fonction pour vérifier si le clic gauche est enfoncé sur la surface cliquable
bool Librairies::isLeftClickOnSurface(sf::RectangleShape clickableSurface, sf::RenderWindow &window) {
    // Vérifier si le clic gauche est enfoncé
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Récupérer la position de la souris
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Vérifier si le clic est sur la surface cliquable
        if (clickableSurface.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            return true;
        }
    }

    return false;
}
