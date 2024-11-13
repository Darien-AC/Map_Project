#include "Map.h"
#include <iostream>

RouteManager routeManager;
FileManager fileManager;
Route currentRoute("Unnamed Route");

Map::Map() : window(sf::VideoMode(1600, 900), "Touristic Map") {
    window.setFramerateLimit(60);
    if (!mapTexture.loadFromFile("images/mapa225.jpg")) {
        std::cerr << "Error loading map image.\n";
        exit(-1);
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setPosition(800, 0);
    mapSprite.setScale(800.0f / mapTexture.getSize().x, 900.0f / mapTexture.getSize().y);
    routeManager.loadRoutes(); // Cargar las rutas al iniciar el programa

    const std::string buttonImagePaths[6] = {
        "images/agregar.jpg", "images/editar.jpg",//editar
        "images/mostrar.jpg", "images/limpiar.jpg",
        "images/salir.jpg", "images/eliminar.jpg"
    };
    for (int i = 0; i < 6; ++i) {
        if (!buttonTextures[i].loadFromFile(buttonImagePaths[i])) {
            std::cerr << "Error loading button image: " << buttonImagePaths[i] << "\n";
        }
    }

    for (int i = 0; i < 6; ++i) {
        buttonSprites[i].setTexture(buttonTextures[i]);
        buttonSprites[i].setPosition(350, 100 + i * 130);

        float scaleX = 300.0f / buttonTextures[i].getSize().x;
        float scaleY = 100.0f / buttonTextures[i].getSize().y;
        buttonSprites[i].setScale(scaleX, scaleY);
    }
    buttonSprites[5].setTexture(buttonTextures[5]); // deletePointButton
    buttonSprites[5].setPosition(350, 300);
    buttonSprites[5].setColor(sf::Color(128, 128, 128, 128)); // Initially invisible

    routeManager.loadRoutes();

    creatingRoute = false;
    editingRoute = false;

    Route currentRoute("Unnamed Route");

    selectedColor = Color::Blue;

    fileManager.loadRoutesFromFile(routeNamesText, chooseColor);
    setupDividerLine();
    setupFonts();
    setupColorPalette();
}

void Map::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            routeManager.saveRoutes(); // Guardar rutas antes de cerrar
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (!creatingRoute && !editingRoute) {
                for (int i = 0; i < 5; ++i) {
                    if (buttonSprites[i].getGlobalBounds().contains(mousePos)) {
                        if (i == 0) { // addRouteButton
                            creatingRoute = true;
                            routeManager.routesVisible = true; // Hacer visibles las rutas
                            for (int j = 1; j < 5; ++j) {
                                buttonSprites[j].setColor(sf::Color(128, 128, 128, 128));
                            }
                            buttonSprites[0].setPosition(250, 500);
                            buttonTextures[0].loadFromFile("images/guardar.jpg");
                            buttonSprites[0].setTexture(buttonTextures[0]);

                            break;
                        }
                        else if (i == 1) { // editRouteButton
                            editingRoute = true;
                            routeManager.routesVisible = true; // Hacer visibles las rutas
                            for (int j = 0; j < 5; ++j) {
                                buttonSprites[j].setColor(sf::Color(128, 128, 128, 128));
                            }
                            buttonSprites[3].setColor(sf::Color::White); // Show clearRoutesButton
                            buttonSprites[5].setColor(sf::Color::White); // Show deletePointButton

                            buttonTextures[3].loadFromFile("images/borrar.jpg");
                            buttonSprites[3].setTexture(buttonTextures[3]);
                            buttonSprites[3].setPosition(350, 500);
                        }
                        else if (i == 2) { // showRouteButton (botón de mostrar ruta)
                            routeManager.routesVisible = true; // Hacer visibles las rutas
                        }
                        else if (i == 3) {
                            routeManager.routesVisible = false; // Hacer visibles las rutas
                        }
                        else if (i == 4) {
                            routeManager.saveRoutes();
                            window.close();
                        }
                    }
                }
            }
            else if (creatingRoute) {
                if (mousePos.x < 900 && mousePos.y < 120) {
                    // Color selection
                    for (int i = 0; i < 7; ++i) {
                        if (colorPalette[i].getGlobalBounds().contains(mousePos)) {
                            selectedColor = colors[i];
                            break;
                        }
                    }
                }
                else if (mousePos.x > 800) {
                    std::string placeName;
                    std::cout << "Digite el nombre del lugar: ";
                    std::cin >> placeName;
                    Point point(mousePos, placeName, selectedColor); // Use selectedColor
                    currentRoute.points.push_back(point);
                }
                else if (buttonSprites[0].getGlobalBounds().contains(mousePos)) {
                    std::string routeName;
                    std::cout << "Ingrese el nombre de la ruta: ";
                    std::cin >> routeName;
                    currentRoute.routeName = routeName;
                    routeManager.addRoute(currentRoute);
                    currentRoute.points.clear();
                    creatingRoute = false;
                    routeManager.routesVisible = false; // Ocultar las rutas después de guardar

                    for (int j = 0; j < 5; ++j) {
                        buttonSprites[j].setColor(sf::Color::White);
                        buttonTextures[0].loadFromFile("images/agregar.jpg");
                        buttonSprites[0].setTexture(buttonTextures[0]);
                        buttonSprites[0].setPosition(350, 100);
                    }

                    sf::Text routeNameText(routeName, routesList, 15);
                    routeNameText.setFillColor(sf::Color::White);
                    routeNameText.setPosition(30, 50 + routeNamesText.size() * 25); // Ajusta la posición según el índice
                    routeNamesText.push_back(routeNameText);

                    currentRoute.points.clear();
                }
            }
            else if (editingRoute) {
                if (buttonSprites[3].getGlobalBounds().contains(mousePos) && routeManager.selectedRoute) {
                    routeManager.deleteSelectedRoute(routeNamesText);
                    for (size_t i = 0; i < routeNamesText.size(); ++i) {
                        routeNamesText[i].setPosition(20, 50 + i * 25); // Reajusta la posición en función del índice
                    }
                    editingRoute = false; // Exit editing mode after deleting
                    routeManager.routesVisible = false; // Ocultar las rutas después de guardar
                    for (int j = 0; j < 5; ++j) {
                        buttonSprites[j].setColor(sf::Color::White);
                        buttonTextures[3].loadFromFile("images/limpiar.jpg");
                        buttonSprites[3].setTexture(buttonTextures[3]);
                        buttonSprites[3].setPosition(350, 490);
                    }
                    buttonSprites[0].setPosition(350, 100);
                    buttonSprites[5].setColor(sf::Color(128, 128, 128, 128)); // Hide deletePointButton
                }
                else if (buttonSprites[5].getGlobalBounds().contains(mousePos) && routeManager.selectedRoute) {
                    routeManager.selectedRoute->deletePoint(mousePos); // Eliminar el punto seleccionado
                    std::cout << "Eliminado\n";
                }
                else {
                    routeManager.deselectRoute();
                    routeManager.selectRoute(mousePos);
                }
            }
        }
    }
}

void Map::update() {
    // Aquí se pueden actualizar las rutas y otros elementos si es necesario
}

void Map::setupColorPalette()
{
    for (int i = 0; i < 7; ++i) {
        colorPalette[i].setRadius(30);
        colorPalette[i].setFillColor(colors[i]);
        colorPalette[i].setPosition(80 + i * 90, 80);
    }
}

void Map::setupDividerLine() {
    dividerLine.setSize(sf::Vector2f(5, window.getSize().y)); // Línea vertical de 5 px de ancho y la altura de la ventana
    dividerLine.setPosition(210, 0); // Ajusta la posición para que quede entre "Lista de Rutas" y los botones
    dividerLine.setFillColor(sf::Color::White); // Color de la línea
}

void Map::setupFonts()
{
    if (!chooseColor.loadFromFile("Chakra_Petch/ChakraPetch-Bold.ttf")) {
        std::cout << "Error loading font.\n";
    }
    textPoints.setFont(chooseColor);
    textPoints.setString("ELIJA EL COLOR DEL PUNTO");
    textPoints.setCharacterSize(50);
    textPoints.setPosition(60, 10);
    textPoints.setFillColor(sf::Color::White);

    if (!routesList.loadFromFile("Chakra_Petch/ChakraPetch-Bold.ttf")) {
        std::cerr << "Error loading font.\n";
    }
    routeListHeader.setFont(routesList);
    routeListHeader.setString("Lista de Rutas");
    routeListHeader.setCharacterSize(20);
    routeListHeader.setPosition(30, 20);
    routeListHeader.setFillColor(sf::Color::White);
}

void Map::render() {
    window.clear(sf::Color::Black);
    window.draw(mapSprite);

    if (!creatingRoute && !editingRoute) {
        for (int i = 0; i < 5; ++i) {
            window.draw(buttonSprites[i]);
        }

        window.draw(routeListHeader);
        for (auto& routeText : routeNamesText) {
            window.draw(routeText);
        }
        window.draw(dividerLine);
    }
    else if (creatingRoute) {
        for (int i = 0; i < 7; ++i) {
            window.draw(colorPalette[i]);
        }
        window.draw(buttonSprites[0]);
        window.draw(textPoints);
    }
    else if (editingRoute) {
        window.draw(buttonSprites[3]); // Draw clearRoutesButton
        window.draw(buttonSprites[5]); // Draw deletePointButton
        window.draw(routeListHeader);
        for (auto& routeText : routeNamesText) {
            window.draw(routeText);
        }
        window.draw(dividerLine);
    }

    routeManager.draw(window);
    currentRoute.draw(window);

    window.display();
}

void Map::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}