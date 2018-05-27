#pragma once
#include "Bullets.h"
class PlayerBullet : public Bullets
{
public:
	PlayerBullet(sf::Vector2f place);
	void move(const Direction dir, float deltaTime);
	void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
	void setBulletPosition(sf::Vector2f position, Direction dir);
	void setNextDir(Direction dir) { m_nextDir = dir; }
	void setWizardDir(Direction wizardDir) { m_wizardDir = wizardDir; }
	bool isCollide(Object & obj);
	float getSpeed() const { return m_speed; }
	Direction getNextDir() const { return m_nextDir; }
	Direction getWizardDirection() const { return m_wizardDir; };
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	virtual ~PlayerBullet() {}

private:
	float m_speed = 14;
	Direction m_wizardDir = Right;
	Direction m_dir;
};

