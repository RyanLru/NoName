#include "map.h"
#include "librairies.h"
#include <iostream>
#include <sstream>

MapInterface::MapInterface(const std::string& filename, const std::string& textureFilename, sf::RenderWindow& window) {
    if (!loadTileTexture(textureFilename) || !parseTMXFile(filename)) {
        return;
    }

    parseLayers(mapElement);
    std::cout << "Map loaded successfully with " << tiles.size() << " tiles." << std::endl;
    LoadMap(window);
}

bool MapInterface::loadTileTexture(const std::string& textureFilename) {
    if (!tileTexture.loadFromFile(textureFilename)) {
        std::cerr << "Failed to load tile texture!" << std::endl;
        return false;
    }
    return true;
}

bool MapInterface::parseTMXFile(const std::string& filename) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load TMX file!" << std::endl;
        return false;
    }

    mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        std::cerr << "No map element found!" << std::endl;
        return false;
    }

    mapElement->QueryIntAttribute("width", &width);
    mapElement->QueryIntAttribute("height", &height);
    mapElement->QueryIntAttribute("tilewidth", &tileWidth);
    mapElement->QueryIntAttribute("tileheight", &tileHeight);

    return true;
}

void MapInterface::parseLayers(tinyxml2::XMLElement* mapElement) {
    tinyxml2::XMLElement* layerElement = mapElement->FirstChildElement("layer");
    while (layerElement) {
        parseLayerData(layerElement->FirstChildElement("data"));
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void MapInterface::parseLayerData(tinyxml2::XMLElement* dataElement) {
    if (!dataElement) {
        std::cerr << "No data element found in layer!" << std::endl;
        return;
    }

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
                    addTile(gid, x, y);
                }
                x++;
            }
            y++;
        }
    }
}

void MapInterface::addTile(int gid, int x, int y) {
    Tile tile;
    tile.id = gid;
    tile.sprite.setTexture(tileTexture);
    tile.sprite.setTextureRect(sf::IntRect((gid - 1) % (tileTexture.getSize().x / tileWidth) * tileWidth,
                                           (gid - 1) / (tileTexture.getSize().x / tileWidth) * tileHeight,
                                           tileWidth, tileHeight));
    tile.sprite.setPosition(x * tileWidth, y * tileHeight);
    tiles.push_back(tile);
}

void MapInterface::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles) {
        window.draw(tile.sprite);
    }
}

int MapInterface::LoadMap(sf::RenderWindow& window) {
    Librairies librairies;

    sf::Texture textureBackground;
    sf::Sprite spriteBackground = librairies.createSprite("../assets/background/Menu_Background.png", 1920 / 2, 1080 / 2, 1, textureBackground);

    sf::Texture texturePlayer;
    if (!texturePlayer.loadFromFile("../assets/Perso/Perso_Basique.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1;
    }

    sf::Sprite spritePlayer = librairies.createSprite("../assets/Perso/Perso_Basique.png", 1920 / 2, 1080 / 2, 2, texturePlayer);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f mapSize(width * tileWidth, height * tileHeight);
    sf::Vector2f mapPosition((windowSize.x - mapSize.x) / 2.0f, (windowSize.y - mapSize.y) / 2.0f);

    for (auto& tile : tiles) {
        tile.sprite.setPosition(tile.sprite.getPosition() + mapPosition);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handlePlayerMovement(event, spritePlayer);
        }

        window.clear();
        window.draw(spriteBackground);
        draw(window);
        window.draw(spritePlayer);
        window.display();

        sf::sleep(sf::milliseconds(1000 / 144));
    }

    return 0;
}

void MapInterface::handlePlayerMovement(const sf::Event& event, sf::Sprite& spritePlayer) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z) {
            spritePlayer.move(0, -5);
        } else if (event.key.code == sf::Keyboard::S) {
            spritePlayer.move(0, 5);
        } else if (event.key.code == sf::Keyboard::Q) {
            spritePlayer.move(-5, 0);
        } else if (event.key.code == sf::Keyboard::D) {
            spritePlayer.move(5, 0);
        }
    }
}
