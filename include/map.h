#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <vector>
#include <sstream>

struct Tile {
    sf::Sprite sprite;
    int id;
};

class MapInterface {
public:
    MapInterface(const std::string& filename, const std::string& textureFilename, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    int LoadMap(sf::RenderWindow& window);
    bool isCollide(sf::FloatRect player);
    bool isNextMovePossible(sf::FloatRect player, sf::Vector2f move);

private:
    sf::Texture tileTexture;
    std::vector<Tile> tiles;
    int width, height, tileWidth, tileHeight;
    std::vector<sf::FloatRect> collides;
    sf::Vector2f playerPosition;
    float playerSpeed = 200.0f; // Vitesse du joueur en pixels par seconde
};

#endif // MAP_H
