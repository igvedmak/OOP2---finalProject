#include "GameState.h"

// constractor
GameState::GameState(const sf::Vector2f& coords, const sf::Texture& texture)
	:m_texture(texture)
{
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(coords);
}