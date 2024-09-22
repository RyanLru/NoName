#include <SFML/Graphics.hpp>
#include "game.h"
#include "librairies.h"
#include <iostream>

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Project NoName");

    // Créer un objet de la classe Librairies
    Librairies librairies;

    // Création du Bouton Start
    sf::Texture textureStart;
    sf::Sprite spriteStart = librairies.createSprite("../assets/button/Start.png", 960, 440, 2.5, textureStart);
    sf::Texture textureStartHover;
    sf::Sprite spriteStartHover = librairies.createSprite("../assets/button/Start_Hover.png", 960, 440, 2.5, textureStartHover);
    sf::Texture textureStartClicked;
    sf::Sprite spriteStartClicked = librairies.createSprite("../assets/button/Start_Pushed.png", 960, 440, 2.5, textureStartClicked);
    sf::RectangleShape clickableSurfaceStart = librairies.createClickableSurface(960 - textureStart.getSize().x * 2.5 / 2, 440 - textureStart.getSize().y * 2.5 / 2, textureStart.getSize().x * 2.5, textureStart.getSize().y * 2.5);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear();

        // Si la souris est sur le bouton Start
        if (librairies.isMouseOnSurface(clickableSurfaceStart, window)) {
            window.draw(spriteStartHover);
            // Si le clic gauche est enfoncé sur le bouton Start
            if (librairies.isLeftClickOnSurface(clickableSurfaceStart, window)) {
                window.draw(spriteStartClicked);
            }
        }
        // Sinon
        else {
            window.draw(spriteStart);
        }

        // Afficher la fenêtre
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 60));
    }

    // Fermer la fenêtre
    window.close();
}
