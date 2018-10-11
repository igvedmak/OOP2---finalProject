#pragma once
#include "Object.h"
#include "Tile.h"
#include "Wall.h"
#include "HealthPotion.h"
#include "Token.h"
#include "Ladder.h"
#include "PlayerState.h"
#include "emptyHelper.h"
class Tile;
class Wall;
class HealthPotion;
class Token;
class Ladder;
class WallTile;
class emptyHelper;
class DynamicObject : public Object
{
public:
	explicit DynamicObject(sf::Vector2f coords, const sf::Texture& t, sf::Vector2f vel);
	DynamicObject(const DynamicObject&) = delete;//copy c-tor (lvalue)
	DynamicObject& operator=(const DynamicObject&) = delete; //assignment operator (lvalue)
	DynamicObject(DynamicObject&&) = default;//move copy c-tor (rvalue)
	DynamicObject& operator=(DynamicObject&&) = delete;//move assigment operator (rvalue)
	int getScore() const { return m_score; }
	void move() { m_sprite.move(m_velocity); }
	const sf::Vector2f& getVelocity() const { return m_velocity; }
	void setVelocity(const sf::Vector2f& newVel) { m_velocity = newVel; }
	void incDecVelocity(float x, float y) { if (m_velocity.x + x > 0) setVelocity(sf::Vector2f(m_velocity.x + x, m_velocity.y + y)); }
	// for entity
	virtual void moveJump() = 0;
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual void moveUp() { m_sprite.move(0, -m_velocity.y); }
	virtual void moveDown() { m_sprite.move(0, m_velocity.y); }
	virtual void stayAtPlace() { m_sprite.move(0, 0); }
	virtual void entityRight() = 0;
	virtual void entityLeft() = 0;
	virtual void entityStay() = 0;
	virtual void entityDown() = 0;
	virtual void entityUp() = 0;
	virtual void entityAttack() = 0;
	virtual void entityPunch() = 0;
	virtual void entityPunch2() = 0;
	virtual void entityKick() = 0;
	virtual void entityJump() = 0;
	virtual void entityShot() = 0;
	virtual void entityDead() = 0;
	virtual void entityHit(int) = 0;
	virtual int increaseFrame() { return m_frame++; };
	virtual void resetFrame() { m_frame = 0; };
	virtual int getFrame() { return m_frame; };

	//collision
	void collideWithTile(const std::shared_ptr<Tile> tile);
	void collideWithWall(const std::shared_ptr<Wall> wall);
	void collideWithWallTile(const std::shared_ptr<WallTile> walltile);
	void collideWithPlayerEnd(const std::shared_ptr<emptyHelper> empty);
	void collideWithEnemyWall(const std::shared_ptr<Wall> wall);
	bool isOnGround() { return onGround; }

	//jumping
	bool canJump() { return able2jump; }
	void setCanJump(bool jumpStatus) { able2jump = jumpStatus; }
	void setSpeedValue(float newSpeed) { speedValue = newSpeed; }

	// direction for enemies
	virtual Direction changeDir(Direction dir) = 0;
	virtual Direction getDir() = 0;

	virtual void update() = 0;
	virtual bool handleInupt(Input input) = 0;
	bool isAttack() { return m_isAttack;  };
private:
	bool onGround = false;

protected:
	bool m_isAttack = false;
	int m_frame; // for frames
	int m_score; // score
	Direction m_nextDir = Right; // dir for enemies
	sf::Vector2f m_velocity; // speed of sprites
	// for jumping
	bool able2jump = true;
	float speedValue = 0;
};

