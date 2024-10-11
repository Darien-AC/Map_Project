#pragma once
#include "define.h"
#include "Point.h"


class Map
{
private:
	Texture mapTexture;
	Sprite mapSprite;
	list<Point> routes;
	Color currentColor;

public:
	Map();

};

