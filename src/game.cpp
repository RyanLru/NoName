#include <SFML/Graphics.hpp>
#include "game.h"
#include "librairies.h"
#include <iostream>

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Project NoName");

    // Créer un objet de la classe Librairies
    Librairies librairies;

    // Création d'un Surface Cliquable
    sf::RectangleShape clickableSurface = librairies.createClickableSurface(100, 100, 200, 50);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear();

        // Afficher la fenêtre
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 60));
    }

    // Fermer la fenêtre
    window.close();
}
