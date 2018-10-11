#include "RegEnemy.h"

RegEnemy::RegEnemy(const sf::Vector2f& position, const sf::Texture &t)
	: Enemy(position, t), typeEnemy(dumb) {}
