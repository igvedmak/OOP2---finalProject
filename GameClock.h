#pragma once
#include "Constants.h"
class GameClock
{
public:
	static GameClock & getInstance();
	bool isTimePassed(float time, float seconds);
	float getElapsedTime();
private:
	sf::Clock m_clock;
	GameClock();
	~GameClock();
};

