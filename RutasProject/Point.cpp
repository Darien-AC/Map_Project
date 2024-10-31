#include "Point.h"

Point::Point() : name(""), position(0, 0), color(Color::White), pointSize(5.0f) {
	mapPoint.setRadius(pointSize);
	mapPoint.setFillColor(color);
	mapPoint.setPosition(position);
}

Point::Point(const string& name, const Vector2f& position, const Color& color, float pointSize) : name(name), position(position), color(color), pointSize(pointSize) {
	mapPoint.setRadius(pointSize);
	mapPoint.setFillColor(color);
	mapPoint.setPosition(position);
}

void Point::setPosition(float x, float y) {
	mapPoint.setPosition(x, y);
}



// Función para dibujar el círculo en la ventana
void Point::draw(RenderWindow& window) {
	window.draw(mapPoint);
}

Vector2f Point::getPosition() const
{
	return mapPoint.getPosition();
}
