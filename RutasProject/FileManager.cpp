#include "FileManager.h"

RouteManager route1;

void FileManager::loadRoutesFromFile(std::vector<sf::Text>& routeNamesText, sf::Font& font) 
{
    int routeNumber = 1;
    while (true) {
        std::string filename = "Ruta_" + std::to_string(routeNumber++) + ".txt";
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
        
        // Añadir la ruta al manager y actualizar la lista de nombres visual
        route1.routes.push_back(route);
        route1.addRouteNameToList(route.routeName, routeNamesText, font);
        inFile.close();
    }
}

void FileManager::saveRoutesToFile(const std::string& filename, const std::list<Route>& routes) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& route : routes) {
            for (const auto& point : route.points) {
                outFile << point.name << " " << point.position.x << " " << point.position.y << " "
                    << static_cast<int>(point.color.r) << " "
                    << static_cast<int>(point.color.g) << " "
                    << static_cast<int>(point.color.b) << "\n";
            }
        }
        outFile.close();
    }
    else {
        std::cerr << "Error al guardar las rutas en el archivo: " << filename << "\n";
    }
}