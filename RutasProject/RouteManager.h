#pragma once
#include "define.h"
#include "Point.h"
#include "Route.h"
#include "Map.h"

class RouteManager {
public:
    std::list<Route> routes;
    Route* selectedRoute;
    bool routesVisible;

    RouteManager();
    void addRoute(const Route& route);
    void draw(sf::RenderWindow& window);
    Route* selectRoute(const sf::Vector2f& pos);
    void deselectRoute();
    void deleteSelectedRoute(std::vector<sf::Text>& routeNamesText);
    void deletePointFromSelectedRoute(const sf::Vector2f& pos, float radius = 10.0f);
    void loadRoutes();
    void saveRoutes();
    void addRouteNameToList(const std::string& routeName, std::vector<sf::Text>& routeNamesText, sf::Font& font);
};
