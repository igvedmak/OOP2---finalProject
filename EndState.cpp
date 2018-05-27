#include "EndState.h"

bool EndState::m_registerit = SpawnManager<States, GameState>::registerit(States::ENDGAME, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<EndState>(pos, Source::instance().getEndTexture()); });
// constractor
EndState::EndState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture)
{}

// the function get the controller and display the end state when the user finished the levels
// successfully or not
void EndState::displayState(GameManager & controller)
{}
// the function get the controller and handle the event that happend by the user
void EndState::handleEvent(GameManager & controller)
{}