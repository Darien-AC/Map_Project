#pragma once
#include "define.h"

class Point
{
private:
    string name;
    Vector2f position;
    Color color;
    CircleShape mapPoint;
    float pointSize;

public:
    Point();
    Point(const string& name, const Vector2f& position, const Color& color, float pointSize);

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    Vector2f getPosition() const;
};
