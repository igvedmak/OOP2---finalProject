#pragma once
#include "Pickup.h"
class Treasure : public Pickup
{
public:
	explicit Treasure(const sf::Vector2f& position, const sf::Texture &t);
	Treasure(const Treasure&) = delete;//copy c-tor (lvalue)
	Treasure& operator=(const Treasure&) = delete; //assignment operator (lvalue)
	Treasure(Treasure&&) = default;//move copy c-tor (rvalue)
	Treasure& operator=(Treasure&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

