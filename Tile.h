#pragma once
#include "StaticObject.h"
class Tile : public StaticObject
{
public:
	Tile(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	bool isCollide(Object & obj);
	void setBG(int level);
	virtual ~Tile() {}
};

