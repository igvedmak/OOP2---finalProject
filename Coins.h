#pragma once
#include "Treasure.h"
class Coins : public Treasure
{
public:
	explicit Coins(const sf::Vector2f& position, const sf::Texture &t);
	Coins(const Coins&) = delete;//copy c-tor (lvalue)
	Coins& operator=(const Coins&) = delete; //assignment operator (lvalue)
	Coins(Coins&&) = default;//move copy c-tor (rvalue)
	Coins& operator=(Coins&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

