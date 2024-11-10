#include "RouteManager.h"

RouteManager::RouteManager() : selectedRoute(nullptr), routesVisible(false) {}

void RouteManager::addRoute(const Route& route) {
    routes.push_back(route);
}

void RouteManager::draw(sf::RenderWindow& window) {
    if (routesVisible) {
        for (auto& route : routes) {
            route.draw(window);
        }
    }
}

Route* RouteManager::selectRoute(const sf::Vector2f& pos) {
    for (auto& route : routes) {
        if (route.containsPoint(pos)) {
            if (selectedRoute) {
                selectedRoute->isSelected = false;
            }
            selectedRoute = &route;
            selectedRoute->isSelected = true;
            return selectedRoute;
        }
    }
    return nullptr;
}

void RouteManager::deselectRoute() {
    if (selectedRoute) {
        selectedRoute->isSelected = false;
        selectedRoute = nullptr;
    }
}

void RouteManager::deleteSelectedRoute(std::vector<sf::Text>& routeNamesText) {
    if (selectedRoute) {
        routes.remove_if([this](const Route& route) { return &route == selectedRoute; });
        selectedRoute = nullptr;
    }
}

void RouteManager::deletePointFromSelectedRoute(const sf::Vector2f& pos, float radius) {
    if (selectedRoute) {
        selectedRoute->deletePoint(pos, radius);
    }
}

void RouteManager::loadRoutes() {
    int routeNumber = 1;
    while (true) {
        std::string filename = "Ruta_" + std::to_string(routeNumber) + ".txt";
        std::ifstream inFile(filename);
        if (!inFile.is_open()) break;

        Route route("Route_" + std::to_string(routeNumber));
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string name;
            float x, y;
            int r, g, b;
            if (ss >> name >> x >> y >> r >> g >> b) {
                Point point(sf::Vector2f(x, y), name, sf::Color(r, g, b));
                route.addPoint(point);
            }
        }
        routes.push_back(route);
        inFile.close();
        routeNumber++;
    }
}

void RouteManager::saveRoutes() {
    int routeNumber = 1;
    for (const auto& route : routes) {
        std::string filename = "Ruta_" + std::to_string(routeNumber++) + ".txt";
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& point : route.points) {
                outFile << point.name << " " << point.position.x << " " << point.position.y << " "
                    << static_cast<int>(point.color.r) << " "
                    << static_cast<int>(point.color.g) << " "
                    << static_cast<int>(point.color.b) << "\n";
            }
            outFile.close();
        }
        else {
            std::cerr << "Error al guardar la ruta en el archivo: " << filename << "\n";
        }
    }
}

void RouteManager::addRouteNameToList(const std::string& routeName, std::vector<sf::Text>& routeNamesText, sf::Font& font)
{
    sf::Text routeText(routeName, font, 18);
    routeText.setFillColor(sf::Color::White);
    routeText.setPosition(30, 40 + routeNamesText.size() * 25);
    routeNamesText.push_back(routeText);
}
