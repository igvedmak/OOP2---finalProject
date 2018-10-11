#include "Ladder.h"

bool Ladder::m_registerit = SpawnManager<char, StaticObject>::registerit(LADDER_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Ladder>(pos, Source::instance().getLadderTexture()); });
bool Ladder::m_registerit1 = SpawnManager<char, StaticObject>::registerit(LADDER2_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Ladder>(pos, Source::instance().getLadder2Texture()); });

Ladder::Ladder(const sf::Vector2f& position, const sf::Texture &t)
	: StaticObject(position, t){}

