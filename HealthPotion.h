#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
	HealthPotion(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	bool isCollide(Object & obj);
	virtual ~HealthPotion() {}
};

