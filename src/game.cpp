#include <SFML/Graphics.hpp>
#include "game.h"
#include "librairies.h"
#include <iostream>

Game::Game() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Project NoName");

    // Créer un objet de la classe Librairies
    Librairies librairies;

    // Création de l'image de fond
    sf::Texture textureBackground;
    sf::Sprite spriteBackground = librairies.createSprite("../assets/background/Menu_Background.png", 1920 / 2, 1080 / 2, 1, textureBackground);

    // Création du l'image de fond du menu
    sf::Texture textureMenu;
    sf::Sprite spriteMenu = librairies.createSprite("../assets/UI/Menu.png", 960, 570, 3, textureMenu);

    // Création du Bouton Start
    sf::Texture textureStart;
    sf::Sprite spriteStart = librairies.createSprite("../assets/button/Start.png", 960, 400, 2.5, textureStart);
    sf::Texture textureStartHover;
    sf::Sprite spriteStartHover = librairies.createSprite("../assets/button/Start_Hover.png", 960, 400, 2.5, textureStartHover);
    sf::Texture textureStartClicked;
    sf::Sprite spriteStartClicked = librairies.createSprite("../assets/button/Start_Pushed.png", 960, 400, 2.5, textureStartClicked);
    sf::RectangleShape clickableSurfaceStart = librairies.createClickableSurface(960 - textureStart.getSize().x * 2.5 / 2, 400 - textureStart.getSize().y * 2.5 / 2, textureStart.getSize().x * 2.5, textureStart.getSize().y * 2.5);

    // Création du Bouton Continuer
    sf::Texture textureContinue;
    sf::Sprite spriteContinue = librairies.createSprite("../assets/button/Continue.png", 960, 500, 2.5, textureContinue);
    sf::Texture textureContinueHover;
    sf::Sprite spriteContinueHover = librairies.createSprite("../assets/button/Continue_Hover.png", 960, 500, 2.5, textureContinueHover);
    sf::Texture textureContinueClicked;
    sf::Sprite spriteContinueClicked = librairies.createSprite("../assets/button/Continue_Pushed.png", 960, 500, 2.5, textureContinueClicked);
    sf::RectangleShape clickableSurfaceContinue = librairies.createClickableSurface(960 - textureContinue.getSize().x * 2.5 / 2, 500 - textureContinue.getSize().y * 2.5 / 2, textureContinue.getSize().x * 2.5, textureContinue.getSize().y * 2.5);

    // Création du Bouton Options
    sf::Texture textureOptions;
    sf::Sprite spriteOptions = librairies.createSprite("../assets/button/Options.png", 960, 600, 2.5, textureOptions);
    sf::Texture textureOptionsHover;
    sf::Sprite spriteOptionsHover = librairies.createSprite("../assets/button/Options_Hover.png", 960, 600, 2.5, textureOptionsHover);
    sf::Texture textureOptionsClicked;
    sf::Sprite spriteOptionsClicked = librairies.createSprite("../assets/button/Options_Pushed.png", 960, 600, 2.5, textureOptionsClicked);
    sf::RectangleShape clickableSurfaceOptions = librairies.createClickableSurface(960 - textureOptions.getSize().x * 2.5 / 2, 600 - textureOptions.getSize().y * 2.5 / 2, textureOptions.getSize().x * 2.5, textureOptions.getSize().y * 2.5);

    // Création du Bouton Quitter
    sf::Texture textureQuit;
    sf::Sprite spriteQuit = librairies.createSprite("../assets/button/Quit.png", 960, 700, 2.5, textureQuit);
    sf::Texture textureQuitHover;
    sf::Sprite spriteQuitHover = librairies.createSprite("../assets/button/Quit_Hover.png", 960, 700, 2.5, textureQuitHover);
    sf::Texture textureQuitClicked;
    sf::Sprite spriteQuitClicked = librairies.createSprite("../assets/button/Quit_Pushed.png", 960, 700, 2.5, textureQuitClicked);
    sf::RectangleShape clickableSurfaceQuit = librairies.createClickableSurface(960 - textureQuit.getSize().x * 2.5 / 2, 700 - textureQuit.getSize().y * 2.5 / 2, textureQuit.getSize().x * 2.5, textureQuit.getSize().y * 2.5);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre
        window.clear();

        // Afficher l'image de fond
        window.draw(spriteBackground);

        // Afficher l'image de fond du menu
        window.draw(spriteMenu);

        // Si la souris est sur le bouton Start
        if (librairies.isMouseOnSurface(clickableSurfaceStart, window)) {
            // Si le clic gauche est enfoncé sur le bouton Start
            if (librairies.isLeftClickOnSurface(clickableSurfaceStart, window)) {
                window.draw(spriteStartClicked);
            }
            else {
                window.draw(spriteStartHover);
            }
        }
        // Sinon
        else {
            window.draw(spriteStart);
        }

        // Si la souris est sur le bouton Continuer
        if (librairies.isMouseOnSurface(clickableSurfaceContinue, window)) {
            // Si le clic gauche est enfoncé sur le bouton Continuer
            if (librairies.isLeftClickOnSurface(clickableSurfaceContinue, window)) {
                window.draw(spriteContinueClicked);
            }
            else {
                window.draw(spriteContinueHover);
            }
        }
        else {
            window.draw(spriteContinue);
        }

        // Si la souris est sur le bouton Options
        if (librairies.isMouseOnSurface(clickableSurfaceOptions, window)) {
            // Si le clic gauche est enfoncé sur le bouton Options
            if (librairies.isLeftClickOnSurface(clickableSurfaceOptions, window)) {
                window.draw(spriteOptionsClicked);
            }
            else {
                window.draw(spriteOptionsHover);
            }
        }
        else {
            window.draw(spriteOptions);
        }

        // Si la souris est sur le bouton Quitter
        if (librairies.isMouseOnSurface(clickableSurfaceQuit, window)) {
            // Si le clic gauche est enfoncé sur le bouton Quitter
            if (librairies.isLeftClickOnSurface(clickableSurfaceQuit, window)) {
                window.draw(spriteQuitClicked);
            }
            else {
                window.draw(spriteQuitHover);
            }
        }
        else {
            window.draw(spriteQuit);
        }

        // Afficher la fenêtre
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 60));
    }

    // Fermer la fenêtre
    window.close();
}
