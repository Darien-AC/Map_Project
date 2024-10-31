#include "define.h"
#include "Map.h"
#include "PointsAndRoutesList.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "SFML Map Test");

    Map map("imagens/mapa2.jpg", "imagens/fondo2.jpg", Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            map.handleEvents(window, event);
        }

        window.clear();
        map.draw(window); // Dibujar mapa y botones
        window.display();
    }

//    PointsAndRoutesList<string> pointList;
//
//    // Agregar elementos a la lista
//    pointList.append("Punto A");
//    pointList.append("Punto B");
//    pointList.append("Punto C");
//
//    // Mostrar los elementos de la lista
//    std::cout << "Puntos en la lista: ";
//    pointList.display();
//
//    // Eliminar un elemento específico
//    pointList.remove("Punto B");
//
//    // Mostrar la lista nuevamente
//    std::cout << "Puntos después de eliminar 'Punto B': ";
//    pointList.display();
//}