#pragma once
#include "Obstacle.h"
class BreakableTile : public Obstacle
{
public:
	BreakableTile(sf::Vector2f place);
	bool isCollide(Object & obj);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~BreakableTile() {}
};

