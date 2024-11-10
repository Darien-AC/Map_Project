#pragma once
#include "define.h"
#include "Route.h"
#include "RouteManager.h"

class FileManager 
{
public:
    static void loadRoutesFromFile(std::vector<sf::Text>& routeNamesText, sf::Font& font);
    static void saveRoutesToFile(const std::string& filename, const std::list<Route>& routes);
};

