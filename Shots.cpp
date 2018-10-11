#include "Shots.h"

Shots::Shots(const sf::Vector2f& position, const sf::Texture &t)
	: DynamicObject(position, t, sf::Vector2f(0.f, 0.f))
{
	//m_velocity.x = ENEMY_VELOCITY;
	//m_velocity.y = ENEMY_VELOCITY;
	//m_sprite.setTextureRect(sf::IntRect(0, 130, 68, 130));
	//m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}