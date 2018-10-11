#pragma once
#include "Potion.h"
class HealthPotion : public Potion
{
public:
	explicit HealthPotion(const sf::Vector2f& position, const sf::Texture &t);
	HealthPotion(const HealthPotion&) = delete;//copy c-tor (lvalue)
	HealthPotion& operator=(const HealthPotion&) = delete; //assignment operator (lvalue)
	HealthPotion(HealthPotion&&) = default;//move copy c-tor (rvalue)
	HealthPotion& operator=(HealthPotion&&) = delete;//move assigment operator (rvalue)
private:
	static bool m_registerit;
};

