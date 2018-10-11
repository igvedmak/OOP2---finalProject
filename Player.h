#pragma once
#include "DynamicObject.h"
#include "AssetIDs.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include <cmath>
#include "GameClock.h"

//Strategy example: player attack
class AttackBehavior
{
public:
	virtual void Attack(Player & ) = 0;
};

class Player : public DynamicObject
{
public:
	explicit Player(const sf::Vector2f& position, const sf::Texture &t);
	Player(const Player&) = delete;//copy c-tor (lvalue)
	Player& operator=(const Player&) = delete; //assignment operator (lvalue)
	Player(Player&&) = default;//move copy c-tor (rvalue)
	Player& operator=(Player&&) = delete;//move assigment operator (rvalue)
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	bool inRange(size_t x) const;
	//void handle(size_t x, const Direction& dir);
	void entityDead() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * 0, CLAW_DEATH * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityHit(int) override {};
	void entityLeft() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_RUN * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); m_sprite.setScale({ -1, 1 }); };
	void entityStay() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_STAY * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityDown() override {m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_CLIMB * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityUp() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_CLIMB * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void stayAtPlace() override { m_sprite.move(0, 0); }
	void entityPunch() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* m_frame, CLAW_PUNCH * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityPunch2() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* FRAME_LIMIT_CLAW_ATTACK, CLAW_PUNCH * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityKick() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* m_frame, CLAW_KICK * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityJump() override { m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* m_frame, CLAW_JUMP * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); };
	void entityShot() override{ m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* m_frame, CLAW_SHOT * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT)); }
	void moveLeft() override { m_sprite.move(-m_velocity.x, 0); }
	void moveRight() override { m_sprite.move(m_velocity.x, 0); }
	void moveUp() override { m_sprite.move(0, -m_velocity.y); }
	void moveDown() override { m_sprite.move(0, m_velocity.y); }
	Direction changeDir(Direction dir) override { return Right; };
	Direction getDir()override { return Right; };
	float m_jumpStart = 0;
	bool m_canJump = false;
	void setJump() {m_jumpStart = GameClock::getInstance().getElapsedTime();}
	bool isJumping() { return m_jumpStart != 0 && !GameClock::getInstance().isTimePassed(m_jumpStart, 0.5f);  }
	void setCanJump(bool jump) {m_canJump = jump;}
	bool canJump() { return m_canJump; }
	void update() override;
	bool handleInupt(Input input) override;

	//life functions
	int getLife() { return m_life; }
	bool getDeadStatus() { return isDead; }
	void setDeadStatus(bool deadStatus) { isDead = deadStatus; }
	void setLife(int health) { m_life = health; }
	void reduceLife(int reduceNum) { m_life -= reduceNum; }
	void increaseLife(int increaseNum) { m_life += increaseNum; }

	//collision
	void collideWithLadder(const std::shared_ptr<Ladder> ladder);
	bool getLadderStatus() { return isCollidingLadder; }
	

private:
	//details
	int m_life;
	bool isDead = false;

	class PlayerState
	{
	public:
		virtual ~PlayerState() { }
		virtual std::unique_ptr<PlayerState> handleInput(Input input) = 0;
		virtual void enter(Player& obj) = 0;
		virtual void update(Player& obj) = 0;
	};

	class StandingPlayerState
		: public PlayerState {
	public:
		~StandingPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_canUp = false;
		bool m_canDown = false;
		//bool m_onLadder = false;
	};

	class AttackingPlayerState : public PlayerState {
	public:
		~AttackingPlayerState() { }

		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd;
		int m_rnd = rand() % 4;
	};

	class ShootPlayerState : public PlayerState {
	public:
		~ShootPlayerState() {  }

		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd;
	};

	class LeftPlayerState : public PlayerState {
	public:
		~LeftPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	};

	class RightPlayerState
		: public PlayerState {
	public:
		~RightPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	};

	class UpPlayerState
		: public PlayerState {
	public:
		~UpPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd = false;
		bool m_canDown = false;
	};

	class UpStayPlayerState
		: public PlayerState {
	public:
		~UpStayPlayerState() { }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd;
	};

	class DownStayPlayerState
		: public PlayerState {
	public:
		~DownStayPlayerState() { }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd;
	};

	class DownPlayerState
		: public PlayerState {
	public:
		~DownPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_isEnd = false;
	};

	class FallPlayerState
		: public PlayerState {
	public:
		~FallPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endFall = false;
	};

	class FallRightPlayerState
		: public PlayerState {
	public:
		~FallRightPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endFall = false;
	};

	class FallLeftPlayerState
		: public PlayerState {
	public:
		~FallLeftPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endFall = false;
	};

	class JumpPlayerState
		: public PlayerState {
	public:
		~JumpPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endJump = false;
		bool m_canClimb = false;
	};

	class JumpRightPlayerState
		: public PlayerState {
	public:
		~JumpRightPlayerState() { }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endJump = false;
	};

	class JumpLeftPlayerState
		: public PlayerState {
	public:
		~JumpLeftPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endJump = false;
	};

	class DeathPlayerState
		: public PlayerState {
	public:
		~DeathPlayerState() {  }
		std::unique_ptr<PlayerState> handleInput(Input input);
		void enter(Player& obj);
		void update(Player& obj);
	private:
		bool m_endJump = false;
		float delta = 0;
	};

	std::unique_ptr<Player::PlayerState> m_state;
	bool isCollidingLadder = false;
	std::unique_ptr<AttackBehavior>	pAttackBehavior_;
	float lastLadderX;
	
public:
	void moveJump() override {
		JumpData Data;
		m_sprite.move(0, -m_velocity.y);
	}
	void entityRight()override {
		m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_RUN * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT));
		m_sprite.setScale({ 1, 1 });
	};
	void entityAttack()override {
		if (m_frame == FRAME_LIMIT_CLAW_ATTACK)
			m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH* m_frame, CLAW_ATTACK * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT));
		else
			m_sprite.setTextureRect(sf::IntRect(CLAW_WIDTH * m_frame, CLAW_ATTACK * CLAW_WIDTH, CLAW_WIDTH, CLAW_HEIGHT));
	};
	//attack behavior
	void PerformAttack() {
		pAttackBehavior_->Attack(*this);
	}
	void SetAttackBehavior(std::unique_ptr<AttackBehavior>	pAttackBehavior) {
		pAttackBehavior_ = std::move(pAttackBehavior);
	}
};
// attack behavior
class PunchAttackBehavior :public AttackBehavior
{
public:
	void Attack(Player & punchPlayer){
		punchPlayer.entityPunch();
		Source::instance().getuppercutSound().play();
	}
};
class KickAttackBehavior :public AttackBehavior
{
public:
	void Attack(Player & punchPlayer) {
		punchPlayer.entityKick();
		Source::instance().getuppercutSound().play();
	}
};
class Punch2AttackBehavior :public AttackBehavior
{
public:
	void Attack(Player & punchPlayer) {
		punchPlayer.entityPunch2();
		Source::instance().getuppercutSound().play();
	}
};
class SwordAttackBehavior :public AttackBehavior
{
public:
	void Attack(Player & punchPlayer) {
		punchPlayer.entityAttack();
		Source::instance().getswishSound().play();
	}
};