#include "Map.h"

Map::Map() : currentColor(Color::White), addButton(Vector2f(300, 80)), closeButton(Vector2f(300, 80)),
addPointButton(Vector2f(300, 80)), deletePointButton(Vector2f(300, 80)),
saveRouteButton(Vector2f(300, 80)), showRouteButton(Vector2f(300, 80)),
clearMapButton(Vector2f(300, 80))
{
	// Cargar texturas para los botones
	if (!addButtonTexture.loadFromFile("imagens/agregar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Agregar'" << endl;
	}
	if (!closeButtonTexture.loadFromFile("imagens/eliminar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Cerrar'" << endl;
	}
	if (!addPointButtonTexture.loadFromFile("imagens/guardar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Agregar Punto'" << endl;
	}
	if (!deletePointButtonTexture.loadFromFile("imagens/mostrar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Eliminar Punto'" << endl;
	}
	if (!saveRouteButtonTexture.loadFromFile("imagens/limpiar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Guardar Ruta'" << endl;
	}
	if (!showRouteButtonTexture.loadFromFile("imagens/3.jpg")) {
		cout << "Error al cargar la imagen del botón 'Mostrar Ruta'" << endl;
	}
	if (!clearMapButtonTexture.loadFromFile("imagens/salir.jpg")) {
		cout << "Error al cargar la imagen del botón 'Limpiar Mapa'" << endl;
	}

	// Asignar las texturas a los botones
	addButton.setTexture(&addButtonTexture);
	closeButton.setTexture(&closeButtonTexture);
	addPointButton.setTexture(&addPointButtonTexture);
	deletePointButton.setTexture(&deletePointButtonTexture);
	saveRouteButton.setTexture(&saveRouteButtonTexture);
	showRouteButton.setTexture(&showRouteButtonTexture);
	clearMapButton.setTexture(&clearMapButtonTexture);

	// Posicionar los botones más arriba
	float buttonX = 150;
	float startY = 50;
	float spacingY = 120;

	addButton.setPosition(buttonX, startY);
	closeButton.setPosition(buttonX, startY + spacingY);
	addPointButton.setPosition(buttonX, startY + 2 * spacingY);
	deletePointButton.setPosition(buttonX, startY + 3 * spacingY);
	saveRouteButton.setPosition(buttonX, startY + 4 * spacingY);
	showRouteButton.setPosition(buttonX, startY + 5 * spacingY);
	clearMapButton.setPosition(buttonX, startY + 6 * spacingY);
}



Map::Map(const std::string& mapFile, const std::string& backgroundFile, const Color& color)
	: currentColor(color), addButton(Vector2f(300, 80)), closeButton(Vector2f(300, 80)),
	addPointButton(Vector2f(300, 80)), deletePointButton(Vector2f(300, 80)),
	saveRouteButton(Vector2f(300, 80)), showRouteButton(Vector2f(300, 80)),
	clearMapButton(Vector2f(300, 80))
{
	// Cargar la textura del mapa
	if (!mapTexture.loadFromFile(mapFile)) {
		cout << "Error al cargar la imagen del mapa" << endl;
	}
	mapSprite.setTexture(mapTexture);

	// Escalar la textura del mapa
	Vector2u textureSize = mapTexture.getSize();
	float desiredWidth = 880.0f;
	float desiredHeight = 900.0f;
	float scaleX = desiredWidth / textureSize.x;
	float scaleY = desiredHeight / textureSize.y;
	mapSprite.setScale(scaleX, scaleY);
	mapSprite.setPosition(700.0f, 0.0f);

	// Cargar la textura del fondo
	if (!backgroundTexture.loadFromFile(backgroundFile)) {
		cout << "Error al cargar la imagen de fondo" << endl;
	}
	backgroundSprite.setTexture(backgroundTexture);

	// Escalar el fondo al tamaño de la ventana
	Vector2u windowSize(1600, 900);
	scaleX = (float)windowSize.x / backgroundTexture.getSize().x;
	scaleY = (float)windowSize.y / backgroundTexture.getSize().y;
	backgroundSprite.setScale(scaleX, scaleY);

	// Cargar texturas para los botones
	if (!addButtonTexture.loadFromFile("imagens/agregar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Agregar'" << endl;
	}
	if (!closeButtonTexture.loadFromFile("imagens/eliminar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Cerrar'" << endl;
	}
	if (!addPointButtonTexture.loadFromFile("imagens/guardar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Agregar Punto'" << endl;
	}
	if (!deletePointButtonTexture.loadFromFile("imagens/mostrar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Eliminar Punto'" << endl;
	}
	if (!saveRouteButtonTexture.loadFromFile("imagens/limpiar.jpg")) {
		cout << "Error al cargar la imagen del botón 'Guardar Ruta'" << endl;
	}
	if (!showRouteButtonTexture.loadFromFile("imagens/3.jpg")) {
		cout << "Error al cargar la imagen del botón 'Mostrar Ruta'" << endl;
	}
	if (!clearMapButtonTexture.loadFromFile("imagens/salir.jpg")) {
		cout << "Error al cargar la imagen del botón 'Limpiar Mapa'" << endl;
	}

	// Asignar las texturas a los botones
	addButton.setTexture(&addButtonTexture);
	closeButton.setTexture(&closeButtonTexture);
	addPointButton.setTexture(&addPointButtonTexture);
	deletePointButton.setTexture(&deletePointButtonTexture);
	saveRouteButton.setTexture(&saveRouteButtonTexture);
	showRouteButton.setTexture(&showRouteButtonTexture);
	clearMapButton.setTexture(&clearMapButtonTexture);

	// Ajustar los botones más arriba
	float buttonX = 150;
	float startY = 50;
	float spacingY = 120;

	addButton.setPosition(buttonX, startY);
	closeButton.setPosition(buttonX, startY + spacingY);
	addPointButton.setPosition(buttonX, startY + 2 * spacingY);
	deletePointButton.setPosition(buttonX, startY + 3 * spacingY);
	saveRouteButton.setPosition(buttonX, startY + 4 * spacingY);
	showRouteButton.setPosition(buttonX, startY + 5 * spacingY);
	clearMapButton.setPosition(buttonX, startY + 6 * spacingY);
}

void Map::draw(RenderWindow& window)
{
	window.draw(backgroundSprite);  // Dibujar el fondo
	window.draw(mapSprite);         // Dibujar el mapa

	// Dibujar los botones
	window.draw(addButton);
	window.draw(closeButton);
	window.draw(addPointButton);
	window.draw(deletePointButton);
	window.draw(saveRouteButton);
	window.draw(showRouteButton);
	window.draw(clearMapButton);
}

void Map::handleEvents(RenderWindow& window, Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		Vector2i mousePos = Mouse::getPosition(window); // Obtener la posición del ratón
		if (addButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				// Obtener la posición del clic
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				// Establecer la posición del círculo
				mapPoint.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				cout << "Posision: " << "\nX: " << static_cast<float>(mousePos.x) << "\nY: " << static_cast<float>(mousePos.y);
			}
			cout << "Botón Agregar clicado!" << endl;
		}
		if (closeButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Cerrando...." << endl;
		}
		if (addPointButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Botón Agregar Punto clicado!" << endl;
		}
		if (deletePointButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Botón Eliminar Punto clicado!" << endl;
		}
		if (saveRouteButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Botón Guardar Ruta clicado!" << endl;
		}
		if (showRouteButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Botón Mostrar Ruta clicado!" << endl;
		}
		if (clearMapButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
		{
			cout << "Cerrando...." << endl;
			window.close();
		}
	}
}

bool Map::isClicked(const sf::Vector2i& mousePos)
{
	return addButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
