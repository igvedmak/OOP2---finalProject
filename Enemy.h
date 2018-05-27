#pragma once
#include "DynamicObject.h"
class Enemy : public DynamicObject
{
public:
	Enemy(sf::Vector2f place) : DynamicObject(place) {}
	virtual bool getCanShoot() const = 0;
	virtual bool getIfcanErase() const = 0;
	virtual void setCanShoot(const bool canShoot) = 0;
	virtual void setCanErase(const bool canErase) = 0;
	virtual void setCounterBullet() = 0;
	virtual ~Enemy() {}

protected:
	bool m_canShoot = false;
};

