#pragma once
#include "DynamicObject.h"
#include "Constants.h"
#include "CollisionManager.h"

class Player;
/*
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

class JumpPlayerState
	: public PlayerState {
public:
	~JumpPlayerState() {  }
	std::unique_ptr<PlayerState> handleInput(Input input);
	void enter(Player& obj);
	void update(Player& obj);
private:
	bool m_endJump = false;
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
};*/