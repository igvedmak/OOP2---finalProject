#include "WallTile.h"

bool WallTile::m_registerit = SpawnManager<char, StaticObject>::registerit(WALL1_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall1Texture()); });
bool WallTile::m_registerit1 = SpawnManager<char, StaticObject>::registerit(WALL2_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall2Texture()); });
bool WallTile::m_registerit2 = SpawnManager<char, StaticObject>::registerit(WALL3_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall3Texture()); });
bool WallTile::m_registerit3 = SpawnManager<char, StaticObject>::registerit(WALL4_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall4Texture()); });
bool WallTile::m_registerit4 = SpawnManager<char, StaticObject>::registerit(WALL7_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall7Texture()); });
bool WallTile::m_registerit5 = SpawnManager<char, StaticObject>::registerit(WALL8_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<WallTile>(pos, Source::instance().getWall8Texture()); });

WallTile::WallTile(const sf::Vector2f& position, const sf::Texture &t) :
	StaticObject(position, t) {}