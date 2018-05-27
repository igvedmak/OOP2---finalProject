#pragma once
#include "DynamicObject.h"
class Shots : public DynamicObject
{
public:
	Shots(sf::Vector2f place) : DynamicObject(place) {}
	virtual ~Shots() {}
};

