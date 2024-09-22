#include <SFML/Graphics.hpp>

int main() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Créer un cercle
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Red);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

        // Passer en 60 FPS
        sf::sleep(sf::milliseconds(1000 / 144));
    }

    return 0;
}
