#pragma once
#include "Treasure.h"
class Token : public Treasure
{
public:
	Token(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	bool isCollide(Object & obj);
	virtual ~Token() {}
};

