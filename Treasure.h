#pragma once
#include "Pickup.h"
class Treasure : public Pickup
{
public:
	Treasure(sf::Vector2f place) : Pickup(place) {}
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~Treasure() {}
};

