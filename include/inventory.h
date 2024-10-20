#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Inventory {
public:
    Inventory();
    void draw(sf::RenderWindow& window);
    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    bool hasItem(const std::string& item) const;
};

#endif // INVENTORY_H