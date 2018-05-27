#pragma once
#include "StaticObject.h"
class Pickup : public StaticObject
{
public:
	Pickup(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~Pickup() {}
};

