#pragma once
#include "StaticObject.h"
class Obstacle : public StaticObject
{
public:
	Obstacle(sf::Vector2f place);
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual ~Obstacle() {}
};
