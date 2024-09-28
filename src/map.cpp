#include "map.h"
#include "librairies.h"

MapInterface::MapInterface(const std::string& filename, const std::string& textureFilename, sf::RenderWindow& window) {
    // Charger la texture des tuiles
    if (!tileTexture.loadFromFile(textureFilename)) {
        std::cerr << "Failed to load tile texture!" << std::endl;
        return;
    }

    // Parser le fichier TMX
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load TMX file!" << std::endl;
        return;
    }

    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "No map element found!" << std::endl;
        return;
    }

    // Obtenir les dimensions de la map
    mapElement->QueryIntAttribute("width", &width);
    mapElement->QueryIntAttribute("height", &height);
    mapElement->QueryIntAttribute("tilewidth", &tileWidth);
    mapElement->QueryIntAttribute("tileheight", &tileHeight);

    // Parser les layers et les tuiles
    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
    if (!layerElement) {
        std::cerr << "No layer element found!" << std::endl;
        return;
    }

    while (layerElement) {
        tinyxml2::XMLElement* dataElement = layerElement->FirstChildElement("data");
        if (dataElement) {
            const char* data = dataElement->GetText();
            if (data) {
                std::istringstream dataStream(data);
                std::string line;
                int y = 0;
                while (std::getline(dataStream, line)) {
                    std::istringstream lineStream(line);
                    std::string cell;
                    int x = 0;
                    while (std::getline(lineStream, cell, ',')) {
                        int gid = std::stoi(cell);
                        if (gid > 0) {
                            Tile tile;
                            tile.id = gid;
                            tile.sprite.setTexture(tileTexture);
                            tile.sprite.setTextureRect(sf::IntRect((gid - 1) % (tileTexture.getSize().x / tileWidth) * tileWidth,
                                                                   (gid - 1) / (tileTexture.getSize().x / tileWidth) * tileHeight,
                                                                   tileWidth, tileHeight));
                            tile.sprite.setPosition(x * tileWidth, y * tileHeight);

                            tiles.push_back(tile);
                        }
                        x++;
                    }
                    y++;
                }
            }
        } else {
            std::cerr << "No data element found in layer!" << std::endl;
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }

    std::cout << "Map loaded successfully with " << tiles.size() << " tiles." << std::endl;
    // Charger la map
    LoadMap(window);
}

void MapInterface::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        window.draw(tile.sprite);
    }
}

int MapInterface::LoadMap(sf::RenderWindow& window) {
    // Librairies
    Librairies librairies;

    // Affiche un background
    sf::Texture textureBackground;
    sf::Sprite spriteBackground = librairies.createSprite("../assets/background/Menu_Background.png", 1920 / 2, 1080 / 2, 1, textureBackground);

    // Chargement du Player
    // 3 Frames pour l'animation Perso_Basique_Walk_1 -> Perso_Basique -> Perso_Basique_Walk_2
    // Même principe pour les autres directions Perso_Basique_Left -> Perso_Basique_Left -> Perso_Basique_Left_Walk_2

    // Chargement de la texture du Player
    sf::Texture texturePlayer;
    if (!texturePlayer.loadFromFile("../assets/Perso/Perso_Basique.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1;
    }

    // Création du sprite du Player
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Si une touche est pressée
            if (event.type == sf::Event::KeyPressed) {
                // Si la touche flèche du haut est pressée
                if (event.key.code == sf::Keyboard::Up) {
                    spritePlayer.move(0, -5);
                }
                // Si la touche flèche du bas est pressée
                if (event.key.code == sf::Keyboard::Down) {
                    // Déplacement du Player vers le bas
                    spritePlayer.move(0, 5);
                }
                // Si la touche flèche de gauche est pressée
                if (event.key.code == sf::Keyboard::Left) {
                    // Déplacement du Player vers la gauche
                    spritePlayer.move(-5, 0);
                }
                // Si la touche flèche de droite est pressée
                if (event.key.code == sf::Keyboard::Right) {
                    // Déplacement du Player vers la droite
                    spritePlayer.move(5, 0);
                }
            }
        }

        window.clear();
        window.draw(spriteBackground);
        draw(window);

        // Affichage du Player
        window.draw(spritePlayer);

        window.display();

        // Limiter le nombre d'images par seconde à 144
        sf::sleep(sf::milliseconds(1000 / 144));
    }

    return 0;
}
