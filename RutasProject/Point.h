#pragma once
#include "define.h"

#include <SFML/Graphics.hpp>
#include <string>

class Point {
public:
    sf::Vector2f position;
    std::string name;
    sf::Color color;

    Point(const sf::Vector2f& pos, const std::string& n, sf::Color c);
    void draw(sf::RenderWindow& window);
};