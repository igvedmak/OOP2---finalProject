#include "PlayState.h"
bool PlayState::m_registerit = SpawnManager<States, GameState>::registerit(States::PLAY, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<PlayState>(pos, Source::instance().getLvlTexture()); });

// the function get the controller and display the end state when the user finished the levels
// successfully or not
void PlayState::displayState(GameManager & controller){}
// the function get the controller and handle the event that happend by the user
void PlayState::handleEvent(GameManager & controller){}
PlayState::PlayState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture){}


PlayState::~PlayState(){}
