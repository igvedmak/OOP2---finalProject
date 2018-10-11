#include "Player.h"
#include "PlayerState.h"

// c-tor
Player::Player(const sf::Vector2f& position, const sf::Texture &t)
	: DynamicObject(position, t, sf::Vector2f(0.f, 0.f)), m_life(100)
{
	m_state = std::make_unique<StandingPlayerState>();
	m_velocity.x = PLAYER_VELOCITY;
	m_velocity.y = PLAYER_VELOCITY;
	m_sprite.setTextureRect(sf::IntRect(0, CLAW_HEIGHT, CLAW_WIDTH, CLAW_HEIGHT));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
	resetFrame();
}
//----------------------------------------------------------------------------------------------
// the function checks the range of the object, return true if in the range of the game window 
//else return false
bool Player::inRange(size_t width) const{
	return (m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2.f > 0);
}

void Player::update() {
	handleInupt(NONE);
	m_state->update(*this);
	isCollidingLadder = false;
}

bool Player::handleInupt(Input input) {
	if (auto p = m_state->handleInput(input)) {
		m_state = std::move(p);
		m_state->enter(*this);
		return true;
	}
	return false;
}

void Player::collideWithLadder(const std::shared_ptr<Ladder> ladder)
{
	lastLadderX = ladder->getSprite().getPosition().x;
	isCollidingLadder = true;
}


