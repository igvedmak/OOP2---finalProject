#pragma once
#include "StaticObject.h"
class Pickup : public StaticObject
{
public:
	explicit Pickup(const sf::Vector2f& position, const sf::Texture &t);
	Pickup(const Pickup&) = delete;//copy c-tor (lvalue)
	Pickup& operator=(const Pickup&) = delete; //assignment operator (lvalue)
	Pickup(Pickup&&) = default;//move copy c-tor (rvalue)
	Pickup& operator=(Pickup&&) = delete;//move assigment operator (rvalue)

	//for removing picked up objects
	bool isUsed() { return isPicked; }
	void set2used() { isPicked = true; }

private:
	bool isPicked = false;
};

