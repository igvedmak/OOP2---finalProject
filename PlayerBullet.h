#pragma once
#include "Bullets.h"
class PlayerBullet : public Bullets
{
public:
	explicit PlayerBullet(const sf::Vector2f& position, const sf::Texture &t);
	PlayerBullet(const PlayerBullet&) = delete;//copy c-tor (lvalue)
	PlayerBullet& operator=(const PlayerBullet&) = delete; //assignment operator (lvalue)
	PlayerBullet(PlayerBullet&&) = default;//move copy c-tor (rvalue)
	PlayerBullet& operator=(PlayerBullet&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

