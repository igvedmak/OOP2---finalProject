#pragma once
#include "Treasure.h"
class Coins : public Treasure
{
public:
	Coins(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	bool isCollide(Object & obj);
	virtual ~Coins() {}
};

