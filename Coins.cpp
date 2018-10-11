#include "Coins.h"

bool Coins::m_registerit = SpawnManager<char, Pickup>::registerit(COIN_C, [](const sf::Vector2f& pos) -> std::unique_ptr<Pickup> { return std::make_unique<Coins>(pos, Source::instance().getCoinTexture()); });

Coins::Coins(const sf::Vector2f& position, const sf::Texture &t)
	: Treasure(position, t){
	m_sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}
