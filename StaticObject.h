#pragma once
#include "Object.h"
class StaticObject : public Object
{
public:
	StaticObject(sf::Vector2f place) : Object(place) {}
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual bool isCollide(Object & obj) = 0;
	virtual ~StaticObject() {}
};

