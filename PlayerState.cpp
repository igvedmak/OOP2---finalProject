#include "PlayerState.h"
#include "Player.h"

std::unique_ptr<Player::PlayerState> Player::StandingPlayerState::handleInput(Input input) {
	switch (input)
	{
		case PRESS_UP:
			if(m_canUp)
				return std::make_unique<Player::UpPlayerState>();
			break;
		case RELEASE_UP:
			break;
		case PRESS_DOWN:
			if (m_canDown)
				return std::make_unique<Player::DownPlayerState>();
			break;
		case RELEASE_DOWN:
			break;
		case PRESS_LEFT:
			return std::make_unique<Player::LeftPlayerState>();
			break;
		case RELEASE_LEFT:
			break;
		case PRESS_RIGHT:
			return std::make_unique<Player::RightPlayerState>();
			break;
		case RELEASE_RIGHT:
			break;
		case PRESS_R:
			return std::make_unique<Player::AttackingPlayerState>();
			break;
		case NONE:
			break;
		case PRESS_SPACE:
			return std::make_unique<Player::JumpPlayerState>();
			break;
		case RELEASE_SPACE:
			break;
		case PRESS_ALT:
			return std::make_unique<Player::ShootPlayerState>();
			break;
		case DEATH:
			return std::make_unique<Player::DeathPlayerState>();
			break;
		default:
			break;
	}
	return nullptr;
}

void Player::StandingPlayerState::enter(Player & obj) {
	obj.entityStay();
	obj.resetFrame();
	obj.m_isAttack = false;
}

void Player::StandingPlayerState::update(Player & obj) {
	obj.entityStay();
	obj.increaseFrame();
	obj.stayAtPlace();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_STAY)
		obj.resetFrame();
	m_canUp = obj.getLadderStatus();
	m_canDown = obj.getLadderStatus();
	if (!m_canDown) {
		obj.moveDown();
	}
}

std::unique_ptr<Player::PlayerState> Player::AttackingPlayerState::handleInput(Input input) {
	if (m_isEnd) 
		return std::make_unique<Player::StandingPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::AttackingPlayerState::enter(Player & obj) {
	obj.resetFrame();
	obj.m_isAttack = true;
	switch (m_rnd) {
	case 0:
		obj.SetAttackBehavior(std::make_unique<SwordAttackBehavior>());
		break;
	case 1:
		obj.SetAttackBehavior(std::make_unique<PunchAttackBehavior>());
		break;
	case 2:
		obj.SetAttackBehavior(std::make_unique<KickAttackBehavior>());
		break;
	case 3:
		obj.SetAttackBehavior(std::make_unique<Punch2AttackBehavior>());
		break;
	}
}

void Player::AttackingPlayerState::update(Player & obj) {
	if (!m_isEnd) {
		obj.PerformAttack();
		if(obj.getFrame() == FRAME_LIMIT_CLAW_ATTACK)
			m_isEnd = true;
		obj.increaseFrame();
	}
}


std::unique_ptr<Player::PlayerState> Player::ShootPlayerState::handleInput(Input input) {
	if (m_isEnd)
		return std::make_unique<Player::StandingPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::ShootPlayerState::enter(Player & obj) {
	obj.resetFrame();
}

void Player::ShootPlayerState::update(Player & obj) {
	if (!m_isEnd) {
		obj.entityShot();
		Source::instance().getShotSound().play();
		if (obj.getFrame() == FRAME_LIMIT_CLAW_SHOOT)
			m_isEnd = true;
		obj.increaseFrame();
	}
}


std::unique_ptr<Player::PlayerState> Player::LeftPlayerState::handleInput(Input input)
{
	if (input == RELEASE_LEFT)
		return std::make_unique<StandingPlayerState>();
	else if (input == PRESS_SPACE)
		return std::make_unique<JumpLeftPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::LeftPlayerState::enter(Player & obj){
	obj.resetFrame();
}

void Player::LeftPlayerState::update(Player & obj){
	obj.entityLeft();
	obj.increaseFrame();
	obj.moveLeft();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_RUN)
		obj.resetFrame();
	Source::instance().getWalkSound().play();
}

std::unique_ptr<Player::PlayerState> Player::RightPlayerState::handleInput(Input input)
{
	if (input == RELEASE_RIGHT)
		return std::make_unique<StandingPlayerState>();
	else if (input == PRESS_SPACE)
		return std::make_unique<JumpRightPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::RightPlayerState::enter(Player & obj){
	obj.resetFrame();
}

void Player::RightPlayerState::update(Player & obj){
	obj.entityRight();
	obj.increaseFrame();
	obj.moveRight();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_RUN)
		obj.resetFrame();
	Source::instance().getWalkSound().play();
}

std::unique_ptr<Player::PlayerState> Player::UpPlayerState::handleInput(Input input)
{
	if (input == RELEASE_UP) 
		return std::make_unique<Player::UpStayPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	else if (m_isEnd) 
		return std::make_unique<Player::StandingPlayerState>();
	 
	return nullptr;
}

void Player::UpPlayerState::enter(Player & obj){
		obj.resetFrame();
		obj.m_sprite.setPosition(obj.lastLadderX, obj.m_sprite.getPosition().y);
}

void Player::UpPlayerState::update(Player & obj){
	obj.entityUp();
	obj.increaseFrame();
	obj.moveUp();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_CLIMB)
		obj.resetFrame();
	m_isEnd = !obj.getLadderStatus();
	m_canDown = obj.getLadderStatus();
}

std::unique_ptr<Player::PlayerState> Player::DownPlayerState::handleInput(Input input)
{
	if (input == RELEASE_DOWN)
		return std::make_unique<Player::DownStayPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	else if (m_isEnd)
		return std::make_unique<Player::StandingPlayerState>();
	return nullptr;
}

void Player::DownPlayerState::enter(Player & obj){
	obj.resetFrame();
}

void Player::DownPlayerState::update(Player & obj){
	obj.entityDown();
	obj.increaseFrame();
	obj.moveDown();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_CLIMB)
		obj.resetFrame();
	m_isEnd = !obj.getLadderStatus();
}

std::unique_ptr<Player::PlayerState> Player::JumpPlayerState::handleInput(Input input)
{
	if (m_endJump)
		return std::make_unique<FallPlayerState>();
	else if (input == PRESS_LEFT)
		return std::make_unique<JumpLeftPlayerState>();
	else if (input == PRESS_RIGHT)
		return std::make_unique<JumpRightPlayerState>();
	else if (m_canClimb && input == PRESS_UP) 
		return std::make_unique<Player::UpPlayerState>();
	else if (m_canClimb && input == PRESS_DOWN) 
		return std::make_unique<Player::DownPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();

	return nullptr;
}

void Player::JumpPlayerState::enter(Player & obj){
	obj.resetFrame();
	obj.setJump();
}

void Player::JumpPlayerState::update(Player & obj){
	obj.moveJump();
	obj.increaseFrame();
	obj.entityJump();
	if (!obj.isJumping())
		m_endJump = true;
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
	m_canClimb = obj.getLadderStatus();

}

std::unique_ptr<Player::PlayerState> Player::JumpRightPlayerState::handleInput(Input input) {
	if (m_endJump)
		return std::make_unique<FallRightPlayerState>();
	else if (input == RELEASE_RIGHT)
		return std::make_unique<JumpPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::JumpRightPlayerState::enter(Player & obj) {
	obj.resetFrame();
	if (!obj.isJumping()) {
		obj.setJump();
	}
}

void Player::JumpRightPlayerState::update(Player & obj) {
	obj.moveJump();
	obj.moveRight();
	obj.increaseFrame();
	obj.entityJump();
	if (!obj.isJumping())
		m_endJump = true;
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
}

std::unique_ptr<Player::PlayerState> Player::JumpLeftPlayerState::handleInput(Input input){
	if (m_endJump)
		return std::make_unique<FallLeftPlayerState>();
	else if (input == RELEASE_LEFT)
		return std::make_unique<JumpPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::JumpLeftPlayerState::enter(Player & obj){
	obj.resetFrame();
	if (!obj.isJumping())
		obj.setJump();
}

void Player::JumpLeftPlayerState::update(Player & obj){
	obj.moveJump();
	obj.moveLeft();
	obj.increaseFrame();
	obj.entityJump();
	if (!obj.isJumping())
		m_endJump = true;
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
}

std::unique_ptr<Player::PlayerState> Player::UpStayPlayerState::handleInput(Input input) {
	if (input == PRESS_UP)
		return std::make_unique<UpPlayerState>();
	else if (input == PRESS_DOWN)
		return std::make_unique<DownStayPlayerState>();
	else if (input == PRESS_SPACE)
		return std::make_unique<JumpPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	else if (m_isEnd)
		return std::make_unique<StandingPlayerState>();
	return nullptr;
}

void Player::UpStayPlayerState::enter(Player & obj) {}

void Player::UpStayPlayerState::update(Player & obj) {
	m_isEnd = !obj.getLadderStatus();
}

std::unique_ptr<Player::PlayerState> Player::DownStayPlayerState::handleInput(Input input) {
	if (input == PRESS_DOWN)
		return std::make_unique<DownPlayerState>();
	else if (input == PRESS_UP)
		return std::make_unique<UpStayPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	else if (m_isEnd)
		return std::make_unique<StandingPlayerState>();
	return nullptr;
}

void Player::DownStayPlayerState::enter(Player & obj) {}

void Player::DownStayPlayerState::update(Player & obj) {
	m_isEnd = !obj.getLadderStatus();
}

std::unique_ptr<Player::PlayerState> Player::FallPlayerState::handleInput(Input input)
{
	if(m_endFall)
		return std::make_unique<Player::StandingPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::FallPlayerState::enter(Player & obj){}

void Player::FallPlayerState::update(Player & obj){
	m_endFall = obj.isOnGround();
	obj.increaseFrame();
	obj.entityJump();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
	if (!m_endFall) {
		obj.moveDown();
	}
}

std::unique_ptr<Player::PlayerState> Player::FallRightPlayerState::handleInput(Input input)
{
	if (m_endFall)
		return std::make_unique<Player::StandingPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::FallRightPlayerState::enter(Player & obj) {}

void Player::FallRightPlayerState::update(Player & obj) {
	m_endFall = obj.isOnGround();
	obj.increaseFrame();
	obj.entityJump();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
	if (!m_endFall) {
		obj.moveRight();
		obj.moveDown();
	}
}

std::unique_ptr<Player::PlayerState> Player::FallLeftPlayerState::handleInput(Input input)
{
	if (m_endFall)
		return std::make_unique<Player::StandingPlayerState>();
	else if (input == DEATH)
		return std::make_unique<DeathPlayerState>();
	return nullptr;
}

void Player::FallLeftPlayerState::enter(Player & obj) {}

void Player::FallLeftPlayerState::update(Player & obj) {
	m_endFall = obj.isOnGround();
	obj.increaseFrame();
	obj.entityJump();
	if (obj.getFrame() == FRAME_LIMIT_CLAW_JUMP)
		obj.resetFrame();
	if (!m_endFall) {
		obj.moveLeft();
		obj.moveDown();
	}
}

std::unique_ptr<Player::PlayerState> Player::DeathPlayerState::handleInput(Input input){
	return nullptr;
}

void Player::DeathPlayerState::enter(Player & obj) {
	delta = GameClock::getInstance().getElapsedTime();
	obj.resetFrame();
}

void Player::DeathPlayerState::update(Player & obj) {
	Source::instance().getDeathSound().play();
	obj.entityDead();
	if(GameClock::getInstance().isTimePassed(delta, 2.f))
		obj.isDead = true;
}