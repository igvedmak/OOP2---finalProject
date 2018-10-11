#include "SpecialSword.h"

SpecialSword::SpecialSword(const sf::Vector2f& position, const sf::Texture &t) 
	: Shots(position, t), typesword(REGULARSWORD) {}
