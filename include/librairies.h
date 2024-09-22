#ifndef LIBRAIRIES_H
#define LIBRAIRIES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Librairies {
public:
    sf::Sprite addSprite(int x, int y, int sizeX, int sizeY, const std::string& texture);
};

#endif // !LIBRAIRIES_H
