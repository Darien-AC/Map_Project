#include "Route.h"

Route::Route(const std::string& name) : routeName(name), isSelected(false) {}

sf::Vector2f Route::interpolateCatmullRom(const sf::Vector2f& p0, const sf::Vector2f& p1,
    const sf::Vector2f& p2, const sf::Vector2f& p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;
    return 0.5f * ((2.0f * p1) +
        (-p0 + p2) * t +
        (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
        (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
}

void Route::draw(sf::RenderWindow& window) {
    for (auto& point : points) {
        point.draw(window);
    }

    if (points.size() > 1) {
        sf::VertexArray curve(sf::LinesStrip);
        auto p1 = points.begin();
        auto p2 = std::next(p1);

        while (p2 != points.end()) {
            auto p0 = (p1 == points.begin()) ? p1 : std::prev(p1);
            auto p3 = std::next(p2);

            sf::Color curveColor = isSelected ? sf::Color::Yellow : p1->color;

            for (float t = 0; t <= 1; t += 0.05f) {
                sf::Vector2f interpolatedPoint = interpolateCatmullRom(
                    p0->position, p1->position, p2->position, (p3 != points.end() ? p3->position : p2->position), t);
                curve.append(sf::Vertex(interpolatedPoint, curveColor));
            }

            curve.append(sf::Vertex(p2->position, curveColor));
            ++p1;
            ++p2;
        }

        window.draw(curve);
    }
}

void Route::addPoint(const Point& point) {
    points.push_back(point);
}

void Route::deletePoint(const sf::Vector2f& pos, float radius) {
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (std::hypot(it->position.x - pos.x, it->position.y - pos.y) < radius) {
            points.erase(it);
            break;
        }
    }
}

bool Route::containsPoint(const sf::Vector2f& pos, float radius) {
    for (auto& point : points) {
        if (std::hypot(point.position.x - pos.x, point.position.y - pos.y) < radius) {
            return true;
        }
    }
    return false;
}