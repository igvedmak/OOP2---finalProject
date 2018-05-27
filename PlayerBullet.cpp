#include "PlayerBullet.h"

// Constructor which use base class constructor and do intRect to the relvant texture
PlayerBullet::PlayerBullet(sf::Vector2f place) : Bullets(place)
{
	//m_sprite.setTextureRect(sf::IntRect(0, WIZARD_BULLET_ROW * MOVE_SIZE, MOVE_SIZE, MOVE_SIZE));
	//m_sprite.setPosition(place.x *  POSITION, (place.y *  POSITION) - DIF);
}

//----------------------------------------------------------------------------
// Function which check collision of sfml : intersect of this class object eith obj she get 
bool PlayerBullet::isCollide(Object & obj)
{
	return m_sprite.getGlobalBounds().intersects(obj.getSprite().getGlobalBounds());
}

//----------------------------------------------------------------------------
// Function of the move of the current bullet object by move of the sfml
void PlayerBullet::move(const Direction dir, float speed)
{
	switch (dir) {
	case Direction::Right:
		m_sprite.move(speed, 0);
		break;
	case Direction::Left:
		m_sprite.move(-speed, 0);
		break;
	default:
		m_sprite.move(speed, 0);
		break;
	}
}

//----------------------------------------------------------------------------
// Function which set Bullet position by getting the wizard position and
// locate the bulllet in the middle of the wizard object 
void PlayerBullet::setBulletPosition(sf::Vector2f position, Direction dir)
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