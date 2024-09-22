#include <SFML/Graphics.hpp>
#include "game.h"
#include "librairies.h"
#include <iostream>

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Project NoName");

    // Créer un objet de la classe Librairies
    Librairies librairies;

    // Ajouter un sprite
    sf::Texture texture;
    texture.loadFromFile("../assets/Button.png");
    sf::Sprite sprite(texture);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear();

        // Afficher le sprite
        window.draw(sprite);

        // Afficher la fenêtre
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 60));
    }

    // Fermer la fenêtre
    window.close();
}
