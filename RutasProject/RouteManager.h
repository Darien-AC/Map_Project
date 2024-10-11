#pragma once
#include "define.h"
#include "Point.h"
#include "Route.h"
#include "Map.h"

class RouteManager
{
private:
	Map tourMap;
	Route* currentRoute;
	Point* selectedPoint;

public:
	RouteManager();

};

