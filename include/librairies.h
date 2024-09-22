#ifndef LIBRAIRIES_H
#define LIBRAIRIES_H

#include <SFML/Graphics.hpp>
#include <string>

class Librairies {
public:
    sf::Sprite createSprite(const std::string path, int x, int y, float scale, sf::Texture &texture);
    sf::Text createText(const std::string text, int x, int y, int size, sf::Font &font);
    sf::RectangleShape createClickableSurface(int x, int y, int width, int height);
    bool isMouseOnSurface(sf::RectangleShape clickableSurface, sf::RenderWindow &window); 
    bool isLeftClickOnSurface(sf::RectangleShape clickableSurface, sf::RenderWindow &window);
};

#endif // LIBRAIRIES_H
