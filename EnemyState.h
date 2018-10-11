#pragma once
#include "DynamicObject.h"
#include "Constants.h"
#include "CollisionManager.h"

class Enemy;

//class EnemyState
//{
//public:
//	virtual ~EnemyState() { }
//	virtual std::unique_ptr<EnemyState> handleInput(Input input) = 0;
//	virtual void enter(Enemy& obj) = 0;
//	virtual void update(Enemy& obj) = 0;
//};
//
//class StandingEnemyState
//	: public EnemyState {
//public:
//	~StandingEnemyState() { /* ... */ }
//	std::unique_ptr<EnemyState> handleInput(Input input);
//	void enter(Enemy& obj);
//	void update(Enemy& obj);
//};
//
//class AttackingEnemyState
//	: public EnemyState {
//public:
//	~AttackingEnemyState() { /* ... */ }
//	std::unique_ptr<EnemyState> handleInput(Input input);
//	void enter(Enemy& obj);
//	void update(Enemy& obj);
//private:
//	bool m_isEnd;
//};
//
//class LeftEnemyState : public EnemyState {
//public:
//	~LeftEnemyState() { /* ... */ }
//	std::unique_ptr<EnemyState> handleInput(Input input);
//	void enter(Enemy& obj);
//	void update(Enemy& obj);
//};
//
//class RightEnemyState
//	: public EnemyState {
//public:
//	~RightEnemyState() { /* ... */ }
//	std::unique_ptr<EnemyState> handleInput(Input input);
//	void enter(Enemy& obj);
//	void update(Enemy& obj);
//};
