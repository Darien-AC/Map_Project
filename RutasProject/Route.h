#pragma once
#include "define.h"
#include "Point.h"

class Route {
public:
    std::list<Point> points;
    std::string routeName;
    bool isSelected;

    Route(const std::string& name);
    void draw(sf::RenderWindow& window);
    void addPoint(const Point& point);
    void deletePoint(const sf::Vector2f& pos, float radius = 10.0f);
    bool containsPoint(const sf::Vector2f& pos, float radius = 10.0f);
    sf::Vector2f interpolateCatmullRom(const sf::Vector2f& p0, const sf::Vector2f& p1,
        const sf::Vector2f& p2, const sf::Vector2f& p3, float t);
};

