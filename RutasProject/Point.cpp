#include "Point.h"

Point::Point(const sf::Vector2f& pos, const std::string& n, sf::Color c)
    : position(pos), name(n), color(c) {}

void Point::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(10.0f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(position);
    circle.setFillColor(color);
    window.draw(circle);

    sf::Font font;
    if (font.loadFromFile("Chakra_Petch/ChakraPetch-Bold.ttf")) {
        sf::Text text(name, font, 15);
        text.setPosition(position + sf::Vector2f(10, 0));
        text.setFillColor(sf::Color::Black);
        window.draw(text);
    }
}