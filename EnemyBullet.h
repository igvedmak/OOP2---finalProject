#pragma once
#include "Bullets.h"
class EnemyBullet : public Bullets
{
public:
	explicit EnemyBullet(const sf::Vector2f& position, const sf::Texture &t);
	EnemyBullet(const EnemyBullet&) = delete;//copy c-tor (lvalue)
	EnemyBullet& operator=(const EnemyBullet&) = delete; //assignment operator (lvalue)
	EnemyBullet(EnemyBullet&&) = default;//move copy c-tor (rvalue)
	EnemyBullet& operator=(EnemyBullet&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

