#pragma once
#include "define.h"
#include "Map.h"
#include "Point.h"
#include "RouteManager.h"
#include "FileManager.h"

class Map {
public:
    sf::RenderWindow window;

    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    Color selectedColor;

    Texture buttonTextures[6];
    Sprite buttonSprites[6];

    CircleShape colorPalette[7];
    sf::Color colors[8] = {
     sf::Color::Red, sf::Color::Green, sf::Color::Blue,
     sf::Color(255, 182, 255), sf::Color::Cyan, sf::Color::White, sf::Color(190, 0, 190)
    };

    Font chooseColor;
    Font routesList;

    RectangleShape dividerLine;

    Text textPoints;
    Text routeListHeader;
    vector<Text> routeNamesText;

    bool creatingRoute;
    bool editingRoute;


    Map();
    void run();
    void handleEvents();
    void update();
    void setupColorPalette();
    void setupDividerLine();
    void setupFonts();
    void render();
};
