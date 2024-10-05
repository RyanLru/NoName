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
                        try {
                            int gid = std::stoi(cell);
                            if (gid > 0) {
                                Tile tile;
                                tile.id = gid;
                                tile.sprite.setTexture(tileTexture);
                                tile.sprite.setTextureRect(sf::IntRect((gid - 1) % (tileTexture.getSize().x / tileWidth) * tileWidth,
                                                                       (gid - 1) / (tileTexture.getSize().x / tileWidth) * tileHeight,
                                                                       tileWidth, tileHeight));
                                tile.sprite.setPosition(x * tileWidth + 15, y * tileHeight-5);

                                tiles.push_back(tile);
                            }
                        } catch (const std::out_of_range& e) {
                            std::cerr << "Out of range error: " << e.what() << " for cell: " << cell << std::endl;
                        } catch (const std::invalid_argument& e) {
                            std::cerr << "Invalid argument error: " << e.what() << " for cell: " << cell << std::endl;
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

    // Chargement du group d'objet nommé "Collides"
    // On stocke les objets dans un vecteur de sf::FloatRect
    tinyxml2::XMLElement* objectGroupElement = mapElement->FirstChildElement("objectgroup");
    if (!objectGroupElement) {
        std::cerr << "No object group element found!" << std::endl;
        return;
    }

    while (objectGroupElement) {
        const char* name = objectGroupElement->Attribute("name");
        if (name && std::string(name) == "Collides") {
            tinyxml2::XMLElement* objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement) {
                float x, y, width, height;
                objectElement->QueryFloatAttribute("x", &x);
                objectElement->QueryFloatAttribute("y", &y);
                objectElement->QueryFloatAttribute("width", &width);
                objectElement->QueryFloatAttribute("height", &height);
                collides.push_back(sf::FloatRect(x, y, width, height));
                objectElement = objectElement->NextSiblingElement("object");
            }
        }
        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }

    std::cout << "Map loaded successfully with " << tiles.size() << " tiles." << std::endl;

    // Charger la map
    LoadMap(window);
}

void MapInterface::draw(sf::RenderWindow& window) {
    for (auto& tile : tiles) {
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
    sf::Sprite spritePlayer = librairies.createSprite("../assets/Perso/Perso_Basique.png", 1920 / 2, 1080 / 2, 2, texturePlayer);

    // Calculer la position de départ pour centrer la carte
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f mapSize(width * tileWidth, height * tileHeight);
    sf::Vector2f mapPosition((windowSize.x - mapSize.x) / 2.0f, (windowSize.y - mapSize.y) / 2.0f);

    // Appliquer la position de départ à chaque tuile
    for (auto& tile : tiles) {
        tile.sprite.setPosition(tile.sprite.getPosition() + mapPosition);
    }

    // Position initiale du joueur
    playerPosition = sf::Vector2f(1920 / 2, 1080 / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Gestion des mouvements du joueur
        sf::Vector2f move(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            move.y -= playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move.y += playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            move.x -= playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move.x += playerSpeed;
        }

        // Normaliser le vecteur de mouvement pour éviter les mouvements diagonaux plus rapides
        if (move.x != 0.0f && move.y != 0.0f) {
            move *= 0.7071f; // sqrt(2) / 2
        }

        // Calculer la nouvelle position du joueur
        sf::Vector2f newPosition = playerPosition + move * (1.0f / 144.0f); // 144 FPS

        // Vérifier les collisions
        sf::FloatRect playerBounds = spritePlayer.getGlobalBounds();
        playerBounds.left = newPosition.x;
        playerBounds.top = newPosition.y;

        if (!isNextMovePossible(playerBounds, move * (1.0f / 144.0f))) {
            playerPosition = newPosition;
        }

        // Mettre à jour la position du sprite du joueur
        spritePlayer.setPosition(playerPosition);

        window.clear();
        window.draw(spriteBackground);
        draw(window);
        window.draw(spritePlayer);

        // Dessiner les rectangles de collision
        for (const auto& collide : collides) {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(collide.width, collide.height));
            rect.setPosition(collide.left, collide.top);
            rect.setFillColor(sf::Color(255, 0, 0, 128));
            window.draw(rect);
        }
        

        window.display();

        // Limiter le nombre d'images par seconde à 144
        sf::sleep(sf::milliseconds(1000 / 144));
    }

    return 0;
}

bool MapInterface::isCollide(sf::FloatRect player) {
    for (const auto& collide : collides) {
        if (player.intersects(collide)) {
            return true;
        }
    }
    return false;
}

bool MapInterface::isNextMovePossible(sf::FloatRect player, sf::Vector2f move) {
    player.left += move.x;
    player.top += move.y;
    return isCollide(player);
}
