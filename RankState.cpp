#include "RankState.h"

bool RankState::m_registerit = SpawnManager<States, GameState>::registerit(States::SCORES, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<RankState>(pos, Source::instance().getScoreTexture()); });

RankState::RankState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture)
{
}

void RankState::displayState(GameManager& controller) {

}
void RankState::handleEvent(GameManager& controller) {

}