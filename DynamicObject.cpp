#include "DynamicObject.h"

//constractor
DynamicObject::DynamicObject(sf::Vector2f coords, const sf::Texture& t, sf::Vector2f vel)
	:Object(coords, t), m_velocity(vel), m_frame(0), m_score(0){}

void DynamicObject::collideWithTile(const std::shared_ptr<Tile> tile)
{
	if (getBottom() >= tile->getSprite().getPosition().y)
		moveUp();
}

void DynamicObject::collideWithWall(const std::shared_ptr<Wall> wall)
{
	if ((getLeft() <= wall->getRight()) && (m_sprite.getPosition().x > wall->getSprite().getPosition().x)) 
		moveRight();
	else if (getRight() >= wall->getLeft() && (m_sprite.getPosition().x < wall->getSprite().getPosition().x)) 
		moveLeft();
}

void DynamicObject::collideWithEnemyWall(const std::shared_ptr<Wall> wall)
{
	if ((getLeft() <= wall->getRight()) && (m_sprite.getPosition().x > wall->getSprite().getPosition().x))
		moveRight(); 
	else if (getRight() >= wall->getLeft() && (m_sprite.getPosition().x < wall->getSprite().getPosition().x))
		moveLeft();
	changeDir(getDir());
}

void DynamicObject::collideWithWallTile(const std::shared_ptr<WallTile> walltile)
{
	if ((getBottom() - 70.f) >= walltile->getSprite().getPosition().y) {
		onGround = true;
		moveUp();
	}
	else
		onGround = false;
}

void DynamicObject::collideWithPlayerEnd(const std::shared_ptr<emptyHelper> empty) {
	if (getBottom() >= empty->getSprite().getPosition().y)
		moveUp();
}


