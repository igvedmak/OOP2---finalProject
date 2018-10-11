#include "SmartEnemy.h"

SmartEnemy::SmartEnemy(const sf::Vector2f& position, const sf::Texture &t)
	: Enemy(position, t), typeEnemy(smart) {}
