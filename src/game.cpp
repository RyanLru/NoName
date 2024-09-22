#include <SFML/Graphics.hpp>
#include "game.h"

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Project NoName");

    // Créer un cercle
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Red);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 144));
    }
}
