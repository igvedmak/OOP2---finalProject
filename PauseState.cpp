#include "PauseState.h"

bool PauseState::m_registerit = SpawnManager<States, GameState>::registerit(States::PAUSE, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<PauseState>(pos, Source::instance().getPauseTexture()); });

PauseState::PauseState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture)
{
}


void PauseState::displayState(GameManager& controller) {

}
void PauseState::handleEvent(GameManager& controller) {

}
