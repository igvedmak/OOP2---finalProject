#pragma once
#include "Obstacle.h"
class Spkies : public Obstacle
{
public:
	Spkies(sf::Vector2f place);
	bool isCollide(Object & obj);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual ~Spkies() {}
};

