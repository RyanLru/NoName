#include <SFML/Graphics.hpp>
#include "game.h"
#include "librairies.h"

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Project NoName");

    // Créer un objet de la classe Librairies
    Librairies librairies;

    // Ajouter un sprite
    sf::Sprite sprite = librairies.addSprite(400, 400, 1.0f, 1.0f, "../assets/Button.png");

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
        sf::sleep(sf::milliseconds(1000 / 144));
    }

    // Fermer la fenêtre
    window.close();
}
