#include "GameClock.h"

GameClock & GameClock::getInstance() {
	static GameClock instance;
	return instance;
}

bool GameClock::isTimePassed(float time, float seconds) {
	return m_clock.getElapsedTime().asSeconds() - time > seconds;
}

float GameClock::getElapsedTime() {
	return m_clock.getElapsedTime().asSeconds();
}

GameClock::GameClock(){}


GameClock::~GameClock(){}
