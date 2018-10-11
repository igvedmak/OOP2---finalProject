#pragma once
#include "DynamicObject.h"
#include "GameClock.h"
#include "EnemyState.h"

class Enemy : public DynamicObject{
public:
	void moveLeft() override{ m_sprite.move(-m_velocity.x, 0); }
	void moveRight()override { m_sprite.move(m_velocity.x, 0); }
	void stayAtPlace() override { m_sprite.move(0, 0); }
	void moveJump() {};
	void entityStay() override { m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * m_frame, CLAW_STAY * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT)); };
	void entityDown() {};
	void entityUp() {};
	void entityAttack() override { m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * m_frame, CLAW_CLIMB * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT)); };
	void entityHit(int which) override { m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * which, CLAW_JUMP * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT)); };
	void entityPunch() {};
	void entityPunch2() {};
	void entityKick() {};
	void entityJump() {};
	void entityShot() {};
	bool isTarget() { return m_target != nullptr; }
	Direction getDir()override { return m_dir; }
	int getLimitJumpFrame() { return 0; }
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	explicit Enemy(const sf::Vector2f& position, const sf::Texture &t);
	Enemy(const Enemy&) = delete;//copy c-tor (lvalue)
	Enemy& operator=(const Enemy&) = delete; //assignment operator (lvalue)
	Enemy(Enemy&&) = default;//move copy c-tor (rvalue)
	Enemy& operator=(Enemy&&) = delete;//move assigment operator (rvalue)
	Direction getDirection() { return m_dir; }
	std::shared_ptr<Object> m_target = nullptr;
	void setTarget(std::shared_ptr<Object> obj) { m_target = obj; }
	float getLastTime() { return lastTime; }
	void setLastTime() { lastTime = GameClock::getInstance().getElapsedTime(); }
	bool getWallStatus() { return isCollidingWall; }
	void update() override;
	bool handleInupt(Input input) override;
	void decLifePoints() { 
		lifePointer--; 
		m_state = std::make_unique<HitEnemyState>();
	}
	bool isDead() { 
		return lifePointer <= 0; 
	}
	bool getToRemove() { return m_toRemove; }

public:
	Direction changeDir(Direction dir) override {
		if (dir == Right)
			m_dir = Left;
		else
			m_dir = Right;
		return m_dir;
	}
	void gotoTarget() {
		if (m_target != nullptr) {
			if (m_target->getCenter().x - getCenter().x < 0)
				m_dir = Left;
			else
				m_dir = Right;
		}
	}
	sf::Vector2f getCenter() const {
		auto rect = m_sprite.getGlobalBounds();
		return { rect.left + rect.width / 2, rect.top + rect.height / 2 };
	}
	void entityRight() override {
		m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * m_frame, CLAW_RUN * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT));
		m_sprite.setScale({ -1, 1 });
	};
	void entityLeft() override {
		m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * m_frame, CLAW_RUN * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT));
		m_sprite.setScale({ 1, 1 });
	};
	void entityDead() override { m_sprite.setTextureRect(sf::IntRect(ENEMY_WIDTH * 0, 5 * ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT));}

public:
	class EnemyState
	{
	public:
		virtual ~EnemyState() { }
		virtual std::unique_ptr<EnemyState> handleInput(Input input) = 0;
		virtual void enter(Enemy& obj) = 0;
		virtual void update(Enemy& obj) = 0;
	};

	class StandingEnemyState
		: public EnemyState {
	public:
		~StandingEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	};

	class AttackingEnemyState
		: public EnemyState {
	public:
		~AttackingEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	private:
		bool m_isEnd;
	};

	class LeftEnemyState : public EnemyState {
	public:
		~LeftEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	};

	class HitEnemyState : public EnemyState {
	public:
		~HitEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	private:
		bool m_isDead = false;
		bool waitForEntity = false;
		float delta = 0;
	};

	class DeadEnemyState : public EnemyState {
	public:
		~DeadEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	private:
		int m_counter = 0;
	};

	class RightEnemyState
		: public EnemyState {
	public:
		~RightEnemyState() { /* ... */ }
		std::unique_ptr<EnemyState> handleInput(Input input);
		void enter(Enemy& obj);
		void update(Enemy& obj);
	};
private:
	bool m_registerit;
	Direction m_dir = Right;
	float lastTime = 0;
	bool isCollidingWall = false;
	std::unique_ptr<Enemy::EnemyState> m_state;
	int lifePointer;
	bool m_toRemove = false;
};
