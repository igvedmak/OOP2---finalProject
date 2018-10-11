#pragma once
#include "Pickup.h"
class Potion : public Pickup
{
public:
	explicit Potion(const sf::Vector2f& position, const sf::Texture &t);
	Potion(const Potion&) = delete;//copy c-tor (lvalue)
	Potion& operator=(const Potion&) = delete; //assignment operator (lvalue)
	Potion(Potion&&) = default;//move copy c-tor (rvalue)
	Potion& operator=(Potion&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
};

