#include "Token.h"

bool Token::m_registerit = SpawnManager<char, Pickup>::registerit(REDCROWN_C, [](const sf::Vector2f& pos) -> std::unique_ptr<Pickup> { return std::make_unique<Token>(pos, Source::instance().getRedCrownTexture()); });

Token::Token(const sf::Vector2f& position, const sf::Texture &t)
	: Treasure(position, t){}
