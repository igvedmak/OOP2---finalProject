#pragma once
#include "Enemy.h"
class SmartEnemy : public Enemy
{
public:
	explicit SmartEnemy(const sf::Vector2f& position, const sf::Texture &t);
	SmartEnemy(const SmartEnemy&) = delete;//copy c-tor (lvalue)
	SmartEnemy& operator=(const SmartEnemy&) = delete; //assignment operator (lvalue)
	SmartEnemy(SmartEnemy&&) = default;//move copy c-tor (rvalue)
	SmartEnemy& operator=(SmartEnemy&&) = delete;//move assigment operator (rvalue)
private:
	Enemies typeEnemy;
};

