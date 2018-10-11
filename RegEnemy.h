#pragma once
#include "Enemy.h"
class RegEnemy : public Enemy
{
public:
	explicit RegEnemy(const sf::Vector2f& position, const sf::Texture &t);
	RegEnemy(const RegEnemy&) = delete;//copy c-tor (lvalue)
	RegEnemy& operator=(const RegEnemy&) = delete; //assignment operator (lvalue)
	RegEnemy(RegEnemy&&) = default;//move copy c-tor (rvalue)
	RegEnemy& operator=(RegEnemy&&) = delete;//move assigment operator (rvalue)
private:
	Enemies typeEnemy;
};

