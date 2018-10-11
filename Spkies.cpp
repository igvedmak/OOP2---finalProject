#include "Spkies.h"
bool Spkies::m_registerit = SpawnManager<char, StaticObject>::registerit(SPIKES_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkiesTexture()); });
bool Spkies::m_registerit1 = SpawnManager<char, StaticObject>::registerit(SPIKES1_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkies1Texture()); });
bool Spkies::m_registerit2 = SpawnManager<char, StaticObject>::registerit(SPIKES2_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkies2Texture()); });
bool Spkies::m_registerit3 = SpawnManager<char, StaticObject>::registerit(SPIKES3_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkies3Texture()); });
bool Spkies::m_registerit4 = SpawnManager<char, StaticObject>::registerit(SPIKES4_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkies4Texture()); });
bool Spkies::m_registerit5 = SpawnManager<char, StaticObject>::registerit(SPIKES5_C, [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> { return std::make_unique<Spkies>(pos, Source::instance().getSpkies5Texture()); });

Spkies::Spkies(const sf::Vector2f& position, const sf::Texture &t) 
	: Obstacle(position, t){}