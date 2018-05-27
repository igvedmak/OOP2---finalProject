#pragma once
#include "Pickup.h"
class Potion : public Pickup
{
public:
	Potion(sf::Vector2f place) : Pickup(place) {}
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~Potion() {}
};

