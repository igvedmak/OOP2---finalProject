#include "EnemyState.h"
#include "Enemy.h"
std::unique_ptr<Enemy::EnemyState> Enemy::StandingEnemyState::handleInput(Input input) {
	switch (input)
	{
	case PRESS_LEFT:
		return std::make_unique<LeftEnemyState>();
		break;
	case RELEASE_LEFT:
		break;
	case PRESS_RIGHT:
		return std::make_unique<RightEnemyState>();
		break;
	case RELEASE_RIGHT:
		break;
	case PRESS_R:
		return std::make_unique<AttackingEnemyState>();
		break;
	case NONE:
		break;
	default:
		break;
	}
	return nullptr;
}

void Enemy::StandingEnemyState::enter(Enemy & obj) {
	obj.entityStay();
	obj.resetFrame();
	obj.m_isAttack = false;
}

void Enemy::StandingEnemyState::update(Enemy & obj) {
	obj.entityStay();
	obj.increaseFrame();
	obj.stayAtPlace();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_ENEMY_STAY)
		obj.resetFrame();
}

std::unique_ptr<Enemy::EnemyState> Enemy::AttackingEnemyState::handleInput(Input input) {
	if (m_isEnd) {
		return std::make_unique<StandingEnemyState>();
	}
	return nullptr;
}

void Enemy::AttackingEnemyState::enter(Enemy & obj) {
	obj.resetFrame();
	obj.m_isAttack = true;
}

void Enemy::AttackingEnemyState::update(Enemy & obj) {
	if (!m_isEnd) {
		obj.entityAttack();
		if (obj.getFrame() == FRAME_LIMIT_ENEMY_ATTACK + 1) {
			Source::instance().getswishSound().play();
			m_isEnd = true;
		}
		obj.increaseFrame();
	}
}

std::unique_ptr<Enemy::EnemyState> Enemy::LeftEnemyState::handleInput(Input input)
{
	if (input == RELEASE_LEFT) 
		return std::make_unique<StandingEnemyState>();
	else if (input == PRESS_RIGHT) 
		return std::make_unique<RightEnemyState>();
	else if (input == PRESS_R) 
		return std::make_unique<AttackingEnemyState>();
	return nullptr;
}

void Enemy::LeftEnemyState::enter(Enemy & obj) {
	obj.resetFrame();
}

void Enemy::LeftEnemyState::update(Enemy & obj) {
	obj.entityLeft();
	obj.increaseFrame();
	obj.moveLeft();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_ENEMY_WALK)
		obj.resetFrame();
	Source::instance().getWalkSound().play();
}

std::unique_ptr<Enemy::EnemyState> Enemy::RightEnemyState::handleInput(Input input)
{
	if (input == RELEASE_RIGHT) 
		return std::make_unique<StandingEnemyState>();
	else if (input == PRESS_LEFT)
		return std::make_unique<LeftEnemyState>();
	else if (input == PRESS_R)
		return std::make_unique<AttackingEnemyState>();
	return nullptr;
}

void Enemy::RightEnemyState::enter(Enemy & obj) {
	obj.resetFrame();
}

void Enemy::RightEnemyState::update(Enemy & obj) {
	obj.entityRight();
	obj.increaseFrame();
	obj.moveRight();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_ENEMY_WALK)
		obj.resetFrame();
	Source::instance().getWalkSound().play();
}


std::unique_ptr< Enemy::EnemyState> Enemy::DeadEnemyState::handleInput(Input input)
{
	return nullptr;
}

void Enemy::DeadEnemyState::enter(Enemy & obj)
{
	obj.resetFrame();
}

void Enemy::DeadEnemyState::update(Enemy & obj){
	if (m_counter < 5) {
		m_counter++;
		Source::instance().getEnemyDeathSound().play();
		obj.entityDead();
	} else {
		obj.m_toRemove = true;
	}
}


std::unique_ptr<Enemy::EnemyState> Enemy::HitEnemyState::handleInput(Input input)
{
	if (input == NONE) {
		if (m_isDead)
			return std::make_unique<DeadEnemyState>();
		if(waitForEntity)
			return std::make_unique<StandingEnemyState>();
	}
	return nullptr;
}

void Enemy::HitEnemyState::enter(Enemy & obj) {
	waitForEntity = false;
	delta = GameClock::getInstance().getElapsedTime();
	m_isDead = obj.isDead();
	obj.resetFrame();
}

void Enemy::HitEnemyState::update(Enemy & obj){
	obj.entityHit(0);
	Source::instance().getEnemyHitSound().play();
	m_isDead = obj.isDead();
	if (GameClock::getInstance().isTimePassed(delta, 6.f))
		waitForEntity = true;
}
