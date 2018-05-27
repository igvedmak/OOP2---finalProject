#pragma once
#include "Shots.h"
class Bullets : public Shots
{
public:
	Bullets(sf::Vector2f place) : Shots(place){}
	virtual ~Bullets() {}
	virtual void setBulletPosition(sf::Vector2f position, Direction dir) = 0;
};

