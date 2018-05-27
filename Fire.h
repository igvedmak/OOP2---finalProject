#pragma once
#include "Obstacle.h"
class Fire : public Obstacle
{
public:
	Fire(sf::Vector2f place);
	bool isCollide(Object & obj);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~Fire() {}
};

