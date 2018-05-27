#pragma once
#include "Bullets.h"
class EnemyBullet : public Bullets
{
public:
	EnemyBullet(sf::Vector2f place) : Bullets(place) {}
	void move(const Direction dir, float deltaTime) {}
	void setPosition(sf::Vector2f position) {}
	void setBulletPosition(sf::Vector2f position, Direction dir);
	void setNextDir(Direction dir) { m_nextDir = dir; }
	Direction getNextDir() const { return m_nextDir; }
	virtual ~EnemyBullet() {}

private:
	Direction m_dir;
};

