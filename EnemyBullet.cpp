#include "EnemyBullet.h"
// Function which set Bullet position by getting the enemy position and
// locate the bulllet in the middle of the enemy object 
void EnemyBullet::setBulletPosition(sf::Vector2f position, Direction dir)
{
	int add = 0;

	switch (m_dir)
	{
	case Right:
		add = BULLET_ADD;
		break;
	case Left:
		add = -BULLET_ADD;
		break;
	default:
		add = BULLET_ADD;
		break;
	}

	m_sprite.setPosition(position.x + add, position.y);
}