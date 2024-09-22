#ifndef LIBRAIRIES_H
#define LIBRAIRIES_H

#include <SFML/Graphics.hpp>
#include <string>

class Librairies {
public:
    sf::Sprite createSprite(const std::string path, int x, int y, float scale, sf::Texture &texture);
};

#endif // LIBRAIRIES_H
