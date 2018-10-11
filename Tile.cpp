#include "Tile.h"

bool Tile::m_registerit = SpawnManager<char, StaticObject>::registerit(TILE_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Tile>(pos, Source::instance().getTileTexture()); });
bool Tile::m_registerit1 = SpawnManager<char, StaticObject>::registerit(TILE1_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Tile>(pos, Source::instance().getTile1Texture()); });
bool Tile::m_registerit2 = SpawnManager<char, StaticObject>::registerit(TILE2_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Tile>(pos, Source::instance().getTile2Texture()); });
bool Tile::m_registerit3 = SpawnManager<char, StaticObject>::registerit(TILE3_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Tile>(pos, Source::instance().getTile3Texture()); });
bool Tile::m_registerit4 = SpawnManager<char, StaticObject>::registerit(SMALLTILE_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Tile>(pos, Source::instance().getSmallTileTexture()); });
Tile::Tile(const sf::Vector2f& position, const sf::Texture &t)
	: StaticObject(position, t){}
