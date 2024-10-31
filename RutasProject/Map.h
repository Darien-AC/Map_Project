#pragma once
#include "define.h"
#include "Point.h"

class Map
{
private:
    Texture mapTexture;
    Sprite mapSprite;
    Texture backgroundTexture;
    Sprite backgroundSprite;

    RectangleShape addButton;
    RectangleShape closeButton;
    RectangleShape addPointButton;
    RectangleShape deletePointButton;
    RectangleShape saveRouteButton;
    RectangleShape showRouteButton;
    RectangleShape clearMapButton;

    // Texturas para los botones
    Texture addButtonTexture;
    Texture closeButtonTexture;
    Texture addPointButtonTexture;
    Texture deletePointButtonTexture;
    Texture saveRouteButtonTexture;
    Texture showRouteButtonTexture;
    Texture clearMapButtonTexture;

    Color currentColor;

    Point point;
    CircleShape mapPoint;

public:
    Map();
    Map(const std::string& mapFile, const std::string& backgroundFile, const Color& color);

    void draw(RenderWindow& window);
    void handleEvents(RenderWindow& window, Event& event);
    bool isClicked(const sf::Vector2i& mousePos);
};
