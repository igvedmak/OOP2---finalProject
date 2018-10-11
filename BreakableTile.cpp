#include "BreakableTile.h"

//bool BreakableTile::m_registerit = SpawnManager<char, StaticObject>::registerit(SPIKES5_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<BreakableTile>(pos, Source::instance().getSpkies5Texture()); });

BreakableTile::BreakableTile(const sf::Vector2f& position, const sf::Texture &t)
	: Obstacle(position, t) {}