#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, const sf::Texture &t)
	: DynamicObject(position, t, sf::Vector2f(0.f, 0.f)), lifePointer(2)
{
	m_state = std::make_unique<StandingEnemyState>();
	m_velocity.x = ENEMY_VELOCITY;
	m_velocity.y = ENEMY_VELOCITY;
	m_sprite.setTextureRect(sf::IntRect(0, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}
void Enemy::update() {
	m_state->update(*this);
	handleInupt(NONE);
}

bool Enemy::handleInupt(Input input) {
	if (auto p = m_state->handleInput(input)) {
		m_state = std::move(p);
		m_state->enter(*this);
		return true;
	}
	return false;
}
