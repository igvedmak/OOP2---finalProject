#pragma once
#include "Obstacle.h"
class Spkies : public Obstacle
{
public:
	explicit Spkies(const sf::Vector2f& position, const sf::Texture &t);
	Spkies(const Spkies&) = delete;//copy c-tor (lvalue)
	Spkies& operator=(const Spkies&) = delete; //assignment operator (lvalue)
	Spkies(Spkies&&) = default;//move copy c-tor (rvalue)
	Spkies& operator=(Spkies&&) = delete;//move assigment operator (rvalue)

private:
	static bool m_registerit;
	static bool m_registerit1;	
	static bool m_registerit2;
	static bool m_registerit3;
	static bool m_registerit4;
	static bool m_registerit5;
};

