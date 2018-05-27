#pragma once
#include "Object.h"
class DynamicObject : public Object
{
public:
	DynamicObject(sf::Vector2f place);
	void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
	virtual void move(const Direction dir, float deltaTime) = 0;
	virtual void setPosition(sf::Vector2f position) = 0;
	virtual bool isCollide(Object & obj) = 0;
	virtual void setNextDir(Direction dir) = 0;
	virtual float getSpeed() const = 0;
	virtual Direction getNextDir() const = 0;
	virtual ~DynamicObject() {}

protected:
	Direction m_nextDir = Right;
};

