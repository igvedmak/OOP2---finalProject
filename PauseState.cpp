#include "PauseState.h"

bool PauseState::m_registerit = SpawnManager<States, GameState>::registerit(States::PAUSE, [](const sf::Vector2f& pos) -> std::unique_ptr<GameState> { return std::make_unique<PauseState>(pos, Source::instance().getPauseTexture()); });

PauseState::PauseState(const sf::Vector2f& coords, const sf::Texture& texture)
	:GameState(coords, texture){
	m_sprite.setScale(scaleWidth, scaleHeigth);
	const auto& font = Source::instance().getFont();

	m_title = sf::Text{ Pause ,font ,80U };
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setPosition(STATE_WIDTH / 2, 10.f);
	m_title.setFillColor(sf::Color::Yellow);
}

void PauseState::displayState(GameManager& controller) {
	auto& window = controller.getWindow();
	draw(window);
	window.draw(m_title);
}
void PauseState::handleEvent(GameManager& controller) {
	sf::Event event = controller.getEvent();
	while (controller.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			controller.popState();           // pop the introduction state at the controller
			return;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				controller.changeState(States::PLAY); // update the next state at the controller to menu
				break;

			default:
				break;
			}
		}
	}
}
