#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

struct Tile {
    int id;
    sf::Sprite sprite;
};

class MapInterface {
public:
    MapInterface(const std::string& filename, const std::string& textureFilename, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    int LoadMap(sf::RenderWindow& window);

private:
    bool loadTileTexture(const std::string& textureFilename);
    bool parseTMXFile(const std::string& filename);
    void parseLayers(tinyxml2::XMLElement* mapElement);
    void parseLayerData(tinyxml2::XMLElement* dataElement);
    void addTile(int gid, int x, int y);
    void handlePlayerMovement(const sf::Event& event, sf::Sprite& spritePlayer);

    sf::Texture tileTexture;
    std::vector<Tile> tiles;
    int width, height, tileWidth, tileHeight;
    tinyxml2::XMLElement* mapElement;
};

#endif // MAP_H
