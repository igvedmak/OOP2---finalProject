#pragma once
#include "Treasure.h"
class Token : public Treasure
{
public:
	explicit Token(const sf::Vector2f& position, const sf::Texture &t);
	Token(const Token&) = delete;//copy c-tor (lvalue)
	Token& operator=(const Token&) = delete; //assignment operator (lvalue)
	Token(Token&&) = default;//move copy c-tor (rvalue)
	Token& operator=(Token&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

